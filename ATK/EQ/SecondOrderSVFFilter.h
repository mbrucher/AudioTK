/**
 * \file SecondOrderSVFFilter.h
 * Inspired by http://www.cytomic.com/files/dsp/SvfLinearTrapOptimised2.pdf
 */

#ifndef ATK_EQ_SECONDORDERSVFFILTER_H
#define ATK_EQ_SECONDORDERSVFFILTER_H

#include "config.h"
#include "../Core/TypedBaseFilter.h"

namespace ATK
{
  /**
   * SVF main filter class
   */
  template<typename SVFCoefficients>
  class ATK_EQ_EXPORT SecondOrderSVFFilter: public SVFCoefficients
  {
  public:
    typedef SVFCoefficients Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;

  public:
    SecondOrderSVFFilter();
    
  protected:
    void full_setup() override final;
    void process_impl(int64_t size) const override final;

    mutable DataType iceq1;
    mutable DataType iceq2;
  };

  template<typename DataType_>
  class BaseSecondOrderSVFCoefficients : public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
  protected:
    DataType cut_frequency;
    DataType Q;

    DataType a1;
    DataType a2;
    DataType a3;
    DataType m0;
    DataType m1;
    DataType m2;

  public:
    BaseSecondOrderSVFCoefficients();

    void set_cut_frequency(DataType_ cut_frequency);
    DataType_ get_cut_frequency() const;
    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
  };

  template<typename DataType_>
  class LowSecondOrderSVFCoefficients : public BaseSecondOrderSVFCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderSVFCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::cut_frequency;
    using Parent::Q;
    using Parent::input_sampling_rate;

  protected:
    void setup();
  };

  template<typename DataType_>
  class BandSecondOrderSVFCoefficients : public BaseSecondOrderSVFCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderSVFCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::cut_frequency;
    using Parent::Q;
    using Parent::input_sampling_rate;

  protected:
    void setup();
  };

  template<typename DataType_>
  class HighSecondOrderSVFCoefficients : public BaseSecondOrderSVFCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderSVFCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::cut_frequency;
    using Parent::Q;
    using Parent::input_sampling_rate;

  protected:
    void setup();
  };

  template<typename DataType_>
  class NotchSecondOrderSVFCoefficients : public BaseSecondOrderSVFCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderSVFCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::cut_frequency;
    using Parent::Q;
    using Parent::input_sampling_rate;

  protected:
    void setup();
  };

  template<typename DataType_>
  class PeakSecondOrderSVFCoefficients : public BaseSecondOrderSVFCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderSVFCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::cut_frequency;
    using Parent::Q;
    using Parent::input_sampling_rate;

  protected:
    void setup();
  };

  template<typename DataType_>
  class BellSecondOrderSVFCoefficients : public BaseSecondOrderSVFCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderSVFCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::cut_frequency;
    using Parent::Q;
    using Parent::input_sampling_rate;

    BellSecondOrderSVFCoefficients();

    void set_gain(DataType_ gain);
    DataType_ get_gain() const;
  protected:
    void setup();

    DataType gain;
  };

  template<typename DataType_>
  class LowShelfSecondOrderSVFCoefficients : public BaseSecondOrderSVFCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderSVFCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::cut_frequency;
    using Parent::Q;
    using Parent::input_sampling_rate;

    LowShelfSecondOrderSVFCoefficients();

    void set_gain(DataType_ gain);
    DataType_ get_gain() const;
  protected:
    void setup();

    DataType gain;
  };

  template<typename DataType_>
  class HighShelfSecondOrderSVFCoefficients : public BaseSecondOrderSVFCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderSVFCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::cut_frequency;
    using Parent::Q;
    using Parent::input_sampling_rate;

    HighShelfSecondOrderSVFCoefficients();
    
    void set_gain(DataType_ gain);
    DataType_ get_gain() const;

  protected:
    void setup();

    DataType gain;
  };
}

#endif
