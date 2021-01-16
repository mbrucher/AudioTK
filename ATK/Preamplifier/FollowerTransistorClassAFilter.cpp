/**
* \file FollowerTransistorClassAFilter.cpp
*/

#include <ATK/Preamplifier/FollowerTransistorClassAFilter.h>
#include <ATK/Preamplifier/TransistorFunction.h>
#include <ATK/Utility/fmath.h>
#include <ATK/Utility/SimplifiedVectorizedNewtonRaphson.h>
#include <ATK/Utility/VectorizedNewtonRaphson.h>

namespace
{
  static constexpr size_t vector_size = 5;
}

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
    const DataType_ Vbias;
    const DataType_ Cg;
    const DataType_ Co;
    const DataType_ Ck;

    DataType_ ickeq;
    DataType_ icgeq;
    DataType_ icoeq;

    TransistorFunction<DataType_>& transistor_function_1;
    TransistorFunction<DataType_>& transistor_function_2;
  public:
    using DataType = DataType_;
    using Vector = Eigen::Matrix<DataType, vector_size, 1>;
    using Matrix = Eigen::Matrix<DataType, vector_size, vector_size>;

    std::pair<DataType, DataType> exp_y0;
  
    template<typename T>
    TransistorClassAFunction(DataType dt, DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk1, DataType Rk2, DataType Vbias, DataType Cg, DataType Co, DataType Ck, TransistorFunction<DataType_>& transistor_function_1, TransistorFunction<DataType_>& transistor_function_2, const T& default_output)
      :Rp(1 / Rp), Rg1(1 / Rg1), Rg2(1 / Rg2), Ro(1 / Ro), Rk1(1 / Rk1), Rk2(1 / Rk2), Vbias(Vbias), Cg(2 / dt * Cg), Co(2 / dt * Co), Ck(2 / dt * Ck), ickeq(2 / dt * Ck * default_output[1]), icgeq(2 / dt * -Cg * default_output[3]), icoeq(2 / dt * Co * (default_output[0] - default_output[4])), transistor_function_1(transistor_function_1), transistor_function_2(transistor_function_2)
    {
    }

    Vector estimate(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      return id_estimate(i, input, output);
    }

    Vector id_estimate(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      Vector y0 = Vector::Zero();
      for (int j = 0; j < vector_size; ++j)
      {
        y0.data()[j] = output[j][i - 1];
      }

      return y0;
    }

    void update_state(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      ickeq = 2 * Ck * output[1][i] - ickeq;
      icgeq = 2 * Cg * (input[0][i] - output[3][i]) - icgeq;
      icoeq = 2 * Co * (output[0][i] - output[4][i]) - icoeq;
    }

    Vector operator()(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output, const Vector& y1)
    {
      std::pair<DataType, DataType> exp_y1 = std::make_pair(fmath::exp((y1(3) - y1(1)) / transistor_function_1.Vt), fmath::exp((y1(3) - y1(2)) / transistor_function_1.Vt));

      auto Ib1 = transistor_function_1.Lb(exp_y1);
      auto Ic1 = transistor_function_1.Lc(exp_y1);

      auto Ib1_Vbe = transistor_function_1.Lb_Vbe(exp_y1);
      auto Ib1_Vbc = transistor_function_1.Lb_Vbc(exp_y1);

      auto Ic1_Vbe = transistor_function_1.Lc_Vbe(exp_y1);
      auto Ic1_Vbc = transistor_function_1.Lc_Vbc(exp_y1);

      std::pair<DataType, DataType> exp_y2 = std::make_pair(fmath::exp((y1(2) - y1(4)) / transistor_function_2.Vt), fmath::exp((y1(2) - Vbias) / transistor_function_2.Vt));

      auto Ib2 = transistor_function_2.Lb(exp_y2);
      auto Ic2 = transistor_function_2.Lc(exp_y2);

      auto Ib2_Vbe = transistor_function_2.Lb_Vbe(exp_y2);
      auto Ib2_Vbc = transistor_function_2.Lb_Vbc(exp_y2);

      auto Ic2_Vbe = transistor_function_2.Lc_Vbe(exp_y2);
      auto Ic2_Vbc = transistor_function_2.Lc_Vbc(exp_y2);

      auto f1 = Ib1 + icgeq + y1(3) * Rg2 + (y1(3) - Vbias) * Rg1 + (y1(3) - input[0][i]) * Cg;
      auto f2 = Ib1 + Ic1 + ickeq - y1(1) * (Rk1 + Ck);
      auto f3 = Ic1 + Ib2 + (y1(2) - Vbias) * Rp;
      auto f4 = Ib2 + Ic2 - icoeq - y1(4) * (Co + Rk2) + y1(0) * Co;
      auto f5 = y1(0) * Ro - icoeq + (y1(0) - y1(4)) * Co;

      auto a10 = -Ib1_Vbe - Ib1_Vbc;
      auto a20 = Ib1_Vbc;
      auto a30 = Ib1_Vbc + Rg2 + Rg1 + Cg;
      auto a11 = -Ib1_Vbe - Ib1_Vbc - Ic1_Vbe - Ic1_Vbc - (Rk1 + Ck);
      auto a21 = Ib1_Vbc + Ic1_Vbc;
      auto a31 = Ib1_Vbe + Ic1_Vbe;
      auto a12 = -Ic1_Vbe;
      auto a22 = -Ic1_Vbc + Ib2_Vbe + Ib2_Vbc + Rp;
      auto a32 = Ic1_Vbe;
      auto a42 = -Ib2_Vbe;
      auto a03 = Co;
      auto a23 = Ib2_Vbe + Ib2_Vbc + Ic2_Vbe + Ic2_Vbc;
      auto a43 = -Co - Rk2 - Ib2_Vbe - Ic2_Vbe;
      auto a04 = Ro + Co;
      auto a44 = -Co;

      auto invdet = 1 / (-a03*a10*a21*a32*a44 + a03*a10*a22*a31*a44 + a03*a11*a20*a32*a44 - a03*a11*a22*a30*a44 - a03*a12*a20*a31*a44 + a03*a12*a21*a30*a44 + a04*a10*a21*a32*a43 - a04*a10*a22*a31*a43 + a04*a10*a23*a31*a42 - a04*a11*a20*a32*a43 + a04*a11*a22*a30*a43 - a04*a11*a23*a30*a42 + a04*a12*a20*a31*a43 - a04*a12*a21*a30*a43);

      Vector F;
      F << f1, f2, f3, f4, f5;

      Matrix M;
      M << a23*a44*(-a11*a32 + a12*a31), a23*a44*(a10*a32 - a12*a30), a23*a44*(-a10*a31 + a11*a30), a44*(-a10*a21*a32 + a10*a22*a31 + a11*a20*a32 - a11*a22*a30 - a12*a20*a31 + a12*a21*a30), a10*a21*a32*a43 - a10*a22*a31*a43 + a10*a23*a31*a42 - a11*a20*a32*a43 + a11*a22*a30*a43 - a11*a23*a30*a42 + a12*a20*a31*a43 - a12*a21*a30*a43,
        -a03*a21*a32*a44 + a03*a22*a31*a44 + a04*a21*a32*a43 - a04*a22*a31*a43 + a04*a23*a31*a42, a03*a20*a32*a44 - a03*a22*a30*a44 - a04*a20*a32*a43 + a04*a22*a30*a43 - a04*a23*a30*a42, -a03*a20*a31*a44 + a03*a21*a30*a44 + a04*a20*a31*a43 - a04*a21*a30*a43, a04*a42*(-a20*a31 + a21*a30), a03*a42*(a20*a31 - a21*a30),
        a03*a11*a32*a44 - a03*a12*a31*a44 - a04*a11*a32*a43 + a04*a12*a31*a43, -a03*a10*a32*a44 + a03*a12*a30*a44 + a04*a10*a32*a43 - a04*a12*a30*a43, a03*a10*a31*a44 - a03*a11*a30*a44 - a04*a10*a31*a43 + a04*a11*a30*a43, a04*a42*(a10*a31 - a11*a30), a03*a42*(-a10*a31 + a11*a30),
        -a03*a11*a22*a44 + a03*a12*a21*a44 + a04*a11*a22*a43 - a04*a11*a23*a42 - a04*a12*a21*a43, a03*a10*a22*a44 - a03*a12*a20*a44 - a04*a10*a22*a43 + a04*a10*a23*a42 + a04*a12*a20*a43, -a03*a10*a21*a44 + a03*a11*a20*a44 + a04*a10*a21*a43 - a04*a11*a20*a43, a04*a42*(-a10*a21 + a11*a20), a03*a42*(a10*a21 - a11*a20),
        a04*a23*(a11*a32 - a12*a31), a04*a23*(-a10*a32 + a12*a30), a04*a23*(a10*a31 - a11*a30), a04*(a10*a21*a32 - a10*a22*a31 - a11*a20*a32 + a11*a22*a30 + a12*a20*a31 - a12*a21*a30), a03*(-a10*a21*a32 + a10*a22*a31 + a11*a20*a32 - a11*a22*a30 - a12*a20*a31 + a12*a21*a30);

      return M * F * invdet;
    }
  };

  template <typename DataType_>
  class TransistorClassAInitialFunction
  {
    const DataType_ Rp;
    const DataType_ Rg1;
    const DataType_ Rg2;
    const DataType_ Ro;
    const DataType_ Rk1;
    const DataType_ Rk2;
    const DataType_ Vbias;

    TransistorFunction<DataType_>& transistor_function_1;
    TransistorFunction<DataType_>& transistor_function_2;
  public:
    using DataType = DataType_;
    using Vector = Eigen::Matrix<DataType, 4, 1>;
    using Matrix = Eigen::Matrix<DataType, 4, 4>;

    TransistorClassAInitialFunction(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk1, DataType Rk2, DataType Vbias, TransistorFunction<DataType_>& transistor_function_1, TransistorFunction<DataType_>& transistor_function_2)
      :Rp(1 / Rp), Rg1(1 / Rg1), Rg2(1 / Rg2), Ro(1 / Ro), Rk1(1 / Rk1), Rk2(1 / Rk2), Vbias(Vbias), transistor_function_1(transistor_function_1), transistor_function_2(transistor_function_2)
    {
    }

    Vector operator()(const Vector& y1)
    {
      std::pair<DataType, DataType> exp_y1 = std::make_pair(fmath::exp((y1(2) - y1(0)) / transistor_function_1.Vt), fmath::exp((y1(2) - y1(1)) / transistor_function_1.Vt));

      auto Ib1 = transistor_function_1.Lb(exp_y1);
      auto Ic1 = transistor_function_1.Lc(exp_y1);

      auto Ib1_Vbe = transistor_function_1.Lb_Vbe(exp_y1);
      auto Ib1_Vbc = transistor_function_1.Lb_Vbc(exp_y1);

      auto Ic1_Vbe = transistor_function_1.Lc_Vbe(exp_y1);
      auto Ic1_Vbc = transistor_function_1.Lc_Vbc(exp_y1);

      std::pair<DataType, DataType> exp_y2 = std::make_pair(fmath::exp((y1(1) - y1(3)) / transistor_function_2.Vt), fmath::exp((y1(1) - Vbias) / transistor_function_2.Vt));

      auto Ib2 = transistor_function_2.Lb(exp_y2);
      auto Ic2 = transistor_function_2.Lc(exp_y2);

      auto Ib2_Vbe = transistor_function_2.Lb_Vbe(exp_y2);
      auto Ib2_Vbc = transistor_function_2.Lb_Vbc(exp_y2);

      auto Ic2_Vbe = transistor_function_2.Lc_Vbe(exp_y2);
      auto Ic2_Vbc = transistor_function_2.Lc_Vbc(exp_y2);

      auto f1 = Ib1 + Ic1 - y1(0) * Rk1;
      auto f2 = Ic1 + Ib2 + (y1(1) - Vbias) * Rp;
      auto f3 = Ib1 + y1(2) * Rg2 + (y1(2) - Vbias) * Rg1;
      auto f4 = Ib2 + Ic2 - y1(3) * Rk2;

      Vector F(f1,
        f2,
        f3,
        f4);

      Matrix M;
      M << -Ib1_Vbe - Ic1_Vbe - Rk1, -Ib1_Vbc - Ic1_Vbc, Ib1_Vbe + Ib1_Vbc + Ic1_Vbe + Ic1_Vbc, 0,
        -Ic1_Vbe, -Ic1_Vbc + Ib2_Vbe + Ib2_Vbc + Rp, Ic1_Vbe + Ic1_Vbc, -Ib2_Vbe,
        -Ib1_Vbe, -Ib1_Vbc, Ib1_Vbc + Ib1_Vbe + Rg2 + Rg1, 0,
        0, Ib2_Vbe + Ib2_Vbc + Ic2_Vbe + Ic2_Vbc, 0, -Rk2 - Ib2_Vbe - Ic2_Vbe;

      return M.inverse() * F;
    }
  };

  template <typename DataType>
  FollowerTransistorClassAFilter<DataType>::FollowerTransistorClassAFilter(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk1, DataType Rk2, DataType Vbias, DataType Cg, DataType Co, DataType Ck, TransistorFunction<DataType>&& transistor_function_1, TransistorFunction<DataType>&& transistor_function_2)
    :Parent(1, vector_size), Rp(Rp), Rg1(Rg1), Rg2(Rg2), Ro(Ro), Rk1(Rk1), Rk2(Rk2), Vbias(Vbias), Cg(Cg), Co(Co), Ck(Ck), transistor_function_1(std::move(transistor_function_1)), transistor_function_2(std::move(transistor_function_2))
  {
    input_delay = output_delay = 1;
  }

  template <typename DataType>
  FollowerTransistorClassAFilter<DataType>::FollowerTransistorClassAFilter(FollowerTransistorClassAFilter&& other)
    :Parent(std::move(other)), Rp(other.Rp), Rg1(other.Rg1), Rg2(other.Rg2), Ro(other.Ro), Rk1(other.Rk1), Rk2(other.Rk2), Vbias(other.Vbias), Cg(other.Cg), Co(other.Co), Ck(other.Ck), transistor_function_1(std::move(other.transistor_function_1)), transistor_function_2(std::move(other.transistor_function_2))
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
    optimizer = std::make_unique<VectorizedNewtonRaphson<TransistorClassAFunction, vector_size, nb_max_iter, true>>(TransistorClassAFunction(static_cast<DataType>(1. / input_sampling_rate),
      Rp, Rg1, Rg2, Ro, Rk1, Rk2, //R
      Vbias, // Vbias
      Cg, Co, Ck, // C
      transistor_function_1, // transistor
      transistor_function_2, // transistor
      default_output));
  }

  template<typename DataType_>
  void FollowerTransistorClassAFilter<DataType_>::full_setup()
  {
    // setup default_output
    SimplifiedVectorizedNewtonRaphson<TransistorClassAInitialFunction<DataType_>, 4, 50> custom(TransistorClassAInitialFunction<DataType_>(
      Rp, Rg1, Rg2, Ro, Rk1, Rk2, //R
      Vbias, // Vbias
      transistor_function_1, // transistor
      transistor_function_2 // transistor
      ), typename TransistorClassAInitialFunction<DataType_>::Vector(Vbias / 20, Vbias * 6 / 10, Vbias / 10, Vbias / 2));

    auto stable = custom.optimize();

    default_output[0] = 0;
    default_output[1] = stable(0);
    default_output[2] = stable(1);
    default_output[3] = stable(2);
    default_output[4] = stable(3);

    Parent::full_setup();
  }

  template<typename DataType_>
  void FollowerTransistorClassAFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(input_sampling_rate == output_sampling_rate);

    for (gsl::index i = 0; i < size; ++i)
    {
      optimizer->optimize(i, converted_inputs.data(), outputs.data());
      optimizer->get_function().update_state(i, converted_inputs.data(), outputs.data());
    }
  }

  template<typename DataType_>
  FollowerTransistorClassAFilter<DataType_> FollowerTransistorClassAFilter<DataType_>::build_standard_filter(DataType_ Rp, DataType_ Rg1, DataType_ Rg2, DataType_ Ro,
    DataType_ Rk1, DataType_ Rk2, DataType_ Vbias, DataType_ Cg, DataType_ Co, DataType_ Ck, TransistorFunction<DataType_> function1, TransistorFunction<DataType_> function2)
  {
    return FollowerTransistorClassAFilter<DataType_>(Rp, Rg1, Rg2, Ro, Rk1, Rk2, Vbias, Cg, Co, Ck,
      std::move(function1), std::move(function2));
  }

#if ATK_ENABLE_INSTANTIATION
  template class FollowerTransistorClassAFilter<float>;
#endif
  template class FollowerTransistorClassAFilter<double>;
}
