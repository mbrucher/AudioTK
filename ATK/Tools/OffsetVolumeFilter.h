/**
 * \file OffsetVolumeFilter.h
 */

#ifndef ATK_TOOLS_OFFSETVOLUMEFILTER_H
#define ATK_TOOLS_OFFSETVOLUMEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Scales a signal
  template<typename DataType_>
  class ATK_TOOLS_EXPORT OffsetVolumeFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    OffsetVolumeFilter(int nb_channels = 1);
    /// Destructor
    ~OffsetVolumeFilter();

    /// Sets the output volume, doesn't update the cache
    void set_volume(DataType_ volume);
    /// Gets the output volume
    DataType_ get_volume() const;

    /// Sets the offset of the generated signal, doesn't update the cache
    void set_offset(DataType_ offset);
    /// Gets the offset
    DataType_ get_offset() const;

  protected:
    virtual void process_impl(int64_t size) const override final;
    
  private:
    DataType_ volume;
    DataType_ offset;
  };
}

#endif
