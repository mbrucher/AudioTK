/**
 * \file TransistorClassAFilter.cpp
 */

#include "TransistorClassAFilter.h"

#include <cassert>

#include <ATK/Utility/VectorizedNewtonRaphson.h>

namespace ATK
{
  template <typename DataType_>
  class TransistorClassAFilter<DataType_>::TransistorClassAFunction
  {
    DataType_ dt;
    
    DataType_ Rp;
    DataType_ Rg;
    DataType_ Ro;
    DataType_ Rk;
    DataType_ VBias;
    DataType_ Co;
    DataType_ Ck;
    
    DataType_ Is;
    DataType_ Vt;
    DataType_ Br;
    DataType_ Bf;
    
    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      return Is * ((std::exp(Vbe / Vt) - 1) / Bf + (std::exp((Vbe - Vce) / Vt) - 1) / Br);
    }

    DataType_ Lc(DataType_ Vbe, DataType_ Vce)
    {
      return Is * ((std::exp(Vbe / Vt) - std::exp((Vbe - Vce) / Vt)) - (std::exp((Vbe - Vce) / Vt) - 1) / Br);
    }

  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 4, 1> Vector;
    typedef Eigen::Matrix<DataType, 4, 4> Matrix;
    
    TransistorClassAFunction(DataType dt)
    :dt(dt), Rp(100e3), Rg(220e3), Ro(22e3), Rk(2.7e3), VBias(400), Co(20e-9), Ck(10e-6), Is(1e-12), Vt(26e-3), Br(1), Bf(100)
    {
    }

    Vector estimate(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      Vector y0 = Vector::Zero();
      for(int j = 0; j < 4; ++j)
      {
        y0.data()[j] = output[j][i-1];
      }

      return y0;
    }
    
    std::pair<Vector, Matrix> operator()(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output, const Vector& y1)
    {
      auto Ib_old = Lb(output[3][i-1] - output[1][i-1], output[3][i-1] - output[2][i-1]);
      auto Ic_old = Lc(output[3][i-1] - output[1][i-1], output[3][i-1] - output[2][i-1]);

      auto Ib = Lb(output[3][i] - output[1][i], output[3][i] - output[2][i]);
      auto Ic = Lc(output[3][i] - output[1][i], output[3][i] - output[2][i]);

      auto f1_old = - output[3][i-1] / (Rk * Ck) + (Ib_old + Ic_old) / Ck;
      auto f2_old = - output[0][i-1] / (Ro * Co);

      auto f1 = - output[3][i] / (Rk * Ck) + (Ib + Ic) / Ck;
      auto f2 = - output[0][i] / (Ro * Co);

      auto g1 = output[2][i] + Rp * (Ic + output[0][i] / Ro) - VBias;
      auto g2 = output[1][i] - input[0][i] + Rg * Ib;
      
      Vector F(Vector::Zero());
      
      F << (dt / 2 * (f1 + f1_old) + output[0][i-1] - output[0][i]) , (dt / 2 * (f2 + f2_old) + output[1][i-1] - output[1][i]) , (g1) , (g2);
      Matrix M(Matrix::Zero());
      M << -1, 0, 0, (-1/(Rk * Ck)),
           (-1/(Ro * Co)), 0, 0, 0,
           Rp/Ro, 0, 1, 0,
           -1, 1, 0, 1;
      return std::make_pair(F, M);
    }

  };
  
  template <typename DataType>
  TransistorClassAFilter<DataType>::TransistorClassAFilter()
    :Parent(1, 4)
  {
    input_delay = output_delay = 1;
  }
  
  template <typename DataType>
  TransistorClassAFilter<DataType>::~TransistorClassAFilter()
  {
  }
  
  template<typename DataType_>
  void TransistorClassAFilter<DataType_>::setup()
  {
    Parent::setup();
    optimizer.reset(new VectorizedNewtonRaphson<TransistorClassAFunction, 4, 10, true>(TransistorClassAFunction(static_cast<DataType>(1. / input_sampling_rate))));
  }

  template<typename DataType_>
  void TransistorClassAFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(input_sampling_rate == output_sampling_rate);

    for(int64_t i = 0; i < size; ++i)
    {
      optimizer->optimize(i, converted_inputs.data(), outputs.data());
    }
  }

  template class TransistorClassAFilter<float>;
  template class TransistorClassAFilter<double>;
}
