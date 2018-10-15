/**
 * \file MuteSoloBufferFilter.h
 */

#ifndef ATK_TOOLS_MUTESOLOBUFFERFILTER_H
#define ATK_TOOLS_MUTESOLOBUFFERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

#include <boost/dynamic_bitset.hpp>

namespace ATK
{
  /// Buffers input signals
  /**
   * Class that buffers input signal and allows mute/solo operations
   */
  template<typename DataType_>
  class ATK_TOOLS_EXPORT MuteSoloBufferFilter final : public TypedBaseFilter<DataType_>
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
    MuteSoloBufferFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~MuteSoloBufferFilter() override;
    
    /// Mutes/unmutes a given channel (outputs 0)
    void set_mute(gsl::index channel, bool mute);
    /// Returns the mute status of a channel
    bool get_mute(gsl::index channel) const;
    /// Soloes/unsoloes a given channel (outputs 0 on the other non soloed channels)
    void set_solo(gsl::index channel, bool solo);
    /// Returns the solo status of a channel
    bool get_solo(gsl::index channel) const;
    
    void set_nb_input_ports(gsl::index nb_ports) final;
    void set_nb_output_ports(gsl::index nb_ports) final;

  protected:
    void process_impl(gsl::index size) const final;
    
  private:
    boost::dynamic_bitset<> mute_statuses;
    boost::dynamic_bitset<> solo_statuses;
    bool any_solo;
  };
}

#endif
