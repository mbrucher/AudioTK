/**
 * \file TubeFilter.cpp
 */

#include "TubeFilter.h"

#include <cassert>

#include <ATK/Utility/SimplifiedVectorizedNewtonRaphson.h>
#include <ATK/Utility/VectorizedNewtonRaphson.h>

namespace ATK
{
  template <typename DataType_>
  class TubeFunction
  {
  protected:
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

    TubeFunction(DataType_ Is, DataType_ Vt, DataType_ Br, DataType_ Bf)
      :Is(Is), Vt(Vt), Br(Br), Bf(Bf)
    {
    }

  };

  template <typename DataType_>
  class TubeFilter<DataType_>::CommonCathodeTriodeFunction : public TubeFunction<DataType_>
  {
    const DataType_ dt;
    
    const DataType_ Rp;
    const DataType_ Rg1;
    const DataType_ Rg2;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;
    const DataType_ Co;
    const DataType_ Ck;
    const DataType_ Cg;

  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 4, 1> Vector;
    typedef Eigen::Matrix<DataType, 4, 4> Matrix;
    
    CommonCathodeTriodeFunction(DataType dt, DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk, DataType VBias, DataType Cg, DataType Co, DataType Ck, DataType Is, DataType Vt, DataType Br, DataType Bf)
      :TubeFunction<DataType_>(Is, Vt, Br, Bf), dt(dt), Rp(Rp), Rg1(Rg1), Rg2(Rg2), Ro(Ro), Rk(Rk), VBias(VBias), Cg(Cg), Co(Co), Ck(Ck)
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
      auto Ib_old = Lb(output[3][i-1] - output[0][i-1], output[2][i-1] - output[0][i-1]);
      auto Ic_old = Lc(output[3][i-1] - output[0][i-1], output[2][i-1] - output[0][i-1]);

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
      auto g2 = y1(3) - input[0][i] + Rg1 * Ib;
      
      Vector F(Vector::Zero());
      F << (dt / 2 * (f1 + f1_old) + output[0][i-1] - y1(0)),
           (dt / 2 * (f2 + f2_old) + output[1][i-1] - y1(1)),
           (g1),
           (g2);

      Matrix M(Matrix::Zero());
      M << (-1 -dt/2/(Rk * Ck)) - dt/2*((Ib_Vbe + Ic_Vbe + Ib_Vce + Ic_Vce)/ Ck), 0, dt/2*(Ib_Vce + Ic_Vce) / Ck, dt/2*(Ib_Vbe + Ic_Vbe) / Ck,
            0, -1 -dt/2*(Ro * Co), -dt/2*(Ro * Co), 0,
            -Rp * (Ic_Vbe + Ic_Vce), Rp / Ro, 1 + Rp / Ro + Rp * Ic_Vce, Rp * Ic_Vbe,
            -Rg1 * (Ib_Vbe + Ib_Vce), 0, Rg1 * Ib_Vce, Rg1 * Ib_Vbe + 1;
      
