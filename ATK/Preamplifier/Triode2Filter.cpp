/**
 * \file Triode2Filter.cpp
 */

#include <ATK/Preamplifier/DempwolfTriodeFunction.h>
#include <ATK/Preamplifier/EnhancedKorenTriodeFunction.h>
#include <ATK/Preamplifier/KorenTriodeFunction.h>
#include <ATK/Preamplifier/LeachTriodeFunction.h>
#include <ATK/Preamplifier/MunroPiazzaTriodeFunction.h>
#include <ATK/Preamplifier/ModifiedMunroPiazzaTriodeFunction.h>
#include <ATK/Preamplifier/Triode2Filter.h>
#include <ATK/Utility/SimplifiedVectorizedNewtonRaphson.h>
#include <ATK/Utility/VectorizedNewtonRaphson.h>

#include <cassert>

namespace ATK
{
  template <typename DataType_, typename TriodeFunction>
  class Triode2Filter<DataType_, TriodeFunction>::CommonCathodeTriode2Function
  {
    const DataType_ Rp;
    const DataType_ Rg;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ Vbias;
    const DataType_ Co;
    const DataType_ Ck;
    const DataType_ Cpg;

    DataType_ ickeq;
    DataType_ icoeq;
    DataType_ icpgeq;

    TriodeFunction& tube_function;

  public:
    using DataType = DataType_;
    using Vector = Eigen::Matrix<DataType, 4, 1>;
    using Matrix = Eigen::Matrix<DataType, 4, 4>;

    template<typename T>
    CommonCathodeTriode2Function(DataType dt, DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType Vbias, DataType Co, DataType Ck, TriodeFunction& tube_function, const T& default_output)
      :Rp(1/Rp), Rg(1/Rg), Ro(1/Ro), Rk(1/Rk), Vbias(Vbias), Co(2 / dt * Co), Ck(2 / dt * Ck), Cpg(2 / dt * tube_function.Cpg), ickeq(2 / dt * Ck * default_output[1]), icoeq(-2 / dt * Co * default_output[2]), icpgeq(Cpg * (default_output[3] - default_output[4]) ), tube_function(tube_function)
    {
    }

    Vector estimate(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      return id_estimate(i, input, output);
    }
    
    Vector id_estimate(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      Vector y0 = Vector::Zero();
      for (int j = 0; j < 4; ++j)
      {
        y0.data()[j] = output[j][i - 1];
      }
      
      return y0;
    }
    
    void update_state(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      ickeq = 2 * Ck * output[1][i] - ickeq;
      icoeq = -2 * Co * output[2][i] - icoeq;
      icpgeq = 2 * Cpg * (output[3][i] - output[4][i]) - icpgeq;
    }

    Vector operator()(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output, const Vector& y1)
    {
      auto Ib = tube_function.Lb(y1(3) - y1(0), y1(2) - y1(0));
      auto Ic = tube_function.Lc(y1(3) - y1(0), y1(2) - y1(0));

      auto Ib_Vbe = tube_function.Lb_Vbe(y1(3) - y1(0), y1(2) - y1(0));
      auto Ib_Vce = tube_function.Lb_Vce(y1(3) - y1(0), y1(2) - y1(0));

      auto Ic_Vbe = tube_function.Lc_Vbe(y1(3) - y1(0), y1(2) - y1(0));
      auto Ic_Vce = tube_function.Lc_Vce(y1(3) - y1(0), y1(2) - y1(0));

      auto f1 = Ib + Ic + ickeq - y1(0) * (Rk + Ck);
      auto f2 = icoeq + (y1(1) + y1(2)) * Ro + y1(1) * Co;

      auto g1 = (y1(2) - Vbias) * Rp + (Ic + (y1(1) + y1(2)) * Ro) + (y1(2) - y1(3)) * Cpg - icpgeq;
      auto g2 = (y1(3) - input[0][i]) * Rg + Ib + icpgeq - (y1(2) - y1(3)) * Cpg;
      
      Vector F(f1,
           f2,
           g1,
           g2);

      Matrix M;
      M << -(Ib_Vbe + Ic_Vbe + Ib_Vce + Ic_Vce) - (Rk + Ck), 0, (Ib_Vce + Ic_Vce), (Ib_Vbe + Ic_Vbe),
            0, Ro + Co, Ro, 0,
      -(Ic_Vbe + Ic_Vce), Ro, Rp + Ro + Ic_Vce + Cpg, Ic_Vbe - Cpg,
            -(Ib_Vbe + Ib_Vce), 0, Ib_Vce - Cpg, Ib_Vbe + Rg + Cpg;

      return M.inverse() * F;
    }

  };
  
  template <typename DataType_, typename TriodeFunction>
  class CommonCathodeTriode2InitialFunction
  {
    const DataType_ Rp;
    const DataType_ Rg;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ Vbias;

    TriodeFunction& tube_function;

  public:
    using DataType = DataType_;
    using Vector = Eigen::Matrix<DataType, 3, 1>;
    using Matrix = Eigen::Matrix<DataType, 3, 3>;

    CommonCathodeTriode2InitialFunction(DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType Vbias, TriodeFunction& tube_function)
      :Rp(Rp), Rg(Rg), Ro(Ro), Rk(Rk), Vbias(Vbias), tube_function(tube_function)
    {
    }

