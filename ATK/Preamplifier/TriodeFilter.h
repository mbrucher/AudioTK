/**
 * \file TriodeFilter.h
 * Heavily inspired by Simulation of a guitar amplifier stage for several triode models (Cohen and Helie)
 */

#ifndef ATK_PREAMPLIFIER_TRIODEFILTER_H
#define ATK_PREAMPLIFIER_TRIODEFILTER_H

#include <ATK/Preamplifier/config.h>
#include <ATK/Core/TypedBaseFilter.h>

#include <list>
#include <vector>

namespace ATK
{
  template<typename Function, gsl::index size, gsl::index max_iterations, bool check_convergence>
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
  class ATK_PREAMPLIFIER_EXPORT TriodeFilter final : public TypedBaseFilter<DataType_>
  {
    class CommonCathodeTriodeFunction;
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
    std::unique_ptr<VectorizedNewtonRaphson<CommonCathodeTriodeFunction, 4, 10, true> > optimizer;

    const DataType_ Rp;
    const DataType_ Rg;
    const DataType_ Ro;
    const DataType_ Rk;
    const DataType_ Vbias;
    const DataType_ Co;
    const DataType_ Ck;

    TriodeFunction tube_function;

  protected:
    /// Constructor, used with a builder static method
    TriodeFilter(DataType Rp, DataType Rg, DataType Ro, DataType Rk, DataType Vbias, DataType Co, DataType Ck, TriodeFunction&& tube_function);
  public:
    /// Builds a standard filter with default triode and circuit parameters
    static TriodeFilter build_standard_filter(DataType Rp=200e3, DataType Rg=220e3, DataType Ro=220e3, DataType Rk=1e3, DataType Vbias=300, DataType Co=22e-9, DataType Ck=1.e-6, TriodeFunction function = TriodeFunction::build_standard_function());
    /**
     * Build a custom filter with a given tube function contructor
     * The defaults are Rp=200e3, Rg=220e3, Ro=220e3, Rk=1e3, Vbias=300, Co=22e-9, Ck=1e-6
     * Guitar AC30 preamp: Rp=220e3, Rg=68e3, Ro=1e6, Rk=1.5e3, Vbias=300, Co=47e-9, Ck=22e-6
     * Bass Bassman preamp: Rp=100e3, Rg=1e6, Ro=1e6, Rk=820, Vbias=300, Co=22e-9, Ck=250e-6
     */
    template<TriodeFunction function()>
    static TriodeFilter build_alternate_filter(DataType Rp=200e3, DataType Rg=220e3, DataType Ro=220e3, DataType Rk=1e3, DataType Vbias=300, DataType Co=22e-9, DataType Ck=1.e-6)
    {
        return TriodeFilter<DataType, TriodeFunction>(Rp, Rg, Ro, Rk, //R
                                                      Vbias, // Vbias
                                                      Co, Ck, // C
                                                      function() // tube
                                                      );
    }
    
    /// Move constructor
    TriodeFilter(TriodeFilter&& other);
    /// Destructor
    ~TriodeFilter() override;

    void process_impl(gsl::index size) const final;
    
    void full_setup() final;
    void setup() final;
  };
}

#endif
