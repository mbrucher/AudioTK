/**
 * \file SimpleOverdriveFilter.cpp
 */

#include "SimpleOverdriveFilter.h"
#include <ATK/Utility/fmath.h>
#include <ATK/Utility/ScalarNewtonRaphson.h>

#include <boost/math/special_functions/sign.hpp>

namespace ATK
{
  template<typename DataType_>
  class SimpleOverdriveFilter<DataType_>::SimpleOverdriveFunction
  {
  public:
    using DataType = DataType_;
  protected:
    DataType A;
    DataType B;
    DataType is;
    DataType vt;

    DataType oldy0{0};
    DataType oldexpy0{1};
    DataType oldinvexpy0{1};
    DataType oldy1{0};
    DataType oldexpy1{1};
    DataType oldinvexpy1{1};
  public:
    SimpleOverdriveFunction(DataType dt, DataType R, DataType C, DataType is, DataType vt)
    :A(dt / (2 * C) + R), B(dt / (2 * C) - R), is(is), vt(vt)
    {
    }
    
    std::pair<DataType, DataType> operator()(const DataType* ATK_RESTRICT input, DataType* ATK_RESTRICT output, DataType y1)
    {
      auto x0 = input[-1];
      auto x1 = input[0];
      auto y0 = output[-1];
      DataType expdiode_y1_p = fmath::exp(y1 / vt);
      DataType expdiode_y1_m = 1 / expdiode_y1_p;
      DataType expdiode_y0_p;
      DataType expdiode_y0_m;
	  
	    if(y0 == oldy0)
	    {
	      expdiode_y0_p = oldexpy0;
	      expdiode_y0_m = oldinvexpy0;
	    }
	    else if(y0 == oldy1)
	    {
	      expdiode_y0_p = oldexpy1;
	      expdiode_y0_m = oldinvexpy1;
	    }
	    else
	    {
	      expdiode_y0_p = fmath::exp(y0 / vt);
	      expdiode_y0_m = 1 / expdiode_y0_p;
	    }
	  
      oldy0 = y0;
      oldexpy0 = expdiode_y0_p;
      oldinvexpy0 = expdiode_y0_m;

      oldy1 = y1;
      oldexpy1 = expdiode_y1_p;
      oldinvexpy1 = expdiode_y1_m;

      std::pair<DataType, DataType> diode = std::make_pair(is * (expdiode_y1_p - expdiode_y1_m), is * (expdiode_y1_p + expdiode_y1_m) / vt);
      return std::make_pair(A * diode.first + y1 + x0 - x1 + B * is * (expdiode_y0_p - expdiode_y0_m) - y0, A * diode.second + 1);
    }

    DataType estimate(const DataType* ATK_RESTRICT input, DataType* ATK_RESTRICT output)
    {
      auto x0 = input[-1];
      auto x1 = input[0];
      auto y0 = output[-1];
      return affine_estimate(x0, x1, y0);
    }

    DataType affine_estimate(DataType x0, DataType x1, DataType y0)
    {
      auto sinh = (oldexpy1 - oldinvexpy1);
      auto cosh = (oldexpy1 + oldinvexpy1);
      return (x1 - x0 + y0 - is * sinh * B - (sinh - y0 / vt * cosh) * is * A) / (is * cosh * A / vt + 1);
    }
  };
  
  template <typename DataType>
  SimpleOverdriveFilter<DataType>::SimpleOverdriveFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
    input_delay = 1;
    output_delay = 1;
  }

  template <typename DataType>
  SimpleOverdriveFilter<DataType>::~SimpleOverdriveFilter()
  {
  }

  template <typename DataType>
  void SimpleOverdriveFilter<DataType>::setup()
  {
    Parent::setup();
    optimizer = std::make_unique<ScalarNewtonRaphson<SimpleOverdriveFunction>>(SimpleOverdriveFunction(static_cast<DataType>(1. / input_sampling_rate),
      10000, static_cast<DataType>(22e-9), static_cast<DataType>(1e-12), static_cast<DataType>(26e-3)));
  }

  template <typename DataType>
  void SimpleOverdriveFilter<DataType>::process_impl(gsl::index size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(gsl::index i = 0; i < size; ++i)
    {
      optimizer->optimize(input + i, output + i);
    }
  }

#if ATK_ENABLE_INSTANTIATION
  template class SimpleOverdriveFilter<float>;
#endif
  template class SimpleOverdriveFilter<double>;
  }
