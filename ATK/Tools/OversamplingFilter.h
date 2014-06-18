/**
 * \file OversamplingFilter.h
 * Inspired by http://yehar.com/blog/wp-content/uploads/2009/08/deip.pdf
 */

#ifndef ATK_TOOLS_OVERSAMPLINGFILTER_H
#define ATK_TOOLS_OVERSAMPLINGFILTER_H

#include "../Core/TypedBaseFilter.h"
#include "config.h"

namespace ATK
{
  template<class DataType_>
  class Oversampling6points5order_2
  {
  public:
    typedef DataType_ DataType;
    
    static const int points = 6;
    static const int order = 5;
    static const int oversampling_factor = 2;
    
  public:
    DataType coeffs[order + 1][points / 2];
    
  public:
    Oversampling6points5order_2();
  };
  
  template<class DataType_>
  class Oversampling6points5order_4
  {
  public:
    typedef DataType_ DataType;
    
    static const int points = 6;
    static const int order = 5;
    static const int oversampling_factor = 4;
    
  public:
    DataType coeffs[order + 1][points / 2];
    
  public:
    Oversampling6points5order_4();
  };
  
  template<class DataType_>
  class Oversampling6points5order_8
  {
  public:
    typedef DataType_ DataType;
    
    static const int points = 6;
    static const int order = 5;
    static const int oversampling_factor = 8;
    
  public:
    DataType coeffs[order + 1][points / 2];
    
  public:
    Oversampling6points5order_8();
  };
  
  template<class DataType_>
  class Oversampling6points5order_16
  {
  public:
    typedef DataType_ DataType;
    
    static const int points = 6;
    static const int order = 5;
    static const int oversampling_factor = 16;
    
  public:
    DataType coeffs[order + 1][points / 2];
    
  public:
    Oversampling6points5order_16();
  };
  
  template<class DataType_>
  class Oversampling6points5order_32
  {
  public:
    typedef DataType_ DataType;
    
    static const int points = 6;
    static const int order = 5;
    static const int oversampling_factor = 32;
    
  public:
    DataType coeffs[order + 1][points / 2];
    
  public:
    Oversampling6points5order_32();
  };

  template<class DataType_, class Coefficients>
  class ATK_TOOLS_EXPORT OversamplingFilter : public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_delay;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  private:
    Coefficients coeffs;
  public:
    OversamplingFilter(int nb_channels = 1);
    
    virtual void process_impl(std::int64_t size);
  };
}

#endif
