/**
 * \file TriodeFilter.h
 * Heavily inspired by Simulation of a guitar amplifier stage for several triode models (Cohen and Helie)
 */

#ifndef ATK_PREAMPLIFIER_TRIODEFILTER_H
#define ATK_PREAMPLIFIER_TRIODEFILTER_H

#include <list>
#include <vector>

#include <ATK/Preamplifier/config.h>

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename Function, int size, int max_iterations, bool check_convergence>
  class VectorizedNewtonRaphson;

  /// A tube preamplifier
  /**
   * Output 0 is Vout
   * Output 1 is Ve
   * Output 2 is Vout - Vc
   * Output 3 is Vc
   * Output 4 is Vb
   */
  template<typename DataType_, typename TriodeFunction>
  class ATK_PREAMPLIFIER_EXPORT TriodeFilter: public TypedBaseFilter<DataType_>
  {
    class CommonCathodeTriodeFunction;
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
    std::unique_ptr<VectorizedNewtonRaphson<CommonCathodeTriodeFunction, 4, 10, true> > optimizer;

    const DataType_ Rp;
    const DataType_ Rg;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;
    const DataType_ Co;
    const DataType_ Ck;

    TriodeFunction tube_function;

    TriodeFilter(DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType VBias, DataType Co, DataType Ck, TriodeFunction&& tube_function);
  public:
    static TriodeFilter build_standard_filter();
    
    /// Move constructor
    TriodeFilter(TriodeFilter&& other);
    /// Destructor
    ~TriodeFilter();

    void process_impl(int64_t size) const override final;
    
    void full_setup() override final;
    void setup() override final;
  };
}

#endif