      return std::make_pair(F, M);
    }

  };
  
  template <typename DataType_>
  class CommonCathodeTriodeInitialFunction : public TubeFunction<DataType_>
  {
    const DataType_ Rp;
    const DataType_ Rg1;
    const DataType_ Rg2;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;

  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 3, 1> Vector;
    typedef Eigen::Matrix<DataType, 3, 3> Matrix;

    CommonCathodeTriodeInitialFunction(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk, DataType VBias, DataType Is, DataType Vt, DataType Br, DataType Bf)
      :TubeFunction<DataType_>(Is, Vt, Br, Bf), Rp(Rp), Rg1(Rg1), Rg2(Rg2), Ro(Ro), Rk(Rk), VBias(VBias)
    {
    }

    std::pair<Vector, Matrix> operator()(const Vector& y1)
    {
      auto Ib = Lb(y1(0) - y1(3), y1(0) - y1(2));
      auto Ic = Lc(y1(0) - y1(3), y1(0) - y1(2));

      auto Ib_Vbe = Lb_Vbe(y1(0) - y1(3), y1(0) - y1(2));
      auto Ib_Vce = Lb_Vce(y1(0) - y1(3), y1(0) - y1(2));

      auto Ic_Vbe = Lc_Vbe(y1(0) - y1(3), y1(0) - y1(2));
      auto Ic_Vce = Lc_Vce(y1(0) - y1(3), y1(0) - y1(2));

      Vector F(Vector::Zero());
      auto R = 1 / (1 / Rg1 + 1 / Rg2);
      F << y1(0) - VBias + Ic * Rp, y1(1) - (Ib + Ic) * Rk, Ib * R + y1(2) - VBias / Rg1 * R;

      Matrix M(Matrix::Zero());
      M << 1 - Ic_Vce * Rp, -Ic_Vbe * Rp, (Ic_Vbe + Ic_Vce) * Rp,
        (Ib_Vce + Ic_Vce) * Rk, 1 + (Ib_Vbe + Ic_Vbe + Ib_Vce + Ic_Vce) * Rk, -(Ib_Vbe + Ic_Vbe + Ib_Vce + Ic_Vce) * Rk,
        -Ib_Vce * R, -Ib_Vbe * R, 1 + (Ib_Vbe + Ib_Vce) * R;

      return std::make_pair(F, M);
    }
  };

  template <typename DataType>
  TubeFilter<DataType>::TubeFilter(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk, DataType VBias, DataType Cg, DataType Co, DataType Ck, DataType Is, DataType Vt, DataType Br, DataType Bf)
    :Parent(1, 5), Rp(Rp), Rg1(Rg1), Rg2(Rg2), Ro(Ro), Rk(Rk), VBias(VBias), Cg(Cg), Co(Co), Ck(Ck), Is(Is), Vt(Vt), Br(Br), Bf(Bf)
  {
    input_delay = output_delay = 1;
  }

  template <typename DataType>
  TubeFilter<DataType>::TubeFilter(TubeFilter&& other)
    :Parent(std::move(other)), Rp(other.Rp), Rg1(other.Rg1), Rg2(other.Rg2), Ro(other.Ro), Rk(other.Rk), VBias(other.VBias), Cg(other.Cg), Co(other.Co), Ck(other.Ck), Is(other.Is), Vt(other.Vt), Br(other.Br), Bf(other.Bf)
  {
  }

  template<typename DataType_>
  void TubeFilter<DataType_>::setup()
  {
    Parent::setup();
    optimizer.reset(new VectorizedNewtonRaphson<CommonCathodeTriodeFunction, 4, 10, true>(CommonCathodeTriodeFunction(static_cast<DataType>(1. / input_sampling_rate),
      Rp, Rg1, Rg2, Ro, Rk, //R
      VBias, // VBias
      Cg, Co, Ck, // C
      Is, Vt, Br, Bf // transistor
      )));
  }

  template<typename DataType_>
  void TubeFilter<DataType_>::full_setup()
  {
    Parent::full_setup();
    // setup default_output

    SimplifiedVectorizedNewtonRaphson<CommonCathodeTriodeInitialFunction<DataType_>, 3, 10> custom(CommonCathodeTriodeInitialFunction<DataType_>(
      Rp, Rg1, Rg2, Ro, Rk, //R
      VBias, // VBias
      Is, Vt, Br, Bf // transistor
      ));

    auto stable = custom.optimize();

    default_output[0] = 0;
    default_output[1] = stable(1);
    default_output[2] = -stable(0);
    default_output[3] = stable(0);
    default_output[4] = stable(2);
  }

  template<typename DataType_>
  void TubeFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(input_sampling_rate == output_sampling_rate);

    for(int64_t i = 0; i < size; ++i)
    {
      optimizer->optimize(i, converted_inputs.data(), outputs.data() + 1);
      outputs[0][i] = outputs[2][i] + outputs[3][i];
    }
  }

  template<typename DataType_>
  TubeFilter<DataType_> TubeFilter<DataType_>::build_standard_filter()
  {
    return TubeFilter<DataType_>(1e3, 15e3, 1.5e3, 22e3, 100, //R
      5, // VBias
      3.3e-6, 1e-6, 160e-6, // C
      1e-12, 26e-3, 1, 100 // transistor
      );
  }

  template class TubeFilter<float>;
  template class TubeFilter<double>;
}
