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
  /// Second order SVF main filter class
  template<typename SVFCoefficients>
  class ATK_EQ_EXPORT SecondOrderSVFFilter: public SVFCoefficients
  {
  public:
    typedef SVFCoefficients Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;

  public:
    SecondOrderSVFFilter(int nb_channels = 1);
    ~SecondOrderSVFFilter();
    
  protected:
    void full_setup() override final;
    void process_impl(int64_t size) const override final;

    struct SVFState;
    std::unique_ptr<SVFState[]> state;
  };

  /// Second order SVF base coefficient class
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
    BaseSecondOrderSVFCoefficients(int nb_channels);

    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
    /// Sets the Q factor, must be strictly positive
    /*!
    * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
    */
    void set_Q(DataType_ Q);
    /// Returns the Q factor
    DataType_ get_Q() const;
  };

  /// Coefficients for a second order SVF low-pass filter
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

    LowSecondOrderSVFCoefficients(int nb_channels);

  protected:
    void setup();
  };

  /// Coefficients for a second order SVF band-pass filter
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

    BandSecondOrderSVFCoefficients(int nb_channels);

  protected:
    void setup();
  };

  /// Coefficients for a second order SVF high-pass filter
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

    HighSecondOrderSVFCoefficients(int nb_channels);

  protected:
    void setup();
  };

  /// Coefficients for a second order SVF notch filter
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

    NotchSecondOrderSVFCoefficients(int nb_channels);

  protected:
    void setup();
  };

  /// Coefficients for a second order SVF peak filter
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

    PeakSecondOrderSVFCoefficients(int nb_channels);

  protected:
    void setup();
  };

  /// Coefficients for a second order SVF bell filter
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

    BellSecondOrderSVFCoefficients(int nb_channels);

    /// Sets the gain of the bell
    void set_gain(DataType_ gain);
    /// Returns the gain for the bell
    DataType_ get_gain() const;
  protected:
    void setup();

    DataType gain;
  };

  /// Coefficients for a second order SVF low-pass shelving filter
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

    LowShelfSecondOrderSVFCoefficients(int nb_channels);

    /// Sets the gain of the shelf
    void set_gain(DataType_ gain);
    /// Returns the gain for the shelf
    DataType_ get_gain() const;
  protected:
    void setup();

    DataType gain;
  };

  /// Coefficients for a second order SVF high-pass shelving filter
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

    HighShelfSecondOrderSVFCoefficients(int nb_channels);
    
    /// Sets the gain of the shelf
    void set_gain(DataType_ gain);
    /// Returns the gain for the shelf
    DataType_ get_gain() const;

  protected:
    void setup();

    DataType gain;
  };
}

#endif
