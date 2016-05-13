/**
 * \file TriodeFilter.cpp
 */

#include "KorenTriodeFunction.h"
#include "TriodeFilter.h"

#include <cassert>

#include <ATK/Utility/SimplifiedVectorizedNewtonRaphson.h>
#include <ATK/Utility/VectorizedNewtonRaphson.h>

namespace ATK
{
  template <typename DataType_, typename TriodeFunction>
  class TriodeFilter<DataType_, TriodeFunction>::CommonCathodeTriodeFunction
  {
    const DataType_ Rp;
    const DataType_ Rg;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;
    const DataType_ Co;
    const DataType_ Ck;

    DataType_ ickeq;
    DataType_ icoeq;

    TriodeFunction& tube_function;

  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 4, 1> Vector;
    typedef Eigen::Matrix<DataType, 4, 4> Matrix;
    
    CommonCathodeTriodeFunction(DataType dt, DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType VBias, DataType Co, DataType Ck, TriodeFunction& tube_function, const std::vector<DataType>& default_output)
      :Rp(Rp), Rg(Rg), Ro(Ro), Rk(Rk), VBias(VBias), Co(2 / dt * Co), Ck(2 / dt * Ck), ickeq(2 / dt * Ck * default_output[1]), icoeq(-2 / dt * Co * default_output[2]), tube_function(tube_function)
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
    
    void update_state(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      ickeq = 2 * Ck * output[1][i] - ickeq;
      icoeq = -2 * Co * output[2][i] - icoeq;
    }

    std::pair<Vector, Matrix> operator()(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output, const Vector& y1)
    {
      auto Ib = tube_function.Lb(y1(3) - y1(0), y1(2) - y1(0));
      auto Ic = tube_function.Lc(y1(3) - y1(0), y1(2) - y1(0));

      auto Ib_Vbe = tube_function.Lb_Vbe(y1(3) - y1(0), y1(2) - y1(0));
      auto Ib_Vce = tube_function.Lb_Vce(y1(3) - y1(0), y1(2) - y1(0));

      auto Ic_Vbe = tube_function.Lc_Vbe(y1(3) - y1(0), y1(2) - y1(0));
      auto Ic_Vce = tube_function.Lc_Vce(y1(3) - y1(0), y1(2) - y1(0));

      auto f1 = Ib + Ic + ickeq - y1(0) * (1/Rk + Ck);
      auto f2 = icoeq + (y1(1) + y1(2)) / Ro + y1(1) * Co;

      auto g1 = y1(2) + Rp * (Ic + (y1(1) + y1(2)) / Ro) - VBias;
      auto g2 = y1(3) - input[0][i] + Rg * Ib;
      
      Vector F(Vector::Zero());
      F << f1,
           f2,
           g1,
           g2;

      Matrix M(Matrix::Zero());
      M << -(Ib_Vbe + Ic_Vbe + Ib_Vce + Ic_Vce) - (1/Rk + Ck), 0, (Ib_Vce + Ic_Vce), (Ib_Vbe + Ic_Vbe),
            0, 1/Ro + Co, 1/Ro, 0,
            -Rp * (Ic_Vbe + Ic_Vce), Rp / Ro, 1 + Rp / Ro + Rp * Ic_Vce, Rp * Ic_Vbe,
            -Rg * (Ib_Vbe + Ib_Vce), 0, Rg * Ib_Vce, Rg * Ib_Vbe + 1;
      
      return std::make_pair(F, M);
    }

  };
  
  template <typename DataType_, typename TriodeFunction>
  class CommonCathodeTriodeInitialFunction
  {
    const DataType_ Rp;
    const DataType_ Rg;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;

    TriodeFunction& tube_function;

  public:
    typedef DataType_ DataType;
    typedef Eigen::Matrix<DataType, 3, 1> Vector;
    typedef Eigen::Matrix<DataType, 3, 3> Matrix;

    CommonCathodeTriodeInitialFunction(DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType VBias, TriodeFunction& tube_function)
      :Rp(Rp), Rg(Rg), Ro(Ro), Rk(Rk), VBias(VBias), tube_function(tube_function)
    {
    }

