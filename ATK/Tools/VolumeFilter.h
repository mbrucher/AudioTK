/**
 * \file VolumeFilter.h
 */

#ifndef ATK_TOOLS_VOLUMEFILTER_H
#define ATK_TOOLS_VOLUMEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Scales input signals
  template<typename DataType_>
  class ATK_TOOLS_EXPORT VolumeFilter final : public TypedBaseFilter<DataType_>
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
    explicit VolumeFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~VolumeFilter() override = default;

    /// Changes the output volume
    void set_volume(DataType_ volume);
    /// Sets the output volume in dB
    void set_volume_db(double volume_db);
    /// Gets the output volume
    DataType_ get_volume() const;
    
  protected:
    void process_impl(gsl::index size) const final;
    
  private:
    DataType_ volume{1};
  };
}

#endif
