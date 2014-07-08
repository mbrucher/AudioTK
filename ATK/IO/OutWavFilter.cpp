/**
 * \file OutWavFilter.cpp
 */

#include "OutWavFilter.h"

#include <cstring>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <ATK/Core/Utilities.h>

namespace
{
  template<typename DataType1, typename DataType2>
  void convert(std::vector<std::vector<DataType1> >& outputs, const std::vector<char>& inputs)
  {
    int nbChannels = outputs.size();
    std::int64_t size = outputs[0].size();
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
    wavstream.open(filename.c_str(), std::ios_base::binary);
    if(!wavstream.good())
    {
      throw std::runtime_error("Could not WAV file " + filename);
    }
  }

  template<typename DataType>
  void OutWavFilter<DataType>::process_impl(std::int64_t size)
  {
    std::size_t nb_inputs = converted_inputs.size();
    std::vector<DataType> buffer(nb_inputs * size);
    
    for(std::int64_t i = 0; i < size; ++i)
    {
      for(std::size_t j = 0; j < nb_inputs; ++j)
      {
        buffer[j + i * nb_inputs] = converted_inputs[j][i];
      }
    }
    
    wavstream.write(reinterpret_cast<const char*>(buffer.data()), buffer.size() * sizeof(DataType));
    write_header();
  }
  
  template<typename DataType>
  void OutWavFilter<DataType>::set_nb_input_ports(int nb_ports)
  {
    Parent::set_nb_input_ports(nb_ports);
    format.NbChannels = nb_ports;
    setup();
  }
  
  template<typename DataType>
  void OutWavFilter<DataType>::setup()
  {
    std::strncpy(header.FileTypeBlocID, "RIFF", 4);
    std::strncpy(header.FileFormatID, "WAVE", 4);
    std::strncpy(format.FormatBlocID, "fmt ", 4);
    std::strncpy(data.DataBlocID, "data", 4);
    format.AudioFormat = WavTraits<DataType>::get_wav_type();
    format.Frequence = input_sampling_rate;
    format.BitsPerSample = sizeof(DataType) * 8;
    format.BytePerBloc = format.NbChannels * format.BitsPerSample / 8;
    format.BytePerSec = format.BytePerBloc * input_sampling_rate;
    write_header();
  }
  
  template<typename DataType>
  void OutWavFilter<DataType>::write_header()
  {
    std::size_t total_size = wavstream.tellp();
    std::size_t bloc_size = sizeof(WavFormat);
    std::size_t data_size = total_size - sizeof(WavFormat) - sizeof(WavHeader) - sizeof(WavData);
    wavstream.seekp(0);
    header.FileSize = static_cast<std::int32_t>(total_size - 8);
    format.BlocSize = static_cast<std::int32_t>(bloc_size - 8);
    data.DataSize = static_cast<std::int32_t>(data_size);
    wavstream.write(reinterpret_cast<char*>(&header), sizeof(WavHeader));
    wavstream.write(reinterpret_cast<char*>(&format), sizeof(WavFormat));
    wavstream.write(reinterpret_cast<char*>(&data), sizeof(WavData));
    wavstream.seekp(0, std::ios_base::end);
  }

  template class OutWavFilter<std::int16_t>;
  template class OutWavFilter<float>;
  template class OutWavFilter<double>;
}
