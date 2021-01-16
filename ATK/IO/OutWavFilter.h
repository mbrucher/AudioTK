/**
 * \file OutWavFilter.h
 */

#ifndef ATK_IO_OUTWAVFILTER_H
#define ATK_IO_OUTWAVFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/IO/config.h>
#include <ATK/IO/WavStruct.h>

#include <fstream>
#include <string>

namespace ATK
{
  /// Simple wav sink, not as robust as the SndFile version
  template<typename DataType_>
  class ATK_IO_EXPORT OutWavFilter final : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
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
    void process_impl(gsl::index size) const final;

  public:
    /*!
     * @brief Constructor
     * @param filename is the name of the output file
     */
    explicit OutWavFilter(const std::string& filename);
    
    void set_nb_input_ports(gsl::index nb_ports) final;
  };
}
#endif
