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
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    DataType cut_frequency;
    
    int in_order;
    int out_order;
    
    void setup() override;
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    ButterworthLowPassCoefficients(int nb_channels = 1);
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    
    void set_order(int order);
  };

  template<typename DataType_>
  class ButterworthHighPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    DataType cut_frequency;
    
    int in_order;
    int out_order;
    
    void setup() override;
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    ButterworthHighPassCoefficients(int nb_channels = 1);
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    
    void set_order(int order);
  };

  template<typename DataType_>
  class ButterworthBandPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    std::pair<DataType, DataType> cut_frequencies;
    
    int in_order;
    int out_order;
    
    void setup() override;
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    ButterworthBandPassCoefficients(int nb_channels = 1);
    
    void set_cut_frequencies(std::pair<DataType, DataType> cut_frequencies);
    void set_cut_frequencies(DataType f0, DataType f1);
    std::pair<DataType, DataType> get_cut_frequencies() const;
    
    void set_order(int order);
  };
  
  template<typename DataType_>
  class ButterworthBandStopCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    std::pair<DataType, DataType> cut_frequencies;
    
    int in_order;
    int out_order;
    
    void setup() override;
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    ButterworthBandStopCoefficients(int nb_channels = 1);
    
    void set_cut_frequencies(std::pair<DataType, DataType> cut_frequencies);
    void set_cut_frequencies(DataType f0, DataType f1);
    std::pair<DataType, DataType> get_cut_frequencies() const;
    
    void set_order(int order);
  };
}

#endif
