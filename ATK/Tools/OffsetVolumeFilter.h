/**
 * \file OffsetVolumeFilter.h
 */

#ifndef ATK_TOOLS_OFFSETVOLUMEFILTER_H
#define ATK_TOOLS_OFFSETVOLUMEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Scales a signal
  template<typename DataType_>
  class ATK_TOOLS_EXPORT OffsetVolumeFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    explicit OffsetVolumeFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~OffsetVolumeFilter() override = default;

    /// Sets the output volume, doesn't update the cache
    void set_volume(DataType_ volume);
    /// Gets the output volume
    DataType_ get_volume() const;

    /// Sets the offset of the generated signal, doesn't update the cache
    void set_offset(DataType_ offset);
    /// Gets the offset
    DataType_ get_offset() const;

  protected:
    void process_impl(gsl::index size) const final;
    
  private:
    DataType_ volume{1};
    DataType_ offset{0};
  };
}

#endif
