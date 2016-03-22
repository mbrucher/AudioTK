/**
 * \file DiodeClipperFilter.cpp
 */

#include "DiodeClipperFilter.h"

#include <boost/math/special_functions/sign.hpp>

#include <ATK/Utility/ScalarNewtonRaphson.h>

namespace ATK
{
  template<typename DataType_>
  class DiodeClipperFilter<DataType_>::SimpleOverdriveFunction
  {
  public:
    typedef DataType_ DataType;
  protected:
    DataType A;
    DataType B;
    DataType is;
    DataType vt;

    DataType oldy0;
    DataType oldexpy0;
    DataType oldinvexpy0;
    DataType oldy1;
    DataType oldexpy1;
    DataType oldinvexpy1;
  public:
    SimpleOverdriveFunction(DataType dt, DataType R, DataType C, DataType is, DataType vt)
    :is(is), vt(vt)
    {
      A = dt / (2 * C * R);
      B = dt / (2 * C);

      oldy0 = oldy1 = 0;
      oldexpy0 = oldinvexpy0 = oldexpy1 = oldinvexpy1 = 1;
    }
    
    std::pair<DataType, DataType> operator()(DataType x0, DataType x1, DataType y0, DataType y1)
    {
      DataType expdiode_y1_p = std::exp(y1 / vt);
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
	      expdiode_y0_p = std::exp(y0 / vt);
	      expdiode_y0_m = 1 / expdiode_y0_p;
	    }
	  
      oldy0 = y0;
      oldexpy0 = expdiode_y0_p;
      oldinvexpy0 = expdiode_y0_m;

      oldy1 = y1;
      oldexpy1 = expdiode_y1_p;
      oldinvexpy1 = expdiode_y1_m;
      
      std::pair<DataType, DataType> diode = std::make_pair(is * (expdiode_y1_p - expdiode_y1_m), is * (expdiode_y1_p + expdiode_y1_m) / vt);
      auto old_diode = is * (expdiode_y0_p - expdiode_y0_m);
      return std::make_pair(y0 - y1 + 2 * A * x1 - (A * (y1 + y0) + B * (diode.first + old_diode)), -1 - A - B * diode.second);
    }
    
    DataType estimate(DataType x0, DataType x1, DataType y0)
    {
      return y0;
    }
    
    DataType linear_estimate(DataType x0, DataType x1, DataType y0)
    {
      if(y0 == 0)
        return 0;
      auto sinh = (oldexpy1 - oldinvexpy1);
      return (y0 + A * (2 * x1 - y0) - B * sinh) / (1 + A + B * sinh / y0);
    }
    
