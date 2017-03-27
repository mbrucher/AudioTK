/**
 * \file BesselFilter.h
 */

#ifndef ATK_EQ_BESSELFILTER_H
#define ATK_EQ_BESSELFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class BesselLowPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::AlignedVector;
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
    BesselLowPassCoefficients(unsigned int nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };
  
  template<typename DataType_>
  class BesselHighPassCoefficients: public TypedBaseFilter<DataType_>
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
    
    std::vector<DataType, boost::alignment::aligned_allocator<DataType, 32> > coefficients_in;
    std::vector<DataType, boost::alignment::aligned_allocator<DataType, 32> > coefficients_out;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    BesselHighPassCoefficients(unsigned int nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };
  
  template<typename DataType_>
  class BesselBandPassCoefficients: public TypedBaseFilter<DataType_>
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
    
    std::vector<DataType, boost::alignment::aligned_allocator<DataType, 32> > coefficients_in;
    std::vector<DataType, boost::alignment::aligned_allocator<DataType, 32> > coefficients_out;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    BesselBandPassCoefficients(unsigned int nb_channels = 1);
    
    void set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies);
    void set_cut_frequencies(DataType_ f0, DataType_ f1);
    std::pair<DataType_, DataType_> get_cut_frequencies() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };
  
  template<typename DataType_>
  class BesselBandStopCoefficients: public TypedBaseFilter<DataType_>
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
    
    std::vector<DataType, boost::alignment::aligned_allocator<DataType, 32> > coefficients_in;
    std::vector<DataType, boost::alignment::aligned_allocator<DataType, 32> > coefficients_out;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    BesselBandStopCoefficients(unsigned int nb_channels = 1);
    
    void set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies);
    void set_cut_frequencies(DataType_ f0, DataType_ f1);
    std::pair<DataType_, DataType_> get_cut_frequencies() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };
}

#endif
