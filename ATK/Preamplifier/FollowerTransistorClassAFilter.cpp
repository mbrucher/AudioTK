/**
 * \file FollowerTransistorClassAFilter.cpp
 */

#include "FollowerTransistorClassAFilter.h"
#include "TransistorFunction.h"

#include <cassert>

#include <ATK/Utility/fmath.h>
#include <ATK/Utility/SimplifiedVectorizedNewtonRaphson.h>
#include <ATK/Utility/VectorizedNewtonRaphson.h>

namespace ATK
{
  template <typename DataType_>
  class FollowerTransistorClassAFilter<DataType_>::TransistorClassAFunction
  {
    const DataType_ Rp;
    const DataType_ Rg1;
    const DataType_ Rg2;
    const DataType_ Ro;
    const DataType_ Rk1;
    const DataType_ Rk2;
    const DataType_ VBias;
    const DataType_ Cg;
    const DataType_ Co;
    const DataType_ Ck;

    DataType_ ickeq;
    DataType_ icgeq;
    DataType_ icoeq;

    TransistorFunction<DataType_>& transistor_function;
  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 5, 1> Vector;
    typedef Eigen::Matrix<DataType, 5, 5> Matrix;

    std::pair<DataType, DataType> exp_y0;

    TransistorClassAFunction(DataType dt, DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk1, DataType Rk2, DataType VBias, DataType Cg, DataType Co, DataType Ck, TransistorFunction<DataType_>& transistor_function, const std::vector<DataType>& default_output)
      :Rp(1/Rp), Rg1(1/Rg1), Rg2(1/Rg2), Ro(1/Ro), Rk1(1/Rk1), Rk2(1/Rk2), VBias(VBias), Cg(2 / dt * Cg), Co(2 / dt * Co), Ck(2 / dt * Ck), ickeq(2 / dt * Ck * default_output[1]), icgeq(2 / dt * -Cg * default_output[4]), icoeq(-2 / dt * Co * default_output[2]), transistor_function(transistor_function)
    {
    }

    Vector estimate(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      return id_estimate(i, input, output);
    }

    Vector id_estimate(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      Vector y0 = Vector::Zero();
      for (int j = 0; j < 4; ++j)
      {
        y0.data()[j] = output[j][i - 1];
      }

      return y0;
    }

    Vector affine_estimate(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      std::pair<DataType, DataType> exp_y1 = std::make_pair(fmath::exp((output[3][i - 1] - output[0][i - 1]) / transistor_function.Vt), fmath::exp((output[3][i - 1] - output[2][i - 1]) / transistor_function.Vt));

      auto Ib = transistor_function.Lb(exp_y1);
      auto Ic = transistor_function.Lc(exp_y1);

      auto Ib_Vbe = transistor_function.Lb_Vbe(exp_y1);
      auto Ib_Vbc = transistor_function.Lb_Vbc(exp_y1);

      auto Ic_Vbe = transistor_function.Lc_Vbe(exp_y1);
      auto Ic_Vbc = transistor_function.Lc_Vbc(exp_y1);

      Vector y0;
      y0 << -ickeq - (Ib - Ib_Vbe * (output[3][i - 1] - output[0][i - 1]) - Ib_Vbc * (output[3][i - 1] - output[2][i - 1]) + Ic - Ic_Vbe * (output[3][i - 1] - output[0][i - 1]) - Ic_Vbc * (output[3][i - 1] - output[2][i - 1])),
        -icoeq,
        VBias * Rp - (Ic - Ic_Vbe * (output[3][i - 1] - output[0][i - 1]) - Ic_Vbc * (output[3][i - 1] - output[2][i - 1])),
        input[0][i] * Cg - icgeq + VBias * Rg1 - (Ib - Ib_Vbe * (output[3][i - 1] - output[0][i - 1]) - Ib_Vbc * (output[3][i - 1] - output[2][i - 1])),
        DataType(0);

      Matrix M;
      M << -(Ib_Vbe + Ic_Vbe) - (Rk1 + Ck), 0, -(Ib_Vbc + Ic_Vbc), (Ib_Vbe + Ic_Vbe + Ib_Vbc + Ic_Vbc), 0,
        0, Ro + Co, Ro, 0, 0,
        -Ic_Vbe, Ro, -Ic_Vbc + Ro + Rp, (Ic_Vbe + Ic_Vbc), 0,
        -Ib_Vbe, 0, -Ib_Vbc, (Ib_Vbc + Ib_Vbe) + Rg2 + Rg1 + Cg, 0,
        0, 0, 0, 0, 0;

      return M.inverse() * y0;
    }