    Vector operator()(const Vector& y1)
    {
      auto Ib = tube_function.Lb(y1(1) - y1(2), y1(0) - y1(2));
      auto Ic = tube_function.Lc(y1(1) - y1(2), y1(0) - y1(2));

      auto Ib_Vbe = tube_function.Lb_Vbe(y1(1) - y1(2), y1(0) - y1(2));
      auto Ib_Vce = tube_function.Lb_Vce(y1(1) - y1(2), y1(0) - y1(2));

      auto Ic_Vbe = tube_function.Lc_Vbe(y1(1) - y1(2), y1(0) - y1(2));
      auto Ic_Vce = tube_function.Lc_Vce(y1(1) - y1(2), y1(0) - y1(2));

      Vector F(y1(0) - Vbias + Ic * Rp,
        Ib * Rg + y1(1),
        y1(2) - (Ib + Ic) * Rk);

      Matrix M;
      M << 1 + Rp * Ic_Vce, Rp * Ic_Vbe, -Rp * (Ic_Vbe + Ic_Vce),
        Ib_Vce * Rg, 1 + Rg * Ib_Vbe, -Rg * (Ib_Vbe + Ib_Vce),
        -(Ic_Vce + Ib_Vce) * Rk, -(Ic_Vbe + Ib_Vbe) * Rk, 1 + (Ic_Vbe + Ic_Vce + Ib_Vbe + Ib_Vce) * Rk;

      return M.inverse() * F;
    }
  };

  template <typename DataType, typename TriodeFunction>
  Triode2Filter<DataType, TriodeFunction>::Triode2Filter(DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType Vbias, DataType Co, DataType Ck, TriodeFunction&& tube_function)
  :Parent(1, 5), Rp(Rp), Rg(Rg), Ro(Ro), Rk(Rk), Vbias(Vbias), Co(Co), Ck(Ck), tube_function(std::move(tube_function))
  {
    input_delay = output_delay = 1;
  }

  template <typename DataType, typename TriodeFunction>
  Triode2Filter<DataType, TriodeFunction>::Triode2Filter(Triode2Filter&& other)
  :Parent(std::move(other)), Rp(other.Rp), Rg(other.Rg), Ro(other.Ro), Rk(other.Rk), Vbias(other.Vbias), Co(other.Co), Ck(other.Ck), tube_function(std::move(other.tube_function))
  {
  }

  template<typename DataType,  typename TriodeFunction>
  Triode2Filter<DataType, TriodeFunction>::~Triode2Filter()
  {
  }

  template<typename DataType,  typename TriodeFunction>
  void Triode2Filter<DataType, TriodeFunction>::setup()
  {
    Parent::setup();
    optimizer = std::make_unique<VectorizedNewtonRaphson<CommonCathodeTriode2Function, 4, iterations, true>>(CommonCathodeTriode2Function(static_cast<DataType>(1. / input_sampling_rate),
      Rp, Rg, Ro, Rk, //R
      Vbias, // Vbias
      Co, Ck, // C
      tube_function, // tube
      default_output));
  }

  template<typename DataType, typename TriodeFunction>
  void Triode2Filter<DataType, TriodeFunction>::full_setup()
  {
    Eigen::Matrix<DataType, 3, 1> y0;
    y0 << Vbias, 0, 0;
    
    // setup default_output
    SimplifiedVectorizedNewtonRaphson<CommonCathodeTriode2InitialFunction<DataType, TriodeFunction>, 3, 20> custom(CommonCathodeTriode2InitialFunction<DataType, TriodeFunction>(
      Rp, Rg, Ro, Rk, //R
      Vbias, // Vbias
      tube_function // tube
      ), std::move(y0));

    auto stable = custom.optimize();

    default_output[0] = 0;
    default_output[1] = stable(2);
    default_output[2] = -stable(0);
    default_output[3] = stable(0);
    default_output[4] = stable(1);

    Parent::full_setup();
  }

  template<typename DataType, typename TriodeFunction>
  void Triode2Filter<DataType, TriodeFunction>::process_impl(gsl::index size) const
  {
    assert(input_sampling_rate == output_sampling_rate);

    for(gsl::index i = 0; i < size; ++i)
    {
      optimizer->optimize(i, converted_inputs.data(), outputs.data() + 1);
      outputs[0][i] = outputs[2][i] + outputs[3][i];
      optimizer->get_function().update_state(i, converted_inputs.data(), outputs.data());
    }
  }

  template<typename DataType, typename TriodeFunction>
  Triode2Filter<DataType, TriodeFunction> Triode2Filter<DataType, TriodeFunction>::build_standard_filter(DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType Vbias, DataType Co, DataType Ck, TriodeFunction function)
  {
    return Triode2Filter<DataType, TriodeFunction>(Rp, Rg, Ro, Rk, //R
                                                  Vbias, // Vbias
                                                  Co, Ck, // C
                                                  std::move(function) // tube
                                                  );
  }

#if ATK_ENABLE_INSTANTIATION
  template class Triode2Filter<float, LeachTriodeFunction<float> >;
  template class Triode2Filter<float, KorenTriodeFunction<float> >;
  template class Triode2Filter<float, EnhancedKorenTriodeFunction<float> >;
  template class Triode2Filter<float, MunroPiazzaTriodeFunction<float> >;
  template class Triode2Filter<float, ModifiedMunroPiazzaTriodeFunction<float> >;
  template class Triode2Filter<float, DempwolfTriodeFunction<float> >;
#endif
  template class Triode2Filter<double, LeachTriodeFunction<double> >;
  template class Triode2Filter<double, KorenTriodeFunction<double> >;
  template class Triode2Filter<double, EnhancedKorenTriodeFunction<double> >;
  template class Triode2Filter<double, MunroPiazzaTriodeFunction<double> >;
  template class Triode2Filter<double, ModifiedMunroPiazzaTriodeFunction<double> >;
  template class Triode2Filter<double, DempwolfTriodeFunction<double> >;
}
