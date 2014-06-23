/**
 * \file SD1OverdriveFilter.cpp
 */

#include "SD1OverdriveFilter.h"

#include <boost/math/special_functions/sign.hpp>

#include "../Tools/exp.h"
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
  };
  
  
  template <typename DataType>
  SD1OverdriveFilter<DataType>::SD1OverdriveFilter(int nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels)
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
    function.reset(new SD1OverdriveFunction<DataType>(static_cast<DataType>(1./input_sampling_rate), 100e3, 0.047e-6, 33e3, 1e6, 1e-12, 26e-3));
    function->set_drive(drive);
  }

  template <typename DataType>
  void SD1OverdriveFilter<DataType>::set_drive(DataType drive)
  {
    if(drive < 0 || drive > 1)
    {
      throw std::out_of_range("Drive must be a value between 0 and 1");
    }
    this->drive = drive;
    function->set_drive(drive);
  }

  template <typename DataType>
  void SD1OverdriveFilter<DataType>::process_impl(std::int64_t size)
  {
    assert(nb_input_ports == nb_output_ports);

    for(int channel = 0; channel < nb_input_ports; ++channel)
    {
      for(std::int64_t i = 0; i < size; ++i)
      {
        outputs[channel][i] = optimizer->optimize(converted_inputs[channel][i]);
      }
    }
  }

  template class SD1OverdriveFilter<float>;
  template class SD1OverdriveFilter<double>;
}
