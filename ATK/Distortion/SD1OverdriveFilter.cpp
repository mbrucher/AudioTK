/**
 * \file SD1OverdriveFilter.cpp
 */

#include "SD1OverdriveFilter.h"

#include <boost/math/special_functions/sign.hpp>

#include "../Tools/ScalarNewtonRaphson.h"

namespace ATK
{
  template<typename DataType_>
  class SD1OverdriveFunction
  {
  public:
    typedef DataType_ DataType;
  protected:
    DataType A;
    DataType B;
    DataType R1;
    DataType Q;
    DataType drive;
    DataType is;
    DataType vt;

    DataType oldy0;
    DataType oldexpy0;
    DataType oldinvexpy0;
    DataType oldy1;
    DataType oldexpy1;
    DataType oldinvexpy1;

  public:
    SD1OverdriveFunction(DataType dt, DataType R, DataType C, DataType R1, DataType Q, DataType is, DataType vt)
    :is(is), vt(vt), R1(R1), Q(Q), drive(0.5)
    {
      A = dt / (2 * C) + R;
      B = dt / (2 * C) - R;
      oldy0 = oldy1 = 0;
      oldexpy0 = oldinvexpy0 = oldexpy1 = oldinvexpy1 = 1;
    }
    
    void set_drive(DataType drive)
    {
      this->drive = drive;
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
  
      std::pair<DataType, DataType> diode1 = std::make_pair(is * (expdiode_y1_p - 2 * expdiode_y1_m + 1), is * (expdiode_y1_p + 2 * expdiode_y1_m) / vt);
      DataType diode0 = is * (expdiode_y0_p - 2 * expdiode_y0_m + 1);
      return std::make_pair(x0 - x1 + y1 * (A / (R1 + drive * Q)) - y0 * (B / (R1 + drive * Q)) + A * diode1.first - B * diode0, (A / (R1 + drive * Q)) + A * diode1.second);
    }
  };
  
  
  template <typename DataType>
  SD1OverdriveFilter<DataType>::SD1OverdriveFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
    optimizer.reset(new ScalarNewtonRaphson<SD1OverdriveFunction<DataType> >(function));
  }

  template <typename DataType>
  SD1OverdriveFilter<DataType>::~SD1OverdriveFilter()
  {
  }

  template <typename DataType>
  void SD1OverdriveFilter<DataType>::setup()
  {
    Parent::setup();
    function.reset(new SD1OverdriveFunction<DataType>(1./input_sampling_rate, 100e3, 0.047e-6, 33e3, 1e6, 1e-12, 26e-3));
  }

  template <typename DataType>
  void SD1OverdriveFilter<DataType>::set_drive(DataType drive)
  {
    function->set_drive(drive);
  }

  template <typename DataType>
  void SD1OverdriveFilter<DataType>::process_impl(long size)
  {
    for(long i = 0; i < size; ++i)
    {
      outputs[0][i] = optimizer->optimize(converted_inputs[0][i]);
    }
  }

  template class SD1OverdriveFilter<float>;
  template class SD1OverdriveFilter<double>;
}
