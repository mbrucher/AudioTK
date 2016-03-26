/**
 * \file OutWavFilter.h
 */

#ifndef ATK_IO_OUTWAVFILTER_H
#define ATK_IO_OUTWAVFILTER_H

#include <fstream>
#include <string>

#include <ATK/Core/TypedBaseFilter.h>

#include "config.h"
#include "WavStruct.h"

namespace ATK
{
  /// Simple wav sink, not as robust as the SndFile version
  template<typename DataType_>
  class ATK_IO_EXPORT OutWavFilter: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    using Parent::set_nb_output_ports;
    using Parent::nb_output_ports;

  private:
    mutable std::ofstream wavstream;
    
    std::vector<std::vector<DataType> > temp_arrays;

  protected:
    void setup() override final;
    /// Write sthe wav standard header
    void write_header() const;
    void process_impl(int64_t size) const override final;

  public:
    /*!
     * @brief Constructor
     * @param filename is the name of the output file
     */
    OutWavFilter(const std::string& filename);
    
    virtual void set_nb_input_ports(int nb_ports) override final;
  };
}
#endif