    void update_state(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      ickeq = 2 * Ck * output[1][i] - ickeq;
      icgeq = 2 * Cg * (input[0][i] - output[4][i]) - icgeq;
      icoeq = -2 * Co * output[2][i] - icoeq;
    }

    Vector operator()(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output, const Vector& y1)
    {
      std::pair<DataType, DataType> exp_y1 = std::make_pair(fmath::exp((y1(3) - y1(0)) / transistor_function.Vt), fmath::exp((y1(3) - y1(2)) / transistor_function.Vt));

      auto Ib = transistor_function.Lb(exp_y1);
      auto Ic = transistor_function.Lc(exp_y1);

      auto Ib_Vbe = transistor_function.Lb_Vbe(exp_y1);
      auto Ib_Vbc = transistor_function.Lb_Vbc(exp_y1);

      auto Ic_Vbe = transistor_function.Lc_Vbe(exp_y1);
      auto Ic_Vbc = transistor_function.Lc_Vbc(exp_y1);

      auto f1 = Ib + Ic + ickeq - y1(0) * (Rk1 + Ck);
      auto f2 = icoeq + (y1(1) + y1(2)) * Ro + y1(1) * Co;
      auto f3 = Ic + (y1(1) + y1(2)) * Ro + (y1(2) - VBias) * Rp;
      auto f4 = Ib + icgeq + y1(3) * Rg2 + (y1(3) - VBias) * Rg1 + (y1(3) - input[0][i]) * Cg;
      auto f5 = DataType(0);

      Vector F;
      F << f1,
        f2,
        f3,
        f4,
        f5;

      Matrix M;
      M << -(Ib_Vbe + Ic_Vbe) - (Rk1 + Ck), 0, -(Ib_Vbc + Ic_Vbc), (Ib_Vbe + Ic_Vbe + Ib_Vbc + Ic_Vbc), 0,
        0, Ro + Co, Ro, 0, 0,
        -Ic_Vbe, Ro, -Ic_Vbc + Ro + Rp, (Ic_Vbe + Ic_Vbc), 0,
        -Ib_Vbe, 0, -Ib_Vbc, (Ib_Vbc + Ib_Vbe) + Rg2 + Rg1 + Cg, 0,
        0, 0, 0, 0, 0;

      return M.inverse() * F;
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
 
    TransistorFunction<DataType_>& transistor_function;
  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 3, 1> Vector;
    typedef Eigen::Matrix<DataType, 3, 3> Matrix;

    TransistorClassAInitialFunction(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk, DataType VBias, TransistorFunction<DataType_>& transistor_function)
      :Rp(Rp), Rg1(Rg1), Rg2(Rg2), Ro(Ro), Rk(Rk), VBias(VBias), transistor_function(transistor_function)
    {
    }

    Vector operator()(const Vector& y1)
    {
      std::pair<DataType, DataType> exp_y1 = std::make_pair(fmath::exp((y1(2) - y1(1)) / transistor_function.Vt), fmath::exp((y1(2) - y1(0)) / transistor_function.Vt));

      auto Ib = transistor_function.Lb(exp_y1);
      auto Ic = transistor_function.Lc(exp_y1);

      auto Ib_Vbe = transistor_function.Lb_Vbe(exp_y1);
      auto Ib_Vbc = transistor_function.Lb_Vbc(exp_y1);

      auto Ic_Vbe = transistor_function.Lc_Vbe(exp_y1);
      auto Ic_Vbc = transistor_function.Lc_Vbc(exp_y1);

      auto R = 1 / (1 / Rg1 + 1 / Rg2);
      Vector F(y1(0) - VBias + Ic * Rp,
       y1(1) - (Ib + Ic) * Rk,
       Ib * R + y1(2) - VBias / Rg1 * R);
      
      Matrix M;
      M << 1 - Ic_Vbc * Rp, -Ic_Vbe * Rp, (Ic_Vbe + Ic_Vbc) * Rp,
        (Ib_Vbc + Ic_Vbc) * Rk, 1 + (Ib_Vbe + Ic_Vbe + Ib_Vbc + Ic_Vbc) * Rk, -(Ib_Vbe + Ic_Vbe + Ib_Vbc + Ic_Vbc) * Rk,
        -Ib_Vbc * R, -Ib_Vbe * R, 1 + (Ib_Vbe + Ib_Vbc) * R;

      return M.inverse() * F;
    }
  };

