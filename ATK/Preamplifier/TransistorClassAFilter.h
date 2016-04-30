/**
 * \file TransistorClassAFilter.h
 * Heavily inspired by Simualtion of a guitar amplifier stage for several triode models (Cohen and Helie)
 */

#ifndef ATK_PREAMPLIFIER_TRANSISTORCLASSAFILTER_H
#define ATK_PREAMPLIFIER_TRANSISTORCLASSAFILTER_H

#include <list>
#include <vector>

#include <ATK/Preamplifier/config.h>

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename Function, int size, int max_iterations, bool check_convergence>
  class VectorizedNewtonRaphson;

  /// A class A transistor preamplifier (Ebers-Moll equations)
  /**
   * Output 0 is Vout
   * Output 1 is Ve
   * Output 2 is Vout - Vc
   * Output 3 is Vc
   * Output 4 is Vb
   */
  template<typename DataType_>
  class ATK_PREAMPLIFIER_EXPORT TransistorClassAFilter: public TypedBaseFilter<DataType_>
  {
    class TransistorClassAFunction;
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_delay;
    using Parent::output_delay;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    
    using Parent::default_output;
  protected:
    std::unique_ptr<VectorizedNewtonRaphson<TransistorClassAFunction, 4, 10, true> > optimizer;

  public:
    /// Build a new preamp filter
    TransistorClassAFilter();
    ~TransistorClassAFilter();
    
    void process_impl(int64_t size) const override final;
    
    void setup() override final;
    void full_setup() override final;
  };
}

#endif
