/**
 * \file VolumeFilter.h
 */

#ifndef ATK_TOOLS_VOLUMEFILTER_H
#define ATK_TOOLS_VOLUMEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Scales input signals
  template<typename DataType_>
  class ATK_TOOLS_EXPORT VolumeFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
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
    VolumeFilter(int nb_channels = 1);
    /// Destructor
    ~VolumeFilter();

    /// Changes the output volume
    void set_volume(double volume);
    /// Sets the output volume in dB
    void set_volume_db(double volume_db);
    
  protected:
    virtual void process_impl(std::size_t size) const override final;
    
  private:
    double volume;
  };
}

#endif
