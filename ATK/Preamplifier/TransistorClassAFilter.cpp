/**
 * \file TransistorClassAFilter.cpp
 */

#include "TransistorClassAFilter.h"

#include <cassert>

#include <ATK/Utility/SimplifiedVectorizedNewtonRaphson.h>
#include <ATK/Utility/VectorizedNewtonRaphson.h>

namespace ATK
{
  template <typename DataType_>
  class TransistorClassAFilter<DataType_>::TransistorClassAFunction
  {
    const DataType_ dt;
    
    const DataType_ Rp;
    const DataType_ Rg1;
    const DataType_ Rg2;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;
    const DataType_ Cg;
    const DataType_ Co;
    const DataType_ Ck;
    
    const DataType_ Is;
    const DataType_ Vt;
    const DataType_ Br;
    const DataType_ Bf;
    
    DataType_ Lb(const std::pair<DataType_, DataType_>& exp)
    {
      return Is * ((exp.first - 1) / Bf + (exp.second - 1) / Br);
    }
    
    DataType_ Lb_Vbe(const std::pair<DataType_, DataType_>& exp)
    {
      return Is / Vt * (exp.first / Bf + exp.second / Br);
    }
    
    DataType_ Lb_Vce(const std::pair<DataType_, DataType_>& exp)
    {
      return -Is / Vt * (exp.second / Br);
    }
    
    DataType_ Lc(const std::pair<DataType_, DataType_>& exp)
    {
      return Is * ((exp.first - exp.second) - (exp.second - 1) / Br);
    }
    
    DataType_ Lc_Vbe(const std::pair<DataType_, DataType_>& exp)
    {
      return Is / Vt * ((exp.first - exp.second) - exp.second / Br);
    }
    
    DataType_ Lc_Vce(const std::pair<DataType_, DataType_>& exp)
    {
      return Is / Vt * (exp.second + exp.second / Br);
    }

  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 4, 1> Vector;
    typedef Eigen::Matrix<DataType, 4, 4> Matrix;

    std::pair<DataType, DataType> exp_y0;

    TransistorClassAFunction(DataType dt, DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk, DataType VBias, DataType Cg, DataType Co, DataType Ck, DataType Is, DataType Vt, DataType Br, DataType Bf)
    :dt(dt), Rp(1e3), Rg1(16.7e3), Rg2(1.47e3), Ro(22e3), Rk(100), VBias(5), Cg(3.3e-6), Co(1e-6), Ck(160e-6), Is(1e-12), Vt(26e-3), Br(1), Bf(100)
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
      auto Ib_old = Lb(exp_y0);
      auto Ic_old = Lc(exp_y0);

      std::pair<DataType, DataType> exp_y1 = std::make_pair(std::exp((y1(3) - y1(0)) / Vt), std::exp((y1(3) - y1(2)) / Vt));
      
      auto Ib = Lb(exp_y1);
      auto Ic = Lc(exp_y1);
      
      auto Ib_Vbe = Lb_Vbe(exp_y1);
      auto Ib_Vbc = Lb_Vce(exp_y1);

      auto Ic_Vbe = Lc_Vbe(exp_y1);
      auto Ic_Vbc = Lc_Vce(exp_y1);

      auto f1_old = - output[0][i-1] / (Rk * Ck) + (Ib_old + Ic_old) / Ck;
      auto f2_old = - (output[1][i-1] + output[2][i-1]) / (Ro * Co);
      auto f4_old = 1/Cg * (output[3][i-1] * (1/Rg1 + 1/Rg2) - VBias/Rg1 + Ib_old);

      auto f1 = - y1(0) / (Rk * Ck) + (Ib + Ic) / Ck;
      auto f2 = - (y1(1) + y1(2)) / (Ro * Co);
      auto f4 = 1/Cg * (y1(3) * (1/Rg1 + 1/Rg2) - VBias/Rg1 + Ib);

      auto g1 = y1(2) + Rp * (Ic + (y1(1) + y1(2)) / Ro) - VBias;
      
      Vector F(Vector::Zero());
      F << (dt / 2 * (f1 + f1_old) + output[0][i-1] - y1(0)),
           (dt / 2 * (f2 + f2_old) + output[1][i-1] - y1(1)),
           (g1),
           (dt / 2 * (f4 + f4_old) - (output[3][i-1] - y1(3) + input[0][i] - input[0][i-1]));

      Matrix M(Matrix::Zero());
      M << (-1 - dt/2/(Rk * Ck)) - dt/2*((Ib_Vbe + Ic_Vbe)/ Ck), 0, -dt/2*(Ib_Vbc + Ic_Vbc) / Ck, dt/2*(Ib_Vbe + Ic_Vbe + Ib_Vbc + Ic_Vbc) / Ck,
            0, -1 -dt/2*(Ro * Co), -dt/2*(Ro * Co), 0,
            -Rp * Ic_Vbe, Rp / Ro, 1 + Rp / Ro - Rp * Ic_Vbc, Rp * (Ic_Vbe + Ic_Vbc),
            -dt/2 * Ib_Vbe/Cg, 0, -dt/2 * Ib_Vbc/Cg, 1 + dt/2 * (1/Cg * ((1/Rg1 + 1/Rg2) + (Ib_Vbc + Ib_Vbe)));

