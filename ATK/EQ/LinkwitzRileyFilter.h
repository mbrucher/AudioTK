/**
 * \file LinkwitzRileyFilter.h
 * 4th order from http://www.musicdsp.org/archive.php?classid=3
 */

#ifndef ATK_EQ_LINKWITZRILEYFILTER_H
#define ATK_EQ_LINKWITZRILEYFILTER_H

#include <ATK/EQ/FourthOrderFilter.h>
#include <ATK/EQ/SecondOrderFilter.h>

namespace ATK
{
  /// Linkwitz-Riley low pass filter coefficients to be used with IIRFilter, 2th order
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
    LinkwitzRileyLowPassCoefficients(std::size_t nb_channels = 1);
  };

  /// Linkwitz-Riley high pass filter coefficients to be used with IIRFilter, 2th order
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
    LinkwitzRileyHighPassCoefficients(std::size_t nb_channels = 1);
  };

  /// Linkwitz-Riley low pass filter coefficients to be used with IIRFilter, 4th order
  /*!
   * Used with the high pass set at the same frequency, the resulting output is a flat spectrum
   */
  template<typename DataType_>
  class LinkwitzRiley4LowPassCoefficients : public FourthOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef FourthOrderBaseCoefficients<DataType_> Parent;
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
    LinkwitzRiley4LowPassCoefficients(std::size_t nb_channels = 1);
  };
  
  /// Linkwitz-Riley high pass filter coefficients to be used with IIRFilter, 4th order
  /*!
   * Used with the low pass set at the same frequency, the resulting output is a flat spectrum
   */
  template<typename DataType_>
  class LinkwitzRiley4HighPassCoefficients : public FourthOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef FourthOrderBaseCoefficients<DataType_> Parent;
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
    LinkwitzRiley4HighPassCoefficients(std::size_t nb_channels = 1);
  };
}

#endif
