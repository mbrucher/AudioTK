/**
 * \file SimpleOverdriveFilter.h
 * Inspired by http://simulanalog.org/statevariable.pdf
 * See https://ccrma.stanford.edu/~dtyeh/papers/yeh07_dafx_clipode.pdf as well
 */

#ifndef ATK_DISTORTION_SIMPLEOVERDRIVEFILTER_H
#define ATK_DISTORTION_SIMPLEOVERDRIVEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Distortion/config.h>

#include <memory>

namespace ATK
{
  template<typename Function, int max_iterations, bool check_convergence>
  class ScalarNewtonRaphson;
  
  /// Diode clipper filter, based on a trapezoidal rule
  template<typename DataType_>
  class ATK_DISTORTION_EXPORT SimpleOverdriveFilter final : public TypedBaseFilter<DataType_>
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
    SimpleOverdriveFilter();
    /// Destructor
    ~SimpleOverdriveFilter();
    
  protected:
    void setup() final;
    void process_impl(gsl::index size) const final;
    
  private:
    std::unique_ptr<ScalarNewtonRaphson<SimpleOverdriveFunction, 10, true> > optimizer;
  };
}

#endif