      return std::make_pair(F, M);
    }

  };
  
  template <typename DataType_>
  class TransistorClassAInitialFunction
  {
    const DataType_ Rp;
    const DataType_ Rg1;
    const DataType_ Rg2;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;
    
    const DataType_ Is;
    const DataType_ Vt;
    const DataType_ Br;
    const DataType_ Bf;
    
    DataType_ Lb(const std::pair<DataType_, DataType_>& exp)
    {
      return Is * ((exp.first - 1) / Bf + (exp.second - 1) / Br);
    }
    
    DataType_ Lb_Vbe(const std::pair<DataType_, DataType_>& exp)
    {
      return Is / Vt * (exp.first / Bf + exp.second / Br);
    }
    
    DataType_ Lb_Vce(const std::pair<DataType_, DataType_>& exp)
    {
      return -Is / Vt * (exp.second / Br);
    }
    
    DataType_ Lc(const std::pair<DataType_, DataType_>& exp)
    {
      return Is * ((exp.first - exp.second) - (exp.second - 1) / Br);
    }
    
    DataType_ Lc_Vbe(const std::pair<DataType_, DataType_>& exp)
    {
      return Is / Vt * ((exp.first - exp.second) - exp.second / Br);
    }
    
    DataType_ Lc_Vce(const std::pair<DataType_, DataType_>& exp)
    {
      return Is / Vt * (exp.second + exp.second / Br);
    }
    
  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 3, 1> Vector;
    typedef Eigen::Matrix<DataType, 3, 3> Matrix;
    
    TransistorClassAInitialFunction(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk, DataType VBias, DataType Is, DataType Vt, DataType Br, DataType Bf)
    :Rp(1e3), Rg1(16.7e3), Rg2(1.47e3), Ro(22e3), Rk(100), VBias(5), Is(1e-12), Vt(26e-3), Br(1), Bf(100)
    {
    }
    
    std::pair<Vector, Matrix> operator()(const Vector& y1)
    {
      std::pair<DataType, DataType> exp_y1 = std::make_pair(std::exp((y1(2) - y1(1)) / Vt), std::exp((y1(2) - y1(0)) / Vt));
      
      auto Ib = Lb(exp_y1);
      auto Ic = Lc(exp_y1);
      
      auto Ib_Vbe = Lb_Vbe(exp_y1);
      auto Ib_Vbc = Lb_Vce(exp_y1);
      
      auto Ic_Vbe = Lc_Vbe(exp_y1);
      auto Ic_Vbc = Lc_Vce(exp_y1);
      
      Vector F(Vector::Zero());
      auto R = 1/(1/Rg1 + 1/Rg2);
      F << y1(0) - VBias + Ic * Rp, y1(1) - (Ib + Ic) * Rk, Ib * R + y1(2) - VBias / Rg1 * R;
      
      Matrix M(Matrix::Zero());
      M << 1 - Ic_Vbc * Rp, -Ic_Vbe * Rp, (Ic_Vbe + Ic_Vbc) * Rp,
           (Ib_Vbc + Ic_Vbc) * Rk, 1 + (Ib_Vbe + Ic_Vbe + Ib_Vbc + Ic_Vbc) * Rk, -(Ib_Vbe + Ic_Vbe + Ib_Vbc + Ic_Vbc) * Rk,
           -Ib_Vbc * R, -Ib_Vbe * R, 1 + (Ib_Vbe + Ib_Vbc) * R;

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
    optimizer.reset(new VectorizedNewtonRaphson<TransistorClassAFunction, 4, 10, true>(TransistorClassAFunction(static_cast<DataType>(1. / input_sampling_rate),
                    1e3, 16.7e3, 1.47e3, 22e3, 100, //R
                    5, // VBias
                    3.3e-6, 1e-6, 160e-6, // C
                    1e-12, 26e-3, 1, 100 // transistor
                    )));
  }

  template<typename DataType_>
  void TransistorClassAFilter<DataType_>::full_setup()
  {
    Parent::full_setup();
    // setup default_output

    SimplifiedVectorizedNewtonRaphson<TransistorClassAInitialFunction<DataType_>, 3, 10> custom(TransistorClassAInitialFunction<DataType_>(
                    1e3, 16.7e3, 1.47e3, 22e3, 100, //R
                    5, // VBias
                    1e-12, 26e-3, 1, 100 // transistor
                    ));
    
    auto stable = custom.optimize();

    default_output[0] = 0;
    default_output[1] = stable(1);
    default_output[2] = -stable(0);
    default_output[3] = stable(0);
    default_output[4] = stable(2);
  }

  template<typename DataType_>
  void TransistorClassAFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(input_sampling_rate == output_sampling_rate);

    DataType Vt = 26e-3;

    for(int64_t i = 0; i < size; ++i)
    {
      optimizer->get_function().exp_y0 = std::make_pair(std::exp((outputs[4][i-1] - outputs[1][i-1]) / Vt), std::exp((outputs[4][i-1] - outputs[3][i-1]) / Vt));

      optimizer->optimize(i, converted_inputs.data(), outputs.data() + 1);
      outputs[0][i] = outputs[2][i] + outputs[3][i];
    }
  }

  template class TransistorClassAFilter<float>;
  template class TransistorClassAFilter<double>;
}
