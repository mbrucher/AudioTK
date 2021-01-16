/**
 * \file FollowerTransistorClassAFilter.h
 * Heavily inspired by http://electronics.stackexchange.com/questions/49860/speaker-bjt-amplifier-function
 */

#ifndef ATK_PREAMPLIFIER_FOLLOWERTRANSISTORCLASSAFILTER_H
#define ATK_PREAMPLIFIER_FOLLOWERTRANSISTORCLASSAFILTER_H

#include <ATK/Preamplifier/config.h>
#include <ATK/Preamplifier/TransistorFunction.h>
#include <ATK/Core/TypedBaseFilter.h>

#include <list>
#include <vector>

namespace ATK
{
  template<typename Function, gsl::index size, gsl::index max_iterations, bool check_convergence>
  class VectorizedNewtonRaphson;

  /// A follower class A transistor preamplifier (Ebers-Moll equations)
  /**
   * Output 0 is Vout
   * Output 1 is Ve1
   * Output 2 is Vc
   * Output 3 is Vb
   * Output 4 is Ve2
   */
  template<typename DataType_>
  class ATK_PREAMPLIFIER_EXPORT FollowerTransistorClassAFilter final : public TypedBaseFilter<DataType_>
  {
    class TransistorClassAFunction;
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
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
    std::unique_ptr<VectorizedNewtonRaphson<TransistorClassAFunction, 5, nb_max_iter, true> > optimizer;

    const DataType_ Rp;
    const DataType_ Rg1;
    const DataType_ Rg2;
    const DataType_ Ro;
    const DataType_ Rk1;
    const DataType_ Rk2;
    const DataType_ Vbias;
    const DataType_ Cg;
    const DataType_ Co;
    const DataType_ Ck;
    
    TransistorFunction<DataType> transistor_function_1;
    TransistorFunction<DataType> transistor_function_2;

  protected:
    /// Build a new preamp filter
    FollowerTransistorClassAFilter(DataType Rp, DataType Rg1, DataType Rg2, DataType Ro, DataType Rk1, DataType Rk2, DataType Vbias,
      DataType Cg, DataType Co, DataType Ck, TransistorFunction<DataType>&& transistor_function_1, TransistorFunction<DataType>&& transistor_function_2);
  public:
    /// Move constructor
    FollowerTransistorClassAFilter(FollowerTransistorClassAFilter&& other);
    /// Destructor
    ~FollowerTransistorClassAFilter() override;

    /// Build a simple class A preamp
    /**
     * The preamp clips at 5V, gain of 10 at BF, 200 at HF and inverts the input.
     * This means that the input has to be low to allow a proper amplification.
     */
    static FollowerTransistorClassAFilter build_standard_filter(DataType_ Rp=10e3, DataType_ Rg1=220e3, DataType_ Rg2=27e3, DataType_ Ro=8, DataType_ Rk1=1.5e3, DataType_ Rk2=1e3,
      DataType_ Vbias=10, DataType_ Cg=0.47e-6, DataType_ Co=4.7e-6, DataType_ Ck=33e-6, TransistorFunction<DataType_> function1 = TransistorFunction<DataType_>::build_standard_function(), TransistorFunction<DataType_> function2 = TransistorFunction<DataType_>::build_standard_function());

    void process_impl(gsl::index size) const final;

    void setup() final;
    void full_setup() final;
  };
}

#endif