  template <typename DataType>
  FollowerTransistorClassAFilter<DataType>::FollowerTransistorClassAFilter(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk1, DataType Rk2, DataType VBias, DataType Cg, DataType Co, DataType Ck, TransistorFunction<DataType>&& transistor_function)
    :Parent(1, 5), Rp(Rp), Rg1(Rg1), Rg2(Rg2), Ro(Ro), Rk1(Rk1), Rk2(Rk2), VBias(VBias), Cg(Cg), Co(Co), Ck(Ck), transistor_function(std::move(transistor_function))
  {
    input_delay = output_delay = 1;
  }

  template <typename DataType>
  FollowerTransistorClassAFilter<DataType>::FollowerTransistorClassAFilter(FollowerTransistorClassAFilter&& other)
    :Parent(std::move(other)), Rp(other.Rp), Rg1(other.Rg1), Rg2(other.Rg2), Ro(other.Ro), Rk1(other.Rk1), Rk2(other.Rk2), VBias(other.VBias), Cg(other.Cg), Co(other.Co), Ck(other.Ck), transistor_function(std::move(other.transistor_function))
  {
  }

  template <typename DataType>
  FollowerTransistorClassAFilter<DataType>::~FollowerTransistorClassAFilter()
  {
  }

  template<typename DataType_>
  void FollowerTransistorClassAFilter<DataType_>::setup()
  {
    Parent::setup();
    optimizer.reset(new VectorizedNewtonRaphson<TransistorClassAFunction, 5, nb_max_iter, true>(TransistorClassAFunction(static_cast<DataType>(1. / input_sampling_rate),
      Rp, Rg1, Rg2, Ro, Rk1, Rk2, //R
      VBias, // VBias
      Cg, Co, Ck, // C
      transistor_function, // transistor
      default_output)));
  }

  template<typename DataType_>
  void FollowerTransistorClassAFilter<DataType_>::full_setup()
  {
    // setup default_output
    SimplifiedVectorizedNewtonRaphson<TransistorClassAInitialFunction<DataType_>, 3, 10> custom(TransistorClassAInitialFunction<DataType_>(
      Rp, Rg1, Rg2, Ro, Rk1, //R
      VBias, // VBias
      transistor_function // transistor
      ));

    auto stable = custom.optimize();

    default_output[0] = 0;
    default_output[1] = stable(1);
    default_output[2] = -stable(0);
    default_output[3] = stable(0);
    default_output[4] = stable(2);

    Parent::full_setup();
  }

  template<typename DataType_>
  void FollowerTransistorClassAFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(input_sampling_rate == output_sampling_rate);

    for (int64_t i = 0; i < size; ++i)
    {
      optimizer->optimize(i, converted_inputs.data(), outputs.data());
      optimizer->get_function().update_state(i, converted_inputs.data(), outputs.data());
    }
  }

  template<typename DataType_>
  FollowerTransistorClassAFilter<DataType_> FollowerTransistorClassAFilter<DataType_>::build_standard_filter()
  {
    return FollowerTransistorClassAFilter<DataType_>(10e3, 220e3, 27e3, 1.5e3, 1e3, 8, //R
      10, // VBias
      0.47e-6, 4.7e-6, 33e-6, // C
      TransistorFunction<DataType_>::build_standard_function() // transistor
      );
  }

  template class FollowerTransistorClassAFilter<float>;
  template class FollowerTransistorClassAFilter<double>;
}
