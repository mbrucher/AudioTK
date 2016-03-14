/**
 * \file LinkwitzRileyFilter.h
 */

#ifndef ATK_EQ_LINKWITZRILEYFILTER_H
#define ATK_EQ_LINKWITZRILEYFILTER_H

#include <ATK/EQ/SecondOrderFilter.h>

namespace ATK
{
  /// Linkwitz-Riley low pass filter coefficients to be used with IIRFilter
  /*!
   * Used with the high pass set at the same frequency, the resulting output is a flat spectrum
   */
  template<typename DataType_>
  class LinkwitzRileyLowPassCoefficients : public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    void setup() override;
        
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    LinkwitzRileyLowPassCoefficients(int nb_channels = 1);
  };

  /// Linkwitz-Riley high pass filter coefficients to be used with IIRFilter
  /*!
  * Used with the low pass set at the same frequency, the resulting output is a flat spectrum
  */
  template<typename DataType_>
  class LinkwitzRileyHighPassCoefficients : public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    LinkwitzRileyHighPassCoefficients(int nb_channels = 1);
  };
}

#endif
