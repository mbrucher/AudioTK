/**
 * \file SimpleOverdriveFilter.h
 * Inspired by http://simulanalog.org/statevariable.pdf
 * See https://ccrma.stanford.edu/~dtyeh/papers/yeh07_dafx_clipode.pdf as well
 */

#ifndef ATK_DISTORTION_SIMPLEOVERDRIVEFILTER_H
#define ATK_DISTORTION_SIMPLEOVERDRIVEFILTER_H

#include <memory>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename Function, int max_iterations, bool check_convergence>
  class ScalarNewtonRaphson;
  
  /// Diode clipper filter, based on a trapezoidal rule
  template<typename DataType_>
  class ATK_DISTORTION_EXPORT SimpleOverdriveFilter: public TypedBaseFilter<DataType_>
  {
    class SimpleOverdriveFunction;
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
    */
    SimpleOverdriveFilter();
    /// Destructor
    ~SimpleOverdriveFilter();
    
  protected:
    void setup() override final;
    void process_impl(int64_t size) const override final;
    
  private:
    std::unique_ptr<ScalarNewtonRaphson<SimpleOverdriveFunction, 10, true> > optimizer;
  };

  /// Diode clipper filter, based on a backward Euler rule
  template<typename DataType_>
  class ATK_DISTORTION_EXPORT BackwardSimpleOverdriveFilter: public TypedBaseFilter<DataType_>
  {
    class SimpleOverdriveFunction;
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
     */
    BackwardSimpleOverdriveFilter();
    /// Destructor
    ~BackwardSimpleOverdriveFilter();
    
  protected:
    void setup() override final;
    void process_impl(int64_t size) const override final;
    
  private:
    std::unique_ptr<ScalarNewtonRaphson<SimpleOverdriveFunction, 10, true> > optimizer;
  };

  /// Diode clipper filter, based on a forward Euler rule
  template<typename DataType_>
  class ATK_DISTORTION_EXPORT ForwardSimpleOverdriveFilter: public TypedBaseFilter<DataType_>
  {
    class SimpleOverdriveFunction;
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
     */
    ForwardSimpleOverdriveFilter();
    /// Destructor
    ~ForwardSimpleOverdriveFilter();
    
  protected:
    void setup() override final;
    void process_impl(int64_t size) const override final;
  };
}

#endif
