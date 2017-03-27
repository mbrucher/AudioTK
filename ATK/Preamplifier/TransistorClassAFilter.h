/**
 * \file TransistorClassAFilter.h
 * Heavily inspired by http://www.electronics-tutorials.ws/amplifier/amp_2.html
 */

#ifndef ATK_PREAMPLIFIER_TRANSISTORCLASSAFILTER_H
#define ATK_PREAMPLIFIER_TRANSISTORCLASSAFILTER_H

#include <list>
#include <vector>

#include <ATK/Preamplifier/config.h>
#include <ATK/Preamplifier/TransistorFunction.h>

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename Function, std::size_t size, std::size_t max_iterations, bool check_convergence>
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
  private:
    static const int nb_max_iter = 10;
    std::unique_ptr<VectorizedNewtonRaphson<TransistorClassAFunction, 4, nb_max_iter, true> > optimizer;

    const DataType_ Rp;
    const DataType_ Rg1;
    const DataType_ Rg2;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ VBias;
    const DataType_ Cg;
    const DataType_ Co;
    const DataType_ Ck;
    
    TransistorFunction<DataType> transistor_function;

  protected:
    /// Build a new preamp filter
    TransistorClassAFilter(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk, DataType VBias, DataType Cg, DataType Co, DataType Ck, TransistorFunction<DataType>&& transistor_function);
  public:
    /// Move constructor
    TransistorClassAFilter(TransistorClassAFilter&& other);
    /// Destructor
    ~TransistorClassAFilter();

    /// Build a simple class A preamp
    /**
     * The preamp clips at 5V, gain of 10 at BF, 200 at HF and inverts the input.
     * This means that the input has to be low to allow a proper amplification.
     */
    static TransistorClassAFilter build_standard_filter();

    void process_impl(std::size_t size) const override final;

    void setup() override final;
    void full_setup() override final;
  };
}

#endif
