/**
 * \file SimpleOverdriveFilter.cpp
 */

#include "SimpleOverdriveFilter.h"

#include <boost/math/special_functions/sign.hpp>

#include <ATK/Utility/ScalarNewtonRaphson.h>

namespace ATK
{
  template<typename DataType_>
  class SimpleOverdriveFilter<DataType_>::SimpleOverdriveFunction
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
      A = dt / (2 * C) + R;
      B = dt / (2 * C) - R;

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
      return std::make_pair(A * diode.first + (y1 + (x0 - x1 + B * is * (expdiode_y0_p - expdiode_y0_m) - y0)), A * diode.second + 1);
    }

    DataType estimate(DataType x0, DataType x1, DataType y0)
    {
      return y0;
    }
  };
  
  template <typename DataType>
  SimpleOverdriveFilter<DataType>::SimpleOverdriveFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
  }

  template <typename DataType>
  SimpleOverdriveFilter<DataType>::~SimpleOverdriveFilter()
  {
  }

  template <typename DataType>
  void SimpleOverdriveFilter<DataType>::setup()
  {
    Parent::setup();
    optimizer.reset(new ScalarNewtonRaphson<SimpleOverdriveFunction>(SimpleOverdriveFunction(static_cast<DataType>(1. / input_sampling_rate),
      10000, static_cast<DataType>(22e-9), static_cast<DataType>(1e-12), static_cast<DataType>(26e-3))));
  }

  template <typename DataType>
  void SimpleOverdriveFilter<DataType>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);

    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(int64_t i = 0; i < size; ++i)
    {
      output[i] = optimizer->optimize(input[i]);
    }
  }

  template class SimpleOverdriveFilter<float>;
  template class SimpleOverdriveFilter<double>;

  template<typename DataType_>
  class BackwardSimpleOverdriveFilter<DataType_>::SimpleOverdriveFunction
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
      A = dt / C + R;
      B = - R;
      
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
      return std::make_pair(A * diode.first + (y1 + (x0 - x1 + B * is * (expdiode_y0_p - expdiode_y0_m) - y0)), A * diode.second + 1);
    }
    
    DataType estimate(DataType x0, DataType x1, DataType y0)
    {
      return y0;
    }
  };

  template <typename DataType>
  BackwardSimpleOverdriveFilter<DataType>::BackwardSimpleOverdriveFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
  }
  
  template <typename DataType>
  BackwardSimpleOverdriveFilter<DataType>::~BackwardSimpleOverdriveFilter()
  {
  }
  
  template <typename DataType>
  void BackwardSimpleOverdriveFilter<DataType>::setup()
  {
    Parent::setup();
    optimizer.reset(new ScalarNewtonRaphson<SimpleOverdriveFunction>(SimpleOverdriveFunction(static_cast<DataType>(1. / input_sampling_rate),
                                                                                             10000, static_cast<DataType>(22e-9), static_cast<DataType>(1e-12), static_cast<DataType>(26e-3))));
  }
  
  template <typename DataType>
  void BackwardSimpleOverdriveFilter<DataType>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);
    
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(int64_t i = 0; i < size; ++i)
    {
      output[i] = optimizer->optimize(input[i]);
    }
  }
  
  template class BackwardSimpleOverdriveFilter<float>;
  template class BackwardSimpleOverdriveFilter<double>;
  
  template <typename DataType>
  ForwardSimpleOverdriveFilter<DataType>::ForwardSimpleOverdriveFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
    input_delay = 1;
    output_delay = 1;
  }
  
  template <typename DataType>
  ForwardSimpleOverdriveFilter<DataType>::~ForwardSimpleOverdriveFilter()
  {
  }
  
  template <typename DataType>
  void ForwardSimpleOverdriveFilter<DataType>::setup()
  {
    Parent::setup();
  }
  
  template <typename DataType>
  void ForwardSimpleOverdriveFilter<DataType>::process_impl(int64_t size) const
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
      output[i] = output[i-1] + (input[i] - input[i-1] - (4 * dt * is * C * sinh(output[i-1] / vt))) / (1 + 2 * is * R * vt * cosh(output[i-1] / vt));
    }
  }
  
  template class ForwardSimpleOverdriveFilter<float>;
  template class ForwardSimpleOverdriveFilter<double>;

}