    std::pair<Vector, Matrix> operator()(const Vector& y1)
    {
      auto Ib = tube_function.Lb(y1(1) - y1(2), y1(0) - y1(2));
      auto Ic = tube_function.Lc(y1(1) - y1(2), y1(0) - y1(2));

      auto Ib_Vbe = tube_function.Lb_Vbe(y1(1) - y1(2), y1(0) - y1(2));
      auto Ib_Vce = tube_function.Lb_Vce(y1(1) - y1(2), y1(0) - y1(2));

      auto Ic_Vbe = tube_function.Lc_Vbe(y1(1) - y1(2), y1(0) - y1(2));
      auto Ic_Vce = tube_function.Lc_Vce(y1(1) - y1(2), y1(0) - y1(2));

      Vector F(Vector::Zero());
      F << y1(0) - VBias + Ic * Rp,
        Ib * Rg + y1(1),
        y1(2) - (Ib + Ic) * Rk;

      Matrix M(Matrix::Zero());
      M << 1 + Rp * Ic_Vce, Rp * Ic_Vbe, -Rp * (Ic_Vbe + Ic_Vce),
        Ib_Vce * Rg, 1 + Rg * Ib_Vbe, -Rg * (Ib_Vbe + Ib_Vce),
        -(Ic_Vce + Ib_Vce) * Rk, -(Ic_Vbe + Ib_Vbe) * Rk, 1 + (Ic_Vbe + Ic_Vce + Ib_Vbe + Ib_Vce) * Rk;

      return std::make_pair(F, M);
    }
  };

  template <typename DataType, typename TriodeFunction>
  TriodeFilter<DataType, TriodeFunction>::TriodeFilter(DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType VBias, DataType Co, DataType Ck, TriodeFunction&& tube_function)
  :Parent(1, 5), Rp(Rp), Rg(Rg), Ro(Ro), Rk(Rk), VBias(VBias), Co(Co), Ck(Ck), tube_function(std::move(tube_function))
  {
    input_delay = output_delay = 1;
  }

  template <typename DataType, typename TriodeFunction>
  TriodeFilter<DataType, TriodeFunction>::TriodeFilter(TriodeFilter&& other)
  :Parent(std::move(other)), Rp(other.Rp), Rg(other.Rg), Ro(other.Ro), Rk(other.Rk), VBias(other.VBias), Co(other.Co), Ck(other.Ck), tube_function(std::move(other.tube_function))
  {
  }

  template<typename DataType,  typename TriodeFunction>
  TriodeFilter<DataType, TriodeFunction>::~TriodeFilter()
  {
  }

  template<typename DataType,  typename TriodeFunction>
  void TriodeFilter<DataType, TriodeFunction>::setup()
  {
    Parent::setup();
    optimizer.reset(new VectorizedNewtonRaphson<CommonCathodeTriodeFunction, 4, 10, true>(CommonCathodeTriodeFunction(static_cast<DataType>(1. / input_sampling_rate),
      Rp, Rg, Ro, Rk, //R
      VBias, // VBias
      Co, Ck, // C
      tube_function, // tube
      default_output)));
  }

  template<typename DataType, typename TriodeFunction>
  void TriodeFilter<DataType, TriodeFunction>::full_setup()
  {
    Eigen::Matrix<DataType, 3, 1> y0;
    y0 << VBias, 0, 0;
    
    // setup default_output
    SimplifiedVectorizedNewtonRaphson<CommonCathodeTriodeInitialFunction<DataType, TriodeFunction>, 3, 20> custom(CommonCathodeTriodeInitialFunction<DataType, TriodeFunction>(
      Rp, Rg, Ro, Rk, //R
      VBias, // VBias
      tube_function // tube
      ), y0);

    auto stable = custom.optimize();

    default_output[0] = 0;
    default_output[1] = stable(2);
    default_output[2] = -stable(0);
    default_output[3] = stable(0);
    default_output[4] = stable(1);

    Parent::full_setup();
  }

  template<typename DataType, typename TriodeFunction>
  void TriodeFilter<DataType, TriodeFunction>::process_impl(int64_t size) const
  {
    assert(input_sampling_rate == output_sampling_rate);

    for(int64_t i = 0; i < size; ++i)
    {
      optimizer->optimize(i, converted_inputs.data(), outputs.data() + 1);
      outputs[0][i] = outputs[2][i] + outputs[3][i];
      optimizer->get_function().update_state(i, converted_inputs.data(), outputs.data());
    }
  }

  template<typename DataType, typename TriodeFunction>
  TriodeFilter<DataType, TriodeFunction> TriodeFilter<DataType, TriodeFunction>::build_standard_filter()
  {
    return TriodeFilter<DataType, TriodeFunction>(200e3, 220e3, 220e3, 1e3, //R
      300, // VBias
      22e-9, 1e-6, // C
      TriodeFunction(100, 1.73e-6, 600, 300, 1060, 1.4) // tube
      );
  }

  template class TriodeFilter<float, KorenTriodeFunction<float> >;
  template class TriodeFilter<double, KorenTriodeFunction<double> >;
}
