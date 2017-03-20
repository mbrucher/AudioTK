/**
 * \file ButterworthFilter.h
 */

#ifndef ATK_EQ_BUTTERWORTHFILTER_H
#define ATK_EQ_BUTTERWORTHFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class ButterworthLowPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedVector;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    DataType cut_frequency;
    
    unsigned int in_order;
    unsigned int out_order;
    
    void setup() override;
    
    AlignedVector coefficients_in;
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthLowPassCoefficients(unsigned int nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };

  template<typename DataType_>
  class ButterworthHighPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedVector;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    DataType cut_frequency;
    
    unsigned int in_order;
    unsigned int out_order;
    
    void setup() override;
    
    AlignedVector coefficients_in;
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthHighPassCoefficients(unsigned int nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };

  template<typename DataType_>
  class ButterworthBandPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedVector;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    std::pair<DataType, DataType> cut_frequencies;
    
    unsigned int in_order;
    unsigned int out_order;
    
    void setup() override;
    
    AlignedVector coefficients_in;
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthBandPassCoefficients(unsigned int nb_channels = 1);
    
    void set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies);
    void set_cut_frequencies(DataType_ f0, DataType_ f1);
    std::pair<DataType_, DataType_> get_cut_frequencies() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };
  
  template<typename DataType_>
  class ButterworthBandStopCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedVector;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    std::pair<DataType, DataType> cut_frequencies;
    
    unsigned int in_order;
    unsigned int out_order;
    
    void setup() override;
    
    AlignedVector coefficients_in;
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthBandStopCoefficients(unsigned int nb_channels = 1);
    
    void set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies);
    void set_cut_frequencies(DataType_ f0, DataType_ f1);
    std::pair<DataType_, DataType_> get_cut_frequencies() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };
}

#endif
