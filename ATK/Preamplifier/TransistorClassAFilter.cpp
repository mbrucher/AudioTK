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
    const DataType_ dt;
    
    const DataType_ Rp;
    const DataType_ Rg;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;
    const DataType_ Co;
    const DataType_ Ck;
    
    const DataType_ Is;
    const DataType_ Vt;
    const DataType_ Br;
    const DataType_ Bf;
    
    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      return Is * ((std::exp(Vbe / Vt) - 1) / Bf + (std::exp((Vce - Vbe) / Vt) - 1) / Br);
    }

    DataType_ Lb_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      return Is / Vt * (std::exp(Vbe / Vt) / Bf - std::exp((Vce - Vbe) / Vt) / Br);
    }

    DataType_ Lb_Vce(DataType_ Vbe, DataType_ Vce)
    {
      return Is / Vt * (std::exp((Vce - Vbe) / Vt) / Br);
    }

    DataType_ Lc(DataType_ Vbe, DataType_ Vce)
    {
      return Is * ((std::exp(Vbe / Vt) - std::exp((Vce - Vbe) / Vt)) - (std::exp((Vce - Vbe) / Vt) - 1) / Br);
    }

    DataType_ Lc_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      return Is / Vt * ((std::exp(Vbe / Vt) + std::exp((Vce - Vbe) / Vt)) + std::exp((Vce - Vbe) / Vt) / Br);
    }

    DataType_ Lc_Vce(DataType_ Vbe, DataType_ Vce)
    {
      return -Is / Vt * (std::exp((Vce - Vbe) / Vt) + std::exp((Vce - Vbe) / Vt) / Br);
    }

  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 4, 1> Vector;
    typedef Eigen::Matrix<DataType, 4, 4> Matrix;
    
    TransistorClassAFunction(DataType dt)
    :dt(dt), Rp(100e3), Rg(220e3), Ro(22e3), Rk(2.7e3), VBias(12), Co(20e-9), Ck(10e-6), Is(1e-12), Vt(26e-3), Br(1), Bf(100)
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
      auto Ib_old = Lb(output[0][i-1] - output[3][i-1], output[0][i-1] - output[2][i-1]);
      auto Ic_old = Lc(output[0][i-1] - output[3][i-1], output[0][i-1] - output[2][i-1]);

      auto Ib = Lb(y1(0) - y1(3), y1(0) - y1(2));
      auto Ic = Lc(y1(0) - y1(3), y1(0) - y1(2));

      auto Ib_Vbe = Lb_Vbe(y1(0) - y1(3), y1(0) - y1(2));
      auto Ib_Vce = Lb_Vce(y1(0) - y1(3), y1(0) - y1(2));

      auto Ic_Vbe = Lc_Vbe(y1(0) - y1(3), y1(0) - y1(2));
      auto Ic_Vce = Lc_Vce(y1(0) - y1(3), y1(0) - y1(2));

      auto f1_old = - output[0][i-1] / (Rk * Ck) + (Ib_old + Ic_old) / Ck;
      auto f2_old = - (output[1][i-1] + output[2][i-1]) / (Ro * Co);

      auto f1 = - y1(0) / (Rk * Ck) + (Ib + Ic) / Ck;
      auto f2 = - (y1(1) + y1(2)) / (Ro * Co);

      auto g1 = y1(2) + Rp * (Ic + (y1(1) + y1(2)) / Ro) - VBias;
      auto g2 = y1(3) - input[0][i] + Rg * Ib;
      
      Vector F(Vector::Zero());
      F << (dt / 2 * (f1 + f1_old) + output[0][i-1] - y1(0)),
           (dt / 2 * (f2 + f2_old) + output[1][i-1] - y1(1)),
           (g1),
           (g2);

      Matrix M(Matrix::Zero());
      M << (-1 -dt/2/(Rk * Ck))+ dt/2*((Ib_Vbe + Ic_Vbe + Ib_Vce + Ic_Vce)/ Ck), 0, -dt/2*(Ib_Vce + Ic_Vce) / Ck, -dt/2*(Ib_Vbe + Ic_Vbe) / Ck,
            0, -1 -dt/2*(Ro * Co), -dt/2*(Ro * Co), 0,
            Rp * (Ic_Vbe + Ic_Vce), Rp / Ro, 1 + Rp / Ro - Rp * Ic_Vce, - Rp * Ic_Vbe,
            Rg * (Ib_Vbe + Ib_Vce), 0, -Rg * Ib_Vce, -Rg * Ib_Vbe + 1;
      
      return std::make_pair(F, M);
    }

  };
  
  template <typename DataType>
  TransistorClassAFilter<DataType>::TransistorClassAFilter()
    :Parent(1, 5)
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
      optimizer->optimize(i, converted_inputs.data(), outputs.data() + 1);
      outputs[0][i] = outputs[2][i] + outputs[3][i];
    }
  }

  template class TransistorClassAFilter<float>;
  template class TransistorClassAFilter<double>;
}
