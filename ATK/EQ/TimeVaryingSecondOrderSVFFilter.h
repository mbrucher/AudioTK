/**
 * \file TimeVaryingSecondOrderSVFFilter.h
 * Inspired by http://www.cytomic.com/files/dsp/SvfLinearTrapOptimised2.pdf
 */

#ifndef ATK_EQ_TIMEVARYINGSECONDORDERSVFFILTER_H
#define ATK_EQ_TIMEVARYINGSECONDORDERSVFFILTER_H

#include <ATK/EQ/config.h>
#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// Second order SVF main filter class with time varying frequency
  template<typename SVFCoefficients>
  class ATK_EQ_EXPORT TimeVaryingSecondOrderSVFFilter final : public SVFCoefficients
  {
  protected:
    using Parent = SVFCoefficients;
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
    using Parent::update_coeffs;

  public:
    explicit TimeVaryingSecondOrderSVFFilter(gsl::index nb_channels = 1);
    ~TimeVaryingSecondOrderSVFFilter() override;
    
  protected:
    void full_setup() final;
    void process_impl(gsl::index size) const final;

    class SVFState;
    std::unique_ptr<SVFState[]> state;
  };

  /// Second order SVF base coefficient class
  template<typename DataType_>
  class TimeVaryingSecondOrderSVFBaseCoefficients : public TypedBaseFilter<DataType_>
  {
  public:
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::setup;
  protected:
    DataType Q{1};

    mutable DataType a1{0};
    mutable DataType a2{0};
    mutable DataType a3{0};
    mutable DataType m0{0};
    mutable DataType m1{0};
    mutable DataType m2{0};

  public:
    explicit TimeVaryingSecondOrderSVFBaseCoefficients(gsl::index nb_channels);

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
  class TimeVaryingSecondOrderSVFLowPassCoefficients : public TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::Q;

    explicit TimeVaryingSecondOrderSVFLowPassCoefficients(gsl::index nb_channels);

  protected:
    void update_coeffs(DataType g) const;
  };

  /// Coefficients for a second order SVF band-pass filter
  template<typename DataType_>
  class TimeVaryingSecondOrderSVFBandPassCoefficients : public TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::Q;

    explicit TimeVaryingSecondOrderSVFBandPassCoefficients(gsl::index nb_channels);

  protected:
    void update_coeffs(DataType g) const;
  };

  /// Coefficients for a second order SVF high-pass filter
  template<typename DataType_>
  class TimeVaryingSecondOrderSVFHighPassCoefficients : public TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::Q;

    explicit TimeVaryingSecondOrderSVFHighPassCoefficients(gsl::index nb_channels);

  protected:
    void update_coeffs(DataType g) const;
  };

  /// Coefficients for a second order SVF notch filter
  template<typename DataType_>
  class TimeVaryingSecondOrderSVFNotchCoefficients : public TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::Q;

    explicit TimeVaryingSecondOrderSVFNotchCoefficients(gsl::index nb_channels);

  protected:
    void update_coeffs(DataType g) const;
  };

  /// Coefficients for a second order SVF peak filter
  template<typename DataType_>
  class TimeVaryingSecondOrderSVFPeakCoefficients : public TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::Q;

    explicit TimeVaryingSecondOrderSVFPeakCoefficients(gsl::index nb_channels);

  protected:
    void update_coeffs(DataType g) const;
  };

  /// Coefficients for a second order SVF bell filter
  template<typename DataType_>
  class TimeVaryingSecondOrderSVFBellCoefficients : public TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::Q;

    explicit TimeVaryingSecondOrderSVFBellCoefficients(gsl::index nb_channels);

    /// Sets the gain of the bell
    void set_gain(DataType_ gain);
    /// Returns the gain for the bell
    DataType_ get_gain() const;
  protected:
    void update_coeffs(DataType g) const;

    DataType gain{1};
  };

  /// Coefficients for a second order SVF low-pass shelving filter
  template<typename DataType_>
  class TimeVaryingSecondOrderSVFLowShelfCoefficients : public TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::Q;

    explicit TimeVaryingSecondOrderSVFLowShelfCoefficients(gsl::index nb_channels);

    /// Sets the gain of the shelf
    void set_gain(DataType_ gain);
    /// Returns the gain for the shelf
    DataType_ get_gain() const;
  protected:
    void update_coeffs(DataType g) const;

    DataType gain{0};
  };

  /// Coefficients for a second order SVF high-pass shelving filter
  template<typename DataType_>
  class TimeVaryingSecondOrderSVFHighShelfCoefficients : public TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>
  {
  public:
    using Parent = TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::a1;
    using Parent::a2;
    using Parent::a3;
    using Parent::m0;
    using Parent::m1;
    using Parent::m2;
    using Parent::Q;

    explicit TimeVaryingSecondOrderSVFHighShelfCoefficients(gsl::index nb_channels);
    
    /// Sets the gain of the shelf
    void set_gain(DataType_ gain);
    /// Returns the gain for the shelf
    DataType_ get_gain() const;

  protected:
    void update_coeffs(DataType g) const;

    DataType gain{0};
  };
}

#endif
