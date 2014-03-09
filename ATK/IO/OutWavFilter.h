/**
 * \file OutWavFilter.h
 */

#ifndef ATK_IO_OUTWAVFILTER_H
#define ATK_IO_OUTWAVFILTER_H

#include <fstream>
#include <string>

#include <ATK/Core/TypedBaseFilter.h>

#include "WavStruct.h"

namespace ATK
{
  template<typename DataType_>
  class OutWavFilter: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    using Parent::set_nb_output_ports;

  private:
    std::ofstream wavstream;
    WavHeader header;
    WavFormat format;
    WavData data;
    
    std::vector<std::vector<DataType> > temp_arrays;

  protected:
    void setup();
    void write_header();
    
  public:
    OutWavFilter(const std::string& filename);
    
    void process_impl(long size);
    
    virtual void set_nb_input_ports(int nb_ports);
  };
}
#endif
