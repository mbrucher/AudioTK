/**
 * \file SD1OverdriveFilter.cpp
 */

#include "SD1OverdriveFilter.h"
#include <ATK/Utility/fmath.h>
#include <ATK/Utility/ScalarNewtonRaphson.h>

#include <boost/math/special_functions/sign.hpp>

#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  class SD1OverdriveFilter<DataType_>::SD1OverdriveFunction
  {
  public:
    using DataType = DataType_;
  protected:
    const DataType R;
    const DataType R1;
    const DataType C;
    const DataType Q;
    DataType drive = 0.5;
    const DataType is;
    const DataType vt;

    DataType ieq{0};
    DataType i{0};

    DataType expdiode_y1_p{1};
    DataType expdiode_y1_m{1};

  public:
    SD1OverdriveFunction(DataType dt, DataType R, DataType C, DataType R1, DataType Q, DataType is, DataType vt)
      :R(R), R1(R1), C(2 * C / dt), Q(Q), is(is), vt(vt)
    {
    }
    
    void set_drive(DataType drive)
    {
      this->drive = (R1 + drive * Q);
    }

    std::pair<DataType, DataType> operator()(const DataType* ATK_RESTRICT input, DataType* ATK_RESTRICT output, DataType y1)
    {
      auto x1 = input[0];
      y1 -= x1;
      expdiode_y1_p = fmath::exp(y1 / vt);
      expdiode_y1_m = 1 / expdiode_y1_p;

      DataType diode1 = is * (expdiode_y1_p - 2 * expdiode_y1_m + 1);
      DataType diode1_derivative = is * (expdiode_y1_p + 2 * expdiode_y1_m) / vt;

      i = (C * x1 - ieq) / (1 + R * C);

      return std::make_pair(y1 / drive + diode1 - i, 1 / drive + diode1_derivative);
    }
    
    void update_state(const DataType* ATK_RESTRICT input, DataType* ATK_RESTRICT output)
    {
      auto x1 = input[0];
      ieq = 2 * C * (x1 - i * R) - ieq;
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
      y0 -= x0;
      auto sinh = is * (expdiode_y1_p - 2 * expdiode_y1_m + 1);
      auto cosh = is * (expdiode_y1_p + 2 * expdiode_y1_m);
      auto i = (C * x1 - ieq) / (1 + R * C);

      return (i - (sinh - y0 / vt * cosh)) / (cosh / vt + (1 / drive)) + x1;
    }
  };
  
  template <typename DataType>
  SD1OverdriveFilter<DataType>::SD1OverdriveFilter()
    :TypedBaseFilter<DataType>(1, 1)
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
    optimizer = std::make_unique<ScalarNewtonRaphson<SD1OverdriveFunction, num_iterations, true>>(SD1OverdriveFunction(static_cast<DataType>(1. / input_sampling_rate),
      static_cast<DataType>(4.7e3), static_cast<DataType>(0.047e-6), static_cast<DataType>(33e3),
      static_cast<DataType>(1e6), static_cast<DataType>(1e-12), static_cast<DataType>(26e-3)));

    optimizer->get_function().set_drive(drive);
  }

  template <typename DataType_>
  void SD1OverdriveFilter<DataType_>::set_drive(DataType_ drive)
  {
    if(drive < 0 || drive > 1)
    {
      throw std::out_of_range("Drive must be a value between 0 and 1");
    }
    this->drive = drive;
    if(optimizer)
    {
        optimizer->get_function().set_drive(drive);
    }
  }

  template <typename DataType_>
  DataType_ SD1OverdriveFilter<DataType_>::get_drive() const
  {
    return drive;
  }

  template <typename DataType>
  void SD1OverdriveFilter<DataType>::process_impl(gsl::index size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(gsl::index i = 0; i < size; ++i)
    {
      optimizer->optimize(input + i, output + i);
      optimizer->get_function().update_state(input + i, output + i);
    }
  }

#if ATK_ENABLE_INSTANTIATION
  template class SD1OverdriveFilter<float>;
#endif
  template class SD1OverdriveFilter<double>;
}
