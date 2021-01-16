/**
* \file TransistorClassAFilter.cpp
*/

#include <ATK/Preamplifier/TransistorClassAFilter.h>
#include <ATK/Preamplifier/TransistorFunction.h>
#include <ATK/Utility/fmath.h>
#include <ATK/Utility/SimplifiedVectorizedNewtonRaphson.h>
#include <ATK/Utility/VectorizedNewtonRaphson.h>

#include <cassert>

namespace ATK
{
  template <typename DataType_>
  class TransistorClassAFilter<DataType_>::TransistorClassAFunction
  {
    const DataType_ Rp;
    const DataType_ Rg1;
    const DataType_ Rg2;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ Vbias;
    const DataType_ Cg;
    const DataType_ Co;
    const DataType_ Ck;

    DataType_ ickeq;
    DataType_ icgeq;
    DataType_ icoeq;

    TransistorFunction<DataType_>& transistor_function;
  public:
    using DataType = DataType_;
    using Vector = Eigen::Matrix<DataType, 4, 1>;
    using Matrix = Eigen::Matrix<DataType, 4, 4>;

    std::pair<DataType, DataType> exp_y0;

    template<typename T>
    TransistorClassAFunction(DataType dt, DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk, DataType Vbias, DataType Cg, DataType Co, DataType Ck, TransistorFunction<DataType_>& transistor_function, const T& default_output)
      :Rp(1 / Rp), Rg1(1 / Rg1), Rg2(1 / Rg2), Ro(1 / Ro), Rk(1 / Rk), Vbias(Vbias), Cg(2 / dt * Cg), Co(2 / dt * Co), Ck(2 / dt * Ck), ickeq(2 / dt * Ck * default_output[1]), icgeq(2 / dt * -Cg * default_output[4]), icoeq(-2 / dt * Co * default_output[2]), transistor_function(transistor_function)
    {
    }

    Vector estimate(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      return affine_estimate(i, input, output);
    }

    Vector affine_estimate(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      std::pair<DataType, DataType> exp_y1 = std::make_pair(fmath::exp((output[3][i - 1] - output[0][i - 1]) / transistor_function.Vt), fmath::exp((output[3][i - 1] - output[2][i - 1]) / transistor_function.Vt));

      auto Ib = transistor_function.Lb(exp_y1);
      auto Ic = transistor_function.Lc(exp_y1);

      auto Ib_Vbe = transistor_function.Lb_Vbe(exp_y1);
      auto Ib_Vbc = transistor_function.Lb_Vbc(exp_y1);

      auto Ic_Vbe = transistor_function.Lc_Vbe(exp_y1);
      auto Ic_Vbc = transistor_function.Lc_Vbc(exp_y1);

      Vector y0(-ickeq - (Ib - Ib_Vbe * (output[3][i - 1] - output[0][i - 1]) - Ib_Vbc * (output[3][i - 1] - output[2][i - 1]) + Ic - Ic_Vbe * (output[3][i - 1] - output[0][i - 1]) - Ic_Vbc * (output[3][i - 1] - output[2][i - 1])),
        -icoeq,
        Vbias * Rp - (Ic - Ic_Vbe * (output[3][i - 1] - output[0][i - 1]) - Ic_Vbc * (output[3][i - 1] - output[2][i - 1])),
        input[0][i] * Cg - icgeq + Vbias * Rg1 - (Ib - Ib_Vbe * (output[3][i - 1] - output[0][i - 1]) - Ib_Vbc * (output[3][i - 1] - output[2][i - 1])));

      Matrix M;
      M << -(Ib_Vbe + Ic_Vbe) - (Rk + Ck), 0, -(Ib_Vbc + Ic_Vbc), (Ib_Vbe + Ic_Vbe + Ib_Vbc + Ic_Vbc),
        0, Ro + Co, Ro, 0,
        -Ic_Vbe, Ro, -Ic_Vbc + Ro + Rp, (Ic_Vbe + Ic_Vbc),
        -Ib_Vbe, 0, -Ib_Vbc, (Ib_Vbc + Ib_Vbe) + Rg2 + Rg1 + Cg;

      return M.inverse() * y0;
    }

    void update_state(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      ickeq = 2 * Ck * output[1][i] - ickeq;
      icgeq = 2 * Cg * (input[0][i] - output[4][i]) - icgeq;
      icoeq = -2 * Co * output[2][i] - icoeq;
    }

