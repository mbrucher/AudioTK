/**
 * \file TS9OverdriveFilter.h
 */

#ifndef ATK_DISTORTION_TS9OVERDRIVEFILTER_H
#define ATK_DISTORTION_TS9OVERDRIVEFILTER_H

#include <memory>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename Function, int max_iterations, bool check_convergence>
  class ScalarNewtonRaphson;

  /// TS9 filter, based on a trapezoidal rule
  template<typename DataType_>
  class ATK_DISTORTION_EXPORT TS9OverdriveFilter final : public TypedBaseFilter<DataType_>
  {
    class TS9OverdriveFunction;
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
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
    TS9OverdriveFilter();
    /// Destructor
    ~TS9OverdriveFilter();

    void set_drive(DataType_ drive);
    DataType_ get_drive() const;

  protected:
    void setup() override final;
    void process_impl(std::size_t size) const override final;
    DataType drive;
    
  private:
    static const int num_iterations = 30;
    std::unique_ptr<ScalarNewtonRaphson<TS9OverdriveFunction, num_iterations, true> > optimizer;
  };
}

#endif
