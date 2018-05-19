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
    using typename Parent::CoeffDataType;
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
    SecondOrderSVFFilter(gsl::index nb_channels = 1);
    ~SecondOrderSVFFilter();
    
    void full_setup() final;
  protected:
    void process_impl(gsl::index size) const final;

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
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using Parent::setup;
  protected:
    CoeffDataType cut_frequency;
    CoeffDataType Q;

    CoeffDataType a1;
    CoeffDataType a2;
    CoeffDataType a3;
    CoeffDataType m0;
    CoeffDataType m1;
    CoeffDataType m2;

  public:
    SecondOrderSVFBaseCoefficients(gsl::index nb_channels);

    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(CoeffDataType cut_frequency);
    /// Returns the cut or central frequency
    CoeffDataType get_cut_frequency() const;
    /// Sets the Q factor, must be strictly positive
    /*!
    * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
    */
    void set_Q(CoeffDataType Q);
    /// Returns the Q factor
    CoeffDataType get_Q() const;
  };

  /// Coefficients for a second order SVF low-pass filter
  template<typename DataType_>
  class SecondOrderSVFLowPassCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
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

    SecondOrderSVFLowPassCoefficients(gsl::index nb_channels);

  protected:
    void setup() override;
  };

  /// Coefficients for a second order SVF band-pass filter
  template<typename DataType_>
  class SecondOrderSVFBandPassCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
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

    SecondOrderSVFBandPassCoefficients(gsl::index nb_channels);

  protected:
    void setup() override;
  };

  /// Coefficients for a second order SVF high-pass filter
  template<typename DataType_>
  class SecondOrderSVFHighPassCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
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

    SecondOrderSVFHighPassCoefficients(gsl::index nb_channels);

  protected:
    void setup() override;
  };

  /// Coefficients for a second order SVF notch filter
  template<typename DataType_>
  class SecondOrderSVFNotchCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
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

    SecondOrderSVFNotchCoefficients(gsl::index nb_channels);

  protected:
    void setup() override;
  };

  /// Coefficients for a second order SVF peak filter
  template<typename DataType_>
  class SecondOrderSVFPeakCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
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

    SecondOrderSVFPeakCoefficients(gsl::index nb_channels);

  protected:
    void setup() override;
  };

  /// Coefficients for a second order SVF bell filter
  template<typename DataType_>
  class SecondOrderSVFBellCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
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

    SecondOrderSVFBellCoefficients(gsl::index nb_channels);

    /// Sets the gain of the bell
    void set_gain(CoeffDataType gain);
    /// Returns the gain for the bell
    CoeffDataType get_gain() const;
  protected:
    void setup() override;

    CoeffDataType gain;
  };

  /// Coefficients for a second order SVF low-pass shelving filter
  template<typename DataType_>
  class SecondOrderSVFLowShelfCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
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

    SecondOrderSVFLowShelfCoefficients(gsl::index nb_channels);

    /// Sets the gain of the shelf
    void set_gain(CoeffDataType gain);
    /// Returns the gain for the shelf
    CoeffDataType get_gain() const;
  protected:
    void setup() override;

    CoeffDataType gain;
  };

  /// Coefficients for a second order SVF high-pass shelving filter
  template<typename DataType_>
  class SecondOrderSVFHighShelfCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderSVFBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
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

    SecondOrderSVFHighShelfCoefficients(gsl::index nb_channels);
    
    /// Sets the gain of the shelf
    void set_gain(CoeffDataType gain);
    /// Returns the gain for the shelf
    CoeffDataType get_gain() const;

  protected:
    void setup() override;

    CoeffDataType gain;
  };
}

#endif
