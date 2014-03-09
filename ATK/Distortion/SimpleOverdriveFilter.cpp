/**
 * \file SimpleOverdriveFilter.cpp
 */

#include "SimpleOverdriveFilter.h"

#include <boost/math/special_functions/sign.hpp>

#include "../Tools/ScalarNewtonRaphson.h"

namespace ATK
{
  template<typename DataType_>
  class SimpleOverdriveFunction
  {
  public:
    typedef DataType_ DataType;
  protected:
    DataType A;
    DataType B;
    DataType is;
    DataType vt;
  public:
    SimpleOverdriveFunction(DataType dt, DataType R, DataType C, DataType is, DataType vt)
    :is(is), vt(vt)
    {
      A = dt / (2 * C) + R;
      B = dt / (2 * C) - R;
    }
    
    std::pair<DataType, DataType> operator()(DataType x0, DataType x1, DataType y0, DataType y1)
    {
      DataType expdiode_y1_p = std::exp(y1 / vt);
      DataType expdiode_y1_m = std::exp(-y1 / vt);
      DataType expdiode_y0_p = std::exp(y0 / vt);
      DataType expdiode_y0_m = std::exp(-y0 / vt);
      std::pair<DataType, DataType> diode = std::make_pair(is * (expdiode_y1_p - expdiode_y1_m), is * (expdiode_y1_p - expdiode_y1_m) / vt);
      
      return std::make_pair(diode.first + 1/A * (y1 + (x0 - x1 + B * is * (expdiode_y0_p - expdiode_y0_m) - y0)), diode.second + 1/A);
    }
  };
  
  
  template <typename DataType>
  SimpleOverdriveFilter<DataType>::SimpleOverdriveFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
    optimizer.reset(new ScalarNewtonRaphson<SimpleOverdriveFunction<DataType> >(function));
  }

  template <typename DataType>
  SimpleOverdriveFilter<DataType>::~SimpleOverdriveFilter()
  {
  }

  template <typename DataType>
  void SimpleOverdriveFilter<DataType>::setup()
  {
    function.reset(new SimpleOverdriveFunction<DataType>(1/input_sampling_rate, 10000, 22e-9, 1e-12, 26e-3));
  }

  template <typename DataType>
  void SimpleOverdriveFilter<DataType>::process_impl(long size)
  {
    for(long i = 0; i < size; ++i)
    {
      outputs[0][i] = optimizer->optimize(converted_inputs[0][i]);
    }
  }

  template class SimpleOverdriveFilter<float>;
  template class SimpleOverdriveFilter<double>;
}
