/**
 * \file OutWavFilter.h
 */

#ifndef ATK_IO_OUTWAVFILTER_H
#define ATK_IO_OUTWAVFILTER_H

#include <fstream>
#include <string>

#include <ATK/Core/TypedBaseFilter.h>

#include <ATK/IO/config.h>
#include <ATK/IO/WavStruct.h>

namespace ATK
{
  /// Simple wav sink, not as robust as the SndFile version
  template<typename DataType_>
  class ATK_IO_EXPORT OutWavFilter final : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    using Parent::nb_input_ports;

  private:
    mutable std::ofstream wavstream;
    
    std::vector<std::vector<DataType> > temp_arrays;

  protected:
    void setup() final;
    /// Write sthe wav standard header
    void write_header() const;
    void process_impl(std::size_t size) const final;

  public:
    /*!
     * @brief Constructor
     * @param filename is the name of the output file
     */
    OutWavFilter(const std::string& filename);
    
    void set_nb_input_ports(std::size_t nb_ports) final;
  };
}
#endif
