 /**
 * \file Chebyshev1Filter.h
 */

#ifndef ATK_EQ_CHEBYSHEV1FILTER_H
#define ATK_EQ_CHEBYSHEV1FILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class Chebyshev1LowPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    DataType cut_frequency;
    DataType ripple;
    
    int in_order;
    int out_order;
    
    void setup() override;
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    Chebyshev1LowPassCoefficients(int nb_channels = 1);
    
    void set_cut_frequency(DataType_ cut_frequency);
    DataType_ get_cut_frequency() const;
    void set_ripple(DataType_ cut_frequency);
    DataType_ get_ripple() const;
    
    void set_order(int order);
  };
  
  template<typename DataType_>
  class Chebyshev1HighPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    DataType cut_frequency;
    DataType ripple;

    int in_order;
    int out_order;
    
    void setup() override;
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    Chebyshev1HighPassCoefficients(int nb_channels = 1);
    
    void set_cut_frequency(DataType_ cut_frequency);
    DataType_ get_cut_frequency() const;
    void set_ripple(DataType_ cut_frequency);
    DataType_ get_ripple() const;
    
    void set_order(int order);
  };
  
  template<typename DataType_>
  class Chebyshev1BandPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    std::pair<DataType, DataType> cut_frequencies;
    DataType ripple;

    int in_order;
    int out_order;
    
    void setup() override;
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    Chebyshev1BandPassCoefficients(int nb_channels = 1);
    
    void set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies);
    void set_cut_frequencies(DataType_ f0, DataType_ f1);
    std::pair<DataType_, DataType_> get_cut_frequencies() const;
    void set_ripple(DataType_ cut_frequency);
    DataType_ get_ripple() const;

    void set_order(int order);
  };
  
  template<typename DataType_>
  class Chebyshev1BandStopCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    std::pair<DataType, DataType> cut_frequencies;
    DataType ripple;

    int in_order;
    int out_order;
    
    void setup() override;
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    Chebyshev1BandStopCoefficients(int nb_channels = 1);
    
    void set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies);
    void set_cut_frequencies(DataType_ f0, DataType_ f1);
    std::pair<DataType_, DataType_> get_cut_frequencies() const;
    void set_ripple(DataType_ cut_frequency);
    DataType_ get_ripple() const;

    void set_order(int order);
  };
}

#endif
