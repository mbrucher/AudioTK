/**
 * \file SD1OverdriveFilter.h
 */

#ifndef ATK_DISTORTION_SD1OVERDRIVEFILTER_H
#define ATK_DISTORTION_SD1OVERDRIVEFILTER_H

#include <memory>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename Function, int max_iterations, bool check_convergence>
  class ScalarNewtonRaphson;

  /// SD1 filter, based on a trapezoidal rule
  template<typename DataType_>
  class ATK_DISTORTION_EXPORT SD1OverdriveFilter: public TypedBaseFilter<DataType_>
  {
    class SD1OverdriveFunction;
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;

    using Parent::input_delay;
    using Parent::output_delay;
  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    SD1OverdriveFilter();
    /// Destructor
    ~SD1OverdriveFilter();

    void set_drive(DataType drive);

  protected:
    void setup() override final;
    void process_impl(int64_t size) const override final;
    DataType drive;
    
  private:
    std::unique_ptr<ScalarNewtonRaphson<SD1OverdriveFunction, 10, true> > optimizer;
  };
}

#endif
