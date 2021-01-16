/**
 * \file SecondOrderSVFFilter.h
 * Inspired by http://www.cytomic.com/files/dsp/SvfLinearTrapOptimised2.pdf
 */

#ifndef ATK_EQ_SECONDORDERSVFFILTER_H
#define ATK_EQ_SECONDORDERSVFFILTER_H

#include <ATK/EQ/config.h>
#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// Second order SVF main filter class
  template<typename SVFCoefficients>
  class ATK_EQ_EXPORT SecondOrderSVFFilter final: public SVFCoefficients
  {
  protected:
    using Parent = SVFCoefficients;
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
    explicit SecondOrderSVFFilter(gsl::index nb_channels = 1);
    ~SecondOrderSVFFilter() override;
    
    void full_setup() final;
  protected:
    void process_impl(gsl::index size) const final;

    class SVFState;
    std::unique_ptr<SVFState[]> state;
  };

  /// Second order SVF base coefficient class
  template<typename DataType_>
  class SecondOrderSVFBaseCoefficients : public TypedBaseFilter<DataType_>
  {
  public:
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::setup;
  protected:
    CoeffDataType cut_frequency{0};
    CoeffDataType Q{1};

    CoeffDataType a1{0};
    CoeffDataType a2{0};
    CoeffDataType a3{0};
    CoeffDataType m0{0};
    CoeffDataType m1{0};
    CoeffDataType m2{0};

  public:
    explicit SecondOrderSVFBaseCoefficients(gsl::index nb_channels);

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
    using Parent = SecondOrderSVFBaseCoefficients<DataType_>;
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

    explicit SecondOrderSVFLowPassCoefficients(gsl::index nb_channels);

  protected:
    void setup() override;
  };

  /// Coefficients for a second order SVF band-pass filter
  template<typename DataType_>
  class SecondOrderSVFBandPassCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = SecondOrderSVFBaseCoefficients<DataType_>;
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

    explicit SecondOrderSVFBandPassCoefficients(gsl::index nb_channels);

  protected:
    void setup() override;
  };

  /// Coefficients for a second order SVF high-pass filter
  template<typename DataType_>
  class SecondOrderSVFHighPassCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = SecondOrderSVFBaseCoefficients<DataType_>;
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

    explicit SecondOrderSVFHighPassCoefficients(gsl::index nb_channels);

  protected:
    void setup() override;
  };

  /// Coefficients for a second order SVF notch filter
  template<typename DataType_>
  class SecondOrderSVFNotchCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = SecondOrderSVFBaseCoefficients<DataType_>;
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

    explicit SecondOrderSVFNotchCoefficients(gsl::index nb_channels);

  protected:
    void setup() override;
  };

  /// Coefficients for a second order SVF peak filter
  template<typename DataType_>
  class SecondOrderSVFPeakCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = SecondOrderSVFBaseCoefficients<DataType_>;
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

    explicit SecondOrderSVFPeakCoefficients(gsl::index nb_channels);

  protected:
    void setup() override;
  };

  /// Coefficients for a second order SVF bell filter
  template<typename DataType_>
  class SecondOrderSVFBellCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = SecondOrderSVFBaseCoefficients<DataType_>;
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

    explicit SecondOrderSVFBellCoefficients(gsl::index nb_channels);

    /// Sets the gain of the bell
    void set_gain(CoeffDataType gain);
    /// Returns the gain for the bell
    CoeffDataType get_gain() const;
  protected:
    void setup() override;

    CoeffDataType gain{1};
  };

  /// Coefficients for a second order SVF low-pass shelving filter
  template<typename DataType_>
  class SecondOrderSVFLowShelfCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = SecondOrderSVFBaseCoefficients<DataType_>;
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

    explicit SecondOrderSVFLowShelfCoefficients(gsl::index nb_channels);

    /// Sets the gain of the shelf
    void set_gain(CoeffDataType gain);
    /// Returns the gain for the shelf
    CoeffDataType get_gain() const;
  protected:
    void setup() override;

    CoeffDataType gain{1};
  };

  /// Coefficients for a second order SVF high-pass shelving filter
  template<typename DataType_>
  class SecondOrderSVFHighShelfCoefficients : public SecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = SecondOrderSVFBaseCoefficients<DataType_>;
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

    explicit SecondOrderSVFHighShelfCoefficients(gsl::index nb_channels);
    
    /// Sets the gain of the shelf
    void set_gain(CoeffDataType gain);
    /// Returns the gain for the shelf
    CoeffDataType get_gain() const;

  protected:
    void setup() override;

    CoeffDataType gain{1};
  };
}

#endif
