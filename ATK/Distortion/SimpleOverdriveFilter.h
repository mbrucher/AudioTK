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
  template<typename Function>
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
    
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    SimpleOverdriveFilter(int nb_channels = 1);
    /// Destructor
    ~SimpleOverdriveFilter();
    
  protected:
    void setup() override final;
    void process_impl(int64_t size) const override final;
    
  private:
    std::unique_ptr<ScalarNewtonRaphson<SimpleOverdriveFunction> > optimizer;
  };
}

#endif