    DataType affine_estimate(DataType x0, DataType x1, DataType y0)
    {
      auto sinh = (oldexpy1 - oldinvexpy1);
      auto cosh = (oldexpy1 + oldinvexpy1);
      return (y0 + A * (2 * x1 - y0) - B * (2 * sinh - y0 / vt * cosh) ) / (B * cosh / vt + 1 + A);
    }
  };
  
  template <typename DataType>
  DiodeClipperFilter<DataType>::DiodeClipperFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
  }

  template <typename DataType>
  DiodeClipperFilter<DataType>::~DiodeClipperFilter()
  {
  }

  template <typename DataType>
  void DiodeClipperFilter<DataType>::setup()
  {
    Parent::setup();
    optimizer.reset(new ScalarNewtonRaphson<SimpleOverdriveFunction>(SimpleOverdriveFunction(static_cast<DataType>(1. / input_sampling_rate),
      10000, static_cast<DataType>(22e-9), static_cast<DataType>(1e-12), static_cast<DataType>(26e-3))));
  }

  template <typename DataType>
  void DiodeClipperFilter<DataType>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);

    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(int64_t i = 0; i < size; ++i)
    {
      output[i] = optimizer->optimize(input[i]);
    }
  }

  template class DiodeClipperFilter<float>;
  template class DiodeClipperFilter<double>;

  template<typename DataType_>
  class BackwardDiodeClipperFilter<DataType_>::SimpleOverdriveFunction
  {
  public:
    typedef DataType_ DataType;
  protected:
    DataType A;
    DataType B;
    DataType is;
    DataType vt;
    
    DataType oldy0;
    DataType oldexpy0;
    DataType oldinvexpy0;
    DataType oldy1;
    DataType oldexpy1;
    DataType oldinvexpy1;
  public:
    SimpleOverdriveFunction(DataType dt, DataType R, DataType C, DataType is, DataType vt)
    :is(is), vt(vt)
    {
      A = dt / (C * R);
      B = dt / C;
      
      oldy0 = oldy1 = 0;
      oldexpy0 = oldinvexpy0 = oldexpy1 = oldinvexpy1 = 1;
    }
    
    std::pair<DataType, DataType> operator()(DataType x0, DataType x1, DataType y0, DataType y1)
    {
      DataType expdiode_y1_p = std::exp(y1 / vt);
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
        expdiode_y0_p = std::exp(y0 / vt);
        expdiode_y0_m = 1 / expdiode_y0_p;
      }
      
      oldy0 = y0;
      oldexpy0 = expdiode_y0_p;
      oldinvexpy0 = expdiode_y0_m;
      
      oldy1 = y1;
      oldexpy1 = expdiode_y1_p;
      oldinvexpy1 = expdiode_y1_m;
      
      std::pair<DataType, DataType> diode = std::make_pair(is * (expdiode_y1_p - expdiode_y1_m), is * (expdiode_y1_p + expdiode_y1_m) / vt);
      return std::make_pair(y0 - y1 + A * x1 - (A * y1 + B * diode.first), -1 - A - B * diode.second);
    }
    
    DataType estimate(DataType x0, DataType x1, DataType y0)
    {
      return y0;
    }
    
    DataType linear_estimate(DataType x0, DataType x1, DataType y0)
    {
      if(y0 == 0)
        return 0;
      auto sinh = (oldexpy1 - oldinvexpy1);
      return (y0 + x1 * A) / (B * sinh / y0 + (1 + A));
    }
    
    DataType affine_estimate(DataType x0, DataType x1, DataType y0)
    {
      auto sinh = (oldexpy1 - oldinvexpy1);
      auto cosh = (oldexpy1 + oldinvexpy1);
      return (y0 + x1 * A - B * (sinh - y0 / vt * cosh) ) / (B * cosh / vt + 1 + A);
    }
  };

  template <typename DataType>
  BackwardDiodeClipperFilter<DataType>::BackwardDiodeClipperFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
  }
  
  template <typename DataType>
  BackwardDiodeClipperFilter<DataType>::~BackwardDiodeClipperFilter()
  {
  }
  
  template <typename DataType>
  void BackwardDiodeClipperFilter<DataType>::setup()
  {
    Parent::setup();
    optimizer.reset(new ScalarNewtonRaphson<SimpleOverdriveFunction>(SimpleOverdriveFunction(static_cast<DataType>(1. / input_sampling_rate),
                                                                                             10000, static_cast<DataType>(22e-9), static_cast<DataType>(1e-12), static_cast<DataType>(26e-3))));
  }
  
  template <typename DataType>
  void BackwardDiodeClipperFilter<DataType>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);
    
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(int64_t i = 0; i < size; ++i)
    {
      output[i] = optimizer->optimize(input[i]);
    }
  }
  
  template class BackwardDiodeClipperFilter<float>;
  template class BackwardDiodeClipperFilter<double>;
  
  template <typename DataType>
  ForwardDiodeClipperFilter<DataType>::ForwardDiodeClipperFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
    input_delay = 1;
    output_delay = 1;
  }
  
  template <typename DataType>
  ForwardDiodeClipperFilter<DataType>::~ForwardDiodeClipperFilter()
  {
  }
  
  template <typename DataType>
  void ForwardDiodeClipperFilter<DataType>::setup()
  {
    Parent::setup();
  }
  
  template <typename DataType>
  void ForwardDiodeClipperFilter<DataType>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);
    
    DataType dt = static_cast<DataType>(1. / input_sampling_rate);
    DataType R = 10000;
    DataType C = static_cast<DataType>(22e-9);
    DataType is = static_cast<DataType>(1e-12);
    DataType vt = static_cast<DataType>(26e-3);
    
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(int64_t i = 0; i < size; ++i)
    {
      output[i] = output[i-1] + dt * ((input[i] - output[i-1]) / (R * C) - (2 * is / C * sinh(output[i-1] / vt)));
    }
  }
  
  template class ForwardDiodeClipperFilter<float>;
  template class ForwardDiodeClipperFilter<double>;

}