    Vector operator()(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output, const Vector& y1)
    {
      std::pair<DataType, DataType> exp_y1 = std::make_pair(fmath::exp((y1(3) - y1(0)) / transistor_function.Vt), fmath::exp((y1(3) - y1(2)) / transistor_function.Vt));

      auto Ib = transistor_function.Lb(exp_y1);
      auto Ic = transistor_function.Lc(exp_y1);

      auto Ib_Vbe = transistor_function.Lb_Vbe(exp_y1);
      auto Ib_Vbc = transistor_function.Lb_Vbc(exp_y1);

      auto Ic_Vbe = transistor_function.Lc_Vbe(exp_y1);
      auto Ic_Vbc = transistor_function.Lc_Vbc(exp_y1);

      auto f1 = Ib + Ic + ickeq - y1(0) * (Rk + Ck);
      auto f2 = icoeq + (y1(1) + y1(2)) * Ro + y1(1) * Co;
      auto f3 = Ic + (y1(1) + y1(2)) * Ro + (y1(2) - Vbias) * Rp;
      auto f4 = Ib + icgeq + y1(3) * Rg2 + (y1(3) - Vbias) * Rg1 + (y1(3) - input[0][i]) * Cg;

      Vector F(f1,
        f2,
        f3,
        f4);

      Matrix M;
      M << -(Ib_Vbe + Ic_Vbe) - (Rk + Ck), 0, -(Ib_Vbc + Ic_Vbc), (Ib_Vbe + Ic_Vbe + Ib_Vbc + Ic_Vbc),
        0, Ro + Co, Ro, 0,
        -Ic_Vbe, Ro, -Ic_Vbc + Ro + Rp, (Ic_Vbe + Ic_Vbc),
        -Ib_Vbe, 0, -Ib_Vbc, (Ib_Vbc + Ib_Vbe) + Rg2 + Rg1 + Cg;

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
    const DataType_ Vbias;

    TransistorFunction<DataType_>& transistor_function;
  public:
    using DataType = DataType_;
    using Vector = Eigen::Matrix<DataType, 3, 1>;
    using Matrix = Eigen::Matrix<DataType, 3, 3>;

    TransistorClassAInitialFunction(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk, DataType Vbias, TransistorFunction<DataType_>& transistor_function)
      :Rp(Rp), Rg1(Rg1), Rg2(Rg2), Ro(Ro), Rk(Rk), Vbias(Vbias), transistor_function(transistor_function)
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
      Vector F(y1(0) - Vbias + Ic * Rp,
        y1(1) - (Ib + Ic) * Rk,
        Ib * R + y1(2) - Vbias / Rg1 * R);

      Matrix M;
      M << 1 - Ic_Vbc * Rp, -Ic_Vbe * Rp, (Ic_Vbe + Ic_Vbc) * Rp,
        (Ib_Vbc + Ic_Vbc) * Rk, 1 + (Ib_Vbc + Ic_Vbc) * Rk, -(Ib_Vbe + Ic_Vbe + Ib_Vbc + Ic_Vbc) * Rk,
        -Ib_Vbc * R, -Ib_Vbe * R, 1 + (Ib_Vbe + Ib_Vbc) * R;

      return M.inverse() * F;
    }
  };

  template <typename DataType>
  TransistorClassAFilter<DataType>::TransistorClassAFilter(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk, DataType Vbias, DataType Cg, DataType Co, DataType Ck, TransistorFunction<DataType>&& transistor_function)
    :Parent(1, 5), Rp(Rp), Rg1(Rg1), Rg2(Rg2), Ro(Ro), Rk(Rk), Vbias(Vbias), Cg(Cg), Co(Co), Ck(Ck), transistor_function(std::move(transistor_function))
  {
    input_delay = output_delay = 1;
  }

  template <typename DataType>
  TransistorClassAFilter<DataType>::TransistorClassAFilter(TransistorClassAFilter&& other)
    :Parent(std::move(other)), Rp(other.Rp), Rg1(other.Rg1), Rg2(other.Rg2), Ro(other.Ro), Rk(other.Rk), Vbias(other.Vbias), Cg(other.Cg), Co(other.Co), Ck(other.Ck), transistor_function(std::move(other.transistor_function))
  {
  }

  template <typename DataType>
  TransistorClassAFilter<DataType>::~TransistorClassAFilter()
  {
  }

  template<typename DataType_>
  void TransistorClassAFilter<DataType_>::setup()
  {
    Parent::setup();
    optimizer = std::make_unique<VectorizedNewtonRaphson<TransistorClassAFunction, 4, nb_max_iter, true>>(TransistorClassAFunction(static_cast<DataType>(1. / input_sampling_rate),
      Rp, Rg1, Rg2, Ro, Rk, //R
      Vbias, // Vbias
      Cg, Co, Ck, // C
      transistor_function, // transistor
      default_output));
  }

  template<typename DataType_>
  void TransistorClassAFilter<DataType_>::full_setup()
  {
    Eigen::Matrix<DataType, 3, 1> y0;
    y0 << Vbias, 0, 0;//VBias * Rg2 / Rg1;

                      // setup default_output
    SimplifiedVectorizedNewtonRaphson<TransistorClassAInitialFunction<DataType_>, 3, 10> custom(TransistorClassAInitialFunction<DataType_>(
      Rp, Rg1, Rg2, Ro, Rk, //R
      Vbias, // VBias
      transistor_function // transistor
      ), std::move(y0));

    auto stable = custom.optimize();

    default_output[0] = 0;
    default_output[1] = stable(1);
    default_output[2] = -stable(0);
    default_output[3] = stable(0);
    default_output[4] = stable(2);

    Parent::full_setup();
  }

  template<typename DataType_>
  void TransistorClassAFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(input_sampling_rate == output_sampling_rate);

    for (gsl::index i = 0; i < size; ++i)
    {
      optimizer->optimize(i, converted_inputs.data(), outputs.data() + 1);
      outputs[0][i] = outputs[2][i] + outputs[3][i];
      optimizer->get_function().update_state(i, converted_inputs.data(), outputs.data());
    }
  }

  template<typename DataType_>
  TransistorClassAFilter<DataType_> TransistorClassAFilter<DataType_>::build_standard_filter(DataType_ Rp, DataType_ Rg1, DataType_ Rg2, DataType_ Ro,
    DataType_ Rk, DataType_ Vbias, DataType_ Cg, DataType_ Co, DataType_ Ck, TransistorFunction<DataType_> function)
  {
    return TransistorClassAFilter<DataType_>(Rp, Rg1, Rg2, Ro, Rk, Vbias, Cg, Co, Ck,
      std::move(function) // transistor
      );
  }

#if ATK_ENABLE_INSTANTIATION
  template class TransistorClassAFilter<float>;
#endif
  template class TransistorClassAFilter<double>;
}
