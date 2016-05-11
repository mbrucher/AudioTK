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
    const DataType_ mu;
    const DataType_ K;
    const DataType_ Kp;
    const DataType_ Kvb;
    const DataType_ Kg;
    const DataType_ Ex;

    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      if(mu * Vbe + Vce > 0)
        return K * std::pow(mu * Vbe + Vce, 1.5);
      return 0;
    }

    DataType_ Lb_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      if (mu * Vbe + Vce > 0)
        return K * mu * 1.5 * std::sqrt(mu * Vbe + Vce);
      return 0;
    }

    DataType_ Lb_Vce(DataType_ Vbe, DataType_ Vce)
    {
      if (mu * Vbe + Vce > 0)
        return K * 1.5 * std::sqrt(mu * Vbe + Vce);;
      return 0;
    }

    DataType_ Lc(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        DataType_ E1 = Vce / Kp * std::log(1 + std::exp(Kp * (1/mu + Vbe / std::sqrt(Kvb + Vce * Vce))));
        return 2 / Kg * std::pow(E1, Ex);
      }
      return 0;
    }

    DataType_ Lc_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        DataType_ E2 = 1 + std::exp(Kp * (1 / mu + Vbe / std::sqrt(Kvb + Vce * Vce)));
        DataType_ E1 = Vce / Kp * std::log(E2);
        DataType_ E1p = Vce / Kp / E2 * (E2 - 1) * Kp / std::sqrt(Kvb + Vce * Vce);
        return 2 * Ex / Kg * std::pow(E1, Ex - 1) * E1p;
      }
      return 0;
    }

    DataType_ Lc_Vce(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        DataType_ E2 = 1 + std::exp(Kp * (1 / mu + Vbe / std::sqrt(Kvb + Vce * Vce)));
        DataType_ E1 = Vce / Kp * std::log(E2);
        DataType_ E1p = 1/Kp * std::log(E2) + Vce / Kp / E2 * (E2 - 1) * Kp * Vce / std::pow(Kvb + Vce * Vce, 1.5);
        return 2 * Ex / Kg * std::pow(E1, Ex - 1) * E1p;
      }
      return 0;
    }

    TubeFunction(DataType_ mu, DataType_ K, DataType_ Kp, DataType_ Kvb, DataType_ Kg, DataType_ Ex)
      :mu(mu), K(K), Kp(Kp), Kvb(Kvb), Kg(Kg), Ex(Ex)
    {
    }

  };

  template <typename DataType_>
  class TubeFilter<DataType_>::CommonCathodeTriodeFunction : public TubeFunction<DataType_>
  {
    const DataType_ dt;
    
    const DataType_ Rp;
    const DataType_ Rg;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;
    const DataType_ Co;
    const DataType_ Ck;

    using TubeFunction<DataType_>::Lb;
    using TubeFunction<DataType_>::Lb_Vbe;
    using TubeFunction<DataType_>::Lb_Vce;
    using TubeFunction<DataType_>::Lc;
    using TubeFunction<DataType_>::Lc_Vbe;
    using TubeFunction<DataType_>::Lc_Vce;

  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 4, 1> Vector;
    typedef Eigen::Matrix<DataType, 4, 4> Matrix;
    
    CommonCathodeTriodeFunction(DataType dt, DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType VBias, DataType Co, DataType Ck, DataType_ mu, DataType_ K, DataType_ Kp, DataType_ Kvb, DataType_ Kg, DataType_ Ex)
      :TubeFunction<DataType_>(mu, K, Kp, Kvb, Kg, Ex), dt(dt), Rp(Rp), Rg(Rg), Ro(Ro), Rk(Rk), VBias(VBias), Co(Co), Ck(Ck)
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

      auto Ib = Lb(y1(3) - y1(0), y1(2) - y1(0));
      auto Ic = Lc(y1(3) - y1(0), y1(2) - y1(0));

      auto Ib_Vbe = Lb_Vbe(y1(3) - y1(0), y1(2) - y1(0));
      auto Ib_Vce = Lb_Vce(y1(3) - y1(0), y1(2) - y1(0));

      auto Ic_Vbe = Lc_Vbe(y1(3) - y1(0), y1(2) - y1(0));
      auto Ic_Vce = Lc_Vce(y1(3) - y1(0), y1(2) - y1(0));

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
      M << (-1 -dt/2/(Rk * Ck)) - dt/2*((Ib_Vbe + Ic_Vbe + Ib_Vce + Ic_Vce)/ Ck), 0, dt/2*(Ib_Vce + Ic_Vce) / Ck, dt/2*(Ib_Vbe + Ic_Vbe) / Ck,
            0, -1 -dt/2*(Ro * Co), -dt/2*(Ro * Co), 0,
            -Rp * (Ic_Vbe + Ic_Vce), Rp / Ro, 1 + Rp / Ro + Rp * Ic_Vce, Rp * Ic_Vbe,
            -Rg * (Ib_Vbe + Ib_Vce), 0, Rg * Ib_Vce, Rg * Ib_Vbe + 1;
      
      return std::make_pair(F, M);
    }

  };
  
  template <typename DataType_>
  class CommonCathodeTriodeInitialFunction : public TubeFunction<DataType_>
  {
    const DataType_ Rp;
    const DataType_ Rg;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;

    using TubeFunction<DataType_>::Lb;
    using TubeFunction<DataType_>::Lb_Vbe;
    using TubeFunction<DataType_>::Lb_Vce;
    using TubeFunction<DataType_>::Lc;
    using TubeFunction<DataType_>::Lc_Vbe;
    using TubeFunction<DataType_>::Lc_Vce;

  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 3, 1> Vector;
    typedef Eigen::Matrix<DataType, 3, 3> Matrix;

    CommonCathodeTriodeInitialFunction(DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType VBias, DataType_ mu, DataType_ K, DataType_ Kp, DataType_ Kvb, DataType_ Kg, DataType_ Ex)
      :TubeFunction<DataType_>(mu, K, Kp, Kvb, Kg, Ex), Rp(Rp), Rg(Rg), Ro(Ro), Rk(Rk), VBias(VBias)
    {
    }

    std::pair<Vector, Matrix> operator()(const Vector& y1)
    {
      auto Ib = Lb(y1(0) - y1(1), y1(0) - y1(2));
      auto Ic = Lc(y1(0) - y1(1), y1(0) - y1(2));

      auto Ib_Vbe = Lb_Vbe(y1(0) - y1(1), y1(0) - y1(2));
      auto Ib_Vce = Lb_Vce(y1(0) - y1(1), y1(0) - y1(2));

      auto Ic_Vbe = Lc_Vbe(y1(0) - y1(1), y1(0) - y1(2));
      auto Ic_Vce = Lc_Vce(y1(0) - y1(1), y1(0) - y1(2));

      Vector F(Vector::Zero());
      F << y1(0) - VBias + Ic * Rp,
        Ib * Rg + y1(1),
        y1(2) - (Ib + Ic) * Rk;

      Matrix M(Matrix::Zero());
      M << 1 + Rp * (Ic_Vbe + Ic_Vce), -Rp * Ic_Vbe, -Rp * Ic_Vce,
        (Ib_Vbe + Ib_Vce) * Rg, 1 - Rg * Ib_Vbe, -Rg * Ib_Vce,
        -(Ic_Vbe + Ic_Vce + Ib_Vbe + Ib_Vce) * Rk, (Ic_Vbe + Ib_Vbe) * Rk, 1 + (Ic_Vce + Ib_Vce) * Rk;

      return std::make_pair(F, M);
    }
  };

  template <typename DataType>
  TubeFilter<DataType>::TubeFilter(DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType VBias, DataType Co, DataType Ck, DataType mu, DataType K, DataType Kp, DataType Kvb, DataType Kg, DataType Ex)
    :Parent(1, 5), Rp(Rp), Rg(Rg), Ro(Ro), Rk(Rk), VBias(VBias), Co(Co), Ck(Ck), mu(mu), K(K), Kp(Kp), Kvb(Kvb), Kg(Kg), Ex(Ex)
  {
    input_delay = output_delay = 1;
  }

  template <typename DataType>
  TubeFilter<DataType>::TubeFilter(TubeFilter&& other)
    :Parent(std::move(other)), Rp(other.Rp), Rg(other.Rg), Ro(other.Ro), Rk(other.Rk), VBias(other.VBias), Co(other.Co), Ck(other.Ck), mu(other.mu), K(other.K), Kp(other.Kp), Kvb(other.Kvb), Kg(other.Kg), Ex(other.Ex)
  {
  }

  template<typename DataType_>
  TubeFilter<DataType_>::~TubeFilter()
  {
  }

  template<typename DataType_>
  void TubeFilter<DataType_>::setup()
  {
    Parent::setup();
    optimizer.reset(new VectorizedNewtonRaphson<CommonCathodeTriodeFunction, 4, 10, true>(CommonCathodeTriodeFunction(static_cast<DataType>(1. / input_sampling_rate),
      Rp, Rg, Ro, Rk, //R
      VBias, // VBias
      Co, Ck, // C
      mu, K, Kp, Kvb, Kg, Ex // tube
      )));
  }

  template<typename DataType_>
  void TubeFilter<DataType_>::full_setup()
  {
    // setup default_output
    SimplifiedVectorizedNewtonRaphson<CommonCathodeTriodeInitialFunction<DataType_>, 3, 10> custom(CommonCathodeTriodeInitialFunction<DataType_>(
      Rp, Rg, Ro, Rk, //R
      VBias, // VBias
      mu, K, Kp, Kvb, Kg, Ex // tube
      ));

    auto stable = custom.optimize();

    default_output[0] = 0;
    default_output[1] = stable(2);
    default_output[2] = -stable(0);
    default_output[3] = stable(0);
    default_output[4] = stable(1);

    Parent::full_setup();
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
    return TubeFilter<DataType_>(100e3, 220e3, 22e3, 2.7e3, //R
      400, // VBias
      20e-9, 10e-6, // C
      88.5, 1.73e-6, 600, 300, 1060, 1.4 // transistor
      );
  }

  template class TubeFilter<float>;
  template class TubeFilter<double>;
}
