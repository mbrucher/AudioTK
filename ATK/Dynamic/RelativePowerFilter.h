/**
 * \file RelativePowerFilter.h
 */

#ifndef ATK_DYNAMIC_RELATIVEPOWERFILTER_H
#define ATK_DYNAMIC_RELATIVEPOWERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Dynamic/config.h>

namespace ATK
{
  /// Creates an output signal with the relative filtered power of the input (computed with an AR1)
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT RelativePowerFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    explicit RelativePowerFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~RelativePowerFilter() override;

    /// Sets the memory of the AR1 (must be between 0 and 1)
    void set_memory(DataType_ memory_factor);
    /// gets the memory factor
    DataType_ get_memory() const;
    
  protected:
    void process_impl(gsl::index size) const final;
    
  private:
    DataType_ memory_factor;
    mutable DataType_ temp_output;
  };
}

#endif
