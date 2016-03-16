/**
 * \file SD1OverdriveFilter.cpp
 */

#include "SD1OverdriveFilter.h"

#include <stdexcept>

#include <boost/math/special_functions/sign.hpp>

#include <ATK/Utility/exp.h>
#include <ATK/Utility/ScalarNewtonRaphson.h>

namespace ATK
{
  template<typename DataType_>
  class SD1OverdriveFilter<DataType_>::SD1OverdriveFunction
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
    
    Exp<DataType> exp;

  public:
    SD1OverdriveFunction(DataType dt, DataType R, DataType C, DataType R1, DataType Q, DataType is, DataType vt)
    :R1(R1), Q(Q), drive(0.5), is(is), vt(vt), exp(32, 1024*1024)
    {
      A = dt / (2 * C) + R;
      B = dt / (2 * C) - R;
      oldy0 = oldy1 = 0;
      oldexpy0 = oldinvexpy0 = oldexpy1 = oldinvexpy1 = 1;
    }
    
    void set_drive(DataType drive)
    {
      this->drive = (R1 + drive * Q);
    }
    
    std::pair<DataType, DataType> operator()(DataType x0, DataType x1, DataType y0, DataType y1)
    {
      y0 -= x0;
      y1 -= x1;
      DataType expdiode_y1_p = exp(y1 / vt);
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
	      expdiode_y0_p = exp(y0 / vt);
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
      return std::make_pair(x0 - x1 + y1 * (A / drive) + y0 * (B / drive) + A * diode1.first + B * diode0, (A / drive) + A * diode1.second);
    }

    DataType estimate(DataType x0, DataType x1, DataType y0)
    {
      return y0;
    }
  };
  
  
  template <typename DataType>
  SD1OverdriveFilter<DataType>::SD1OverdriveFilter()
    :TypedBaseFilter<DataType>(1, 1), drive(0)
  {
  }

  template <typename DataType>
  SD1OverdriveFilter<DataType>::~SD1OverdriveFilter()
  {
  }

  template <typename DataType>
  void SD1OverdriveFilter<DataType>::setup()
  {
    Parent::setup();
    optimizer.reset(new ScalarNewtonRaphson<SD1OverdriveFunction>(SD1OverdriveFunction(static_cast<DataType>(1. / input_sampling_rate),
      static_cast<DataType>(100e3), static_cast<DataType>(0.047e-6), static_cast<DataType>(33e3),
      static_cast<DataType>(1e6), static_cast<DataType>(1e-12), static_cast<DataType>(26e-3))));

    optimizer->get_function().set_drive(drive);
  }

  template <typename DataType>
  void SD1OverdriveFilter<DataType>::set_drive(DataType drive)
  {
    if(drive < 0 || drive > 1)
    {
      throw std::out_of_range("Drive must be a value between 0 and 1");
    }
    this->drive = drive;
    optimizer->get_function().set_drive(drive);
  }

  template <typename DataType>
  void SD1OverdriveFilter<DataType>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);

    for(int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(int64_t i = 0; i < size; ++i)
      {
        output[i] = optimizer->optimize(input[i]);
      }
    }
  }

  template class SD1OverdriveFilter<float>;
  template class SD1OverdriveFilter<double>;
}
