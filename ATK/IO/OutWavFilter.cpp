/**
 * \file OutWavFilter.cpp
 */

#include "OutWavFilter.h"

#include <cstring>

#include <boost/lexical_cast.hpp>

#include <ATK/Core/Utilities.h>

namespace
{
  template<typename DataType1, typename DataType2>
  void convert(std::vector<std::vector<DataType1> >& outputs, const std::vector<char>& inputs)
  {
    int nbChannels = outputs.size();
    long size = outputs[0].size();
    for(int j = 0; j < nbChannels; ++j)
    {
      ATK::ConversionUtilities<DataType2, DataType1>::convert_array(reinterpret_cast<const DataType2*>(inputs.data() + j * sizeof(DataType2)), outputs[j].data(), size, nbChannels);
    }
  }
}

namespace ATK
{
  template<typename DataType>
  OutWavFilter<DataType>::OutWavFilter(const std::string& filename)
  :TypedBaseFilter<DataType>(0, 0)
  {
    wavstream.open(filename.c_str());
    if(!wavstream.good())
    {
      throw std::runtime_error("Could not WAV file " + filename);
    }
  }

  template<typename DataType>
  void OutWavFilter<DataType>::process_impl(long size)
  {
  }
  
  template<typename DataType>
  void OutWavFilter<DataType>::set_nb_input_ports(int nb_ports)
  {
    Parent::set_nb_input_ports(nb_ports);
    format.NbChannels = nb_ports;
  }
  
  template<typename DataType>
  void OutWavFilter<DataType>::set_bits_per_sample(int bits_per_sample)
  {
    format.BitsPerSample = bits_per_sample;
  }
  
  template<typename DataType>
  void OutWavFilter<DataType>::setup()
  {
    format.Frequence = input_sampling_rate;
    std::strncpy(header.FileTypeBlocID, "RIFF", 4);
    std::strncpy(header.FileFormatID, "WAVE", 4);
    std::strncpy(format.FormatBlocID, "fmt ", 4);
    std::strncpy(data.DataBlocID, "data", 4);
  }

  template class OutWavFilter<std::int16_t>;
  template class OutWavFilter<std::int32_t>;
  template class OutWavFilter<std::int64_t>;
  template class OutWavFilter<float>;
  template class OutWavFilter<double>;
}
