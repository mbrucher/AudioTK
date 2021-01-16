/**
 * \file DiodeClipperFilter.h
 */

#ifndef ATK_DISTORTION_DIODECLIPPERFILTER_H
#define ATK_DISTORTION_DIODECLIPPERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Distortion/config.h>

#include <memory>

namespace ATK
{
  template<typename Function, int max_iterations, bool check_convergence>
  class ScalarNewtonRaphson;
  
  /// Diode clipper filter, based on a trapezoidal rule
  template<typename DataType_>
  class ATK_DISTORTION_EXPORT DiodeClipperFilter final : public TypedBaseFilter<DataType_>
  {
    class SimpleOverdriveFunction;
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
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
    */
    DiodeClipperFilter();
    /// Destructor
    ~DiodeClipperFilter();
    
  protected:
    void setup() final;
    void process_impl(gsl::index size) const final;
    
  private:
    std::unique_ptr<ScalarNewtonRaphson<SimpleOverdriveFunction, 10, true> > optimizer;
  };
}

#endif
