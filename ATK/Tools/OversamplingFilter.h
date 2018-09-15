/**
 * \file OversamplingFilter.h
 * Inspired by http://yehar.com/blog/wp-content/uploads/2009/08/deip.pdf
 */

#ifndef ATK_TOOLS_OVERSAMPLINGFILTER_H
#define ATK_TOOLS_OVERSAMPLINGFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Used for an oversampling rate of 2
  template<class DataType_>
  class Oversampling6points5order_2
  {
  public:
    /// To be used by inherited APIs
    typedef DataType_ DataType;
    
    /// Number of points for the filter
    static const int points = 6;
    /// Order of the filter
    static const int order = 5;
    /// Oversampling rate
    static const int oversampling_factor = 2;

    typename TypeTraits<DataType>::Scalar coeffs[order + 1][points / 2];
    
    /// Constructor
    Oversampling6points5order_2();
  };
  
  /// Used for an oversampling rate of 4
  template<class DataType_>
  class Oversampling6points5order_4
  {
  public:
    /// To be used by inherited APIs
    typedef DataType_ DataType;
    
    /// Number of points for the filter
    static const int points = 6;
    /// Order of the filter
    static const int order = 5;
    /// Oversampling rate
    static const int oversampling_factor = 4;
    
    /// Coefficients used by OversamplingFilter
    typename TypeTraits<DataType>::Scalar coeffs[order + 1][points / 2];
    
    /// Constructor
    Oversampling6points5order_4();
  };
  
  /// Used for an oversampling rate of 8
  template<class DataType_>
  class Oversampling6points5order_8
  {
  public:
    /// To be used by inherited APIs
    typedef DataType_ DataType;
    
    /// Number of points for the filter
    static const int points = 6;
    /// Order of the filter
    static const int order = 5;
    /// Oversampling rate
    static const int oversampling_factor = 8;
    
    /// Coefficients used by OversamplingFilter
    typename TypeTraits<DataType>::Scalar coeffs[order + 1][points / 2];
    
    /// Constructor
    Oversampling6points5order_8();
  };
  
  /// Used for an oversampling rate of 16
  template<class DataType_>
  class Oversampling6points5order_16
  {
  public:
    /// To be used by inherited APIs
    typedef DataType_ DataType;
    
    /// Number of points for the filter
    static const int points = 6;
    /// Order of the filter
    static const int order = 5;
    /// Oversampling rate
    static const int oversampling_factor = 16;
    
    /// Coefficients used by OversamplingFilter
    typename TypeTraits<DataType>::Scalar coeffs[order + 1][points / 2];
    
    /// Constructor
    Oversampling6points5order_16();
  };
  
  /// Used for an oversampling rate of 32
  template<class DataType_>
  class Oversampling6points5order_32
  {
  public:
    /// To be used by inherited APIs
    typedef DataType_ DataType;
    
    /// Number of points for the filter
    static const int points = 6;
    /// Order of the filter
    static const int order = 5;
    /// Oversampling rate
    static const int oversampling_factor = 32;
    
    /// Coefficients used by OversamplingFilter
    typename TypeTraits<DataType>::Scalar coeffs[order + 1][points / 2];
    
    /// Constructor
    Oversampling6points5order_32();
  };

  /// The base class for oversampling, given a coefficient class, changing the output rate by a constant power of 2
  template<class DataType_, class Coefficients>
  class ATK_TOOLS_EXPORT OversamplingFilter final : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_delay;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  private:
    Coefficients coeffs;

    void process_one_channel(gsl::index size, const DataType* ATK_RESTRICT input, DataType* ATK_RESTRICT output) const;
  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    OversamplingFilter(gsl::index nb_channels = 1);
    
    void process_impl(gsl::index size) const final;
  };
}

#endif
