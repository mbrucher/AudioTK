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
    using typename Parent::AlignedScalarVector;
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
    SecondOrderSVFFilter(std::size_t nb_channels = 1);
    ~SecondOrderSVFFilter();
    
    void full_setup() override final;
  protected:
    void process_impl(std::size_t size) const override final;

    struct SVFState;
    std::unique_ptr<SVFState[]> state;
  };

  /// Second order SVF base coefficient class
  template<typename DataType_>
  class SecondOrderSVFBaseCoefficients : public TypedBaseFilter<DataType_>
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
    SecondOrderSVFBaseCoefficients(std::size_t nb_channels);

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
  class SecondOrderSVFLowPassCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
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

    SecondOrderSVFLowPassCoefficients(std::size_t nb_channels);

  protected:
    void setup();
  };

  /// Coefficients for a second order SVF band-pass filter
  template<typename DataType_>
  class SecondOrderSVFBandPassCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
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

    SecondOrderSVFBandPassCoefficients(std::size_t nb_channels);

  protected:
    void setup();
  };

  /// Coefficients for a second order SVF high-pass filter
  template<typename DataType_>
  class SecondOrderSVFHighPassCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
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

    SecondOrderSVFHighPassCoefficients(std::size_t nb_channels);

  protected:
    void setup();
  };

  /// Coefficients for a second order SVF notch filter
  template<typename DataType_>
  class SecondOrderSVFNotchCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
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

    SecondOrderSVFNotchCoefficients(std::size_t nb_channels);

  protected:
    void setup();
  };

  /// Coefficients for a second order SVF peak filter
  template<typename DataType_>
  class SecondOrderSVFPeakCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
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

    SecondOrderSVFPeakCoefficients(std::size_t nb_channels);

  protected:
    void setup();
  };

  /// Coefficients for a second order SVF bell filter
  template<typename DataType_>
  class SecondOrderSVFBellCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
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

    SecondOrderSVFBellCoefficients(std::size_t nb_channels);

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
  class SecondOrderSVFLowShelfCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
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

    SecondOrderSVFLowShelfCoefficients(std::size_t nb_channels);

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
  class SecondOrderSVFHighShelfCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
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

    SecondOrderSVFHighShelfCoefficients(std::size_t nb_channels);
    
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
