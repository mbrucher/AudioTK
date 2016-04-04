/**
 * \file SD1OverdriveFilter.cpp
 */

#include "SD1OverdriveFilter.h"

#include <stdexcept>

#include <boost/math/special_functions/sign.hpp>

#include <ATK/Utility/ScalarNewtonRaphson.h>

namespace ATK
{
  template<typename DataType_>
  class SD1OverdriveFilter<DataType_>::SD1OverdriveFunction
  {
  public:
    typedef DataType_ DataType;
  protected:
    const DataType A;
    const DataType B;
    const DataType R1;
    const DataType Q;
    DataType drive;
    const DataType is;
    const DataType vt;

    DataType oldy0;
    DataType oldexpy0;
    DataType oldinvexpy0;
    DataType oldy1;
    DataType oldexpy1;
    DataType oldinvexpy1;

  public:
    SD1OverdriveFunction(DataType dt, DataType R, DataType C, DataType R1, DataType Q, DataType is, DataType vt)
    :A(dt / (2 * C) + R), B(dt / (2 * C) - R), R1(R1), Q(Q), drive(0.5), is(is), vt(vt)
    {
      oldy0 = oldy1 = 0;
      oldexpy0 = oldinvexpy0 = oldexpy1 = oldinvexpy1 = 1;
    }
    
    void set_drive(DataType drive)
    {
      this->drive = (R1 + drive * Q);
    }
    
    std::pair<DataType, DataType> operator()(const DataType* ATK_RESTRICT input, DataType* ATK_RESTRICT output, DataType y1)
    {
      auto x0 = input[-1];
      auto x1 = input[0];
      auto y0 = output[-1];
      y0 -= x0;
      y1 -= x1;
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
  
      DataType diode1 = is * (expdiode_y1_p - 2 * expdiode_y1_m + 1);
      DataType diode1_derivative = is * (expdiode_y1_p + 2 * expdiode_y1_m) / vt;
      DataType diode0 = is * (expdiode_y0_p - 2 * expdiode_y0_m + 1);
      return std::make_pair(x0 - x1 + y1 * (A / drive) + y0 * (B / drive) + A * diode1 + B * diode0, (A / drive) + A * diode1_derivative);
    }

    DataType estimate(const DataType* ATK_RESTRICT input, DataType* ATK_RESTRICT output)
    {
      auto x0 = input[-1];
      auto x1 = input[0];
      auto y0 = output[-1];
      return affine_estimate(x0, x1, y0);
    }
    
    DataType id_estimate(DataType x0, DataType x1, DataType y0)
    {
      return y0;
    }
    
    DataType linear_estimate(DataType x0, DataType x1, DataType y0)
    {
      y0 -= x0;
      if(y0 == 0)
        return 0;
      auto sinh = is * (oldexpy1 - oldinvexpy1);
      return (x1 - x0 - y0 * (B / drive) - B * sinh) / (A * sinh / y0 + (A / drive)) + x1;
    }
    
    DataType affine_estimate(DataType x0, DataType x1, DataType y0)
    {
      y0 -= x0;
      auto sinh = is * (oldexpy1 - oldinvexpy1);
      auto cosh = is * (oldexpy1 + oldinvexpy1);
      return (x1 - x0 - y0 * (B / drive) - B * sinh - A * (sinh - y0 / vt * cosh) ) / (A * cosh / vt + (A / drive)) + x1;
    }
  };
  
  
  template <typename DataType>
  SD1OverdriveFilter<DataType>::SD1OverdriveFilter()
    :TypedBaseFilter<DataType>(1, 1), drive(0)
  {
    input_delay = 1;
    output_delay = 1;
  }

  template <typename DataType>
  SD1OverdriveFilter<DataType>::~SD1OverdriveFilter()
  {
  }

  template <typename DataType>
  void SD1OverdriveFilter<DataType>::setup()
  {
    Parent::setup();
    optimizer.reset(new ScalarNewtonRaphson<SD1OverdriveFunction, 10, true>(SD1OverdriveFunction(static_cast<DataType>(1. / input_sampling_rate),
      static_cast<DataType>(4.7e3), static_cast<DataType>(0.047e-6), static_cast<DataType>(33e3),
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
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(int64_t i = 0; i < size; ++i)
    {
      optimizer->optimize(input + i, output + i);
    }
  }

  template class SD1OverdriveFilter<float>;
  template class SD1OverdriveFilter<double>;
}
