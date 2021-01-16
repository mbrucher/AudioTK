/**
 * \file OutWavFilter.cpp
 */

#include "OutWavFilter.h"
#include <ATK/Core/Utilities.h>

#include <cstring>
#include <stdexcept>

namespace
{
  template<typename DataType1, typename DataType2>
  void convert(std::vector<std::vector<DataType1> >& outputs, const std::vector<char>& inputs)
  {
    int nbChannels = outputs.size();
    int64_t size = outputs[0].size();
    for(gsl::index j = 0; j < nbChannels; ++j)
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
    wavstream.open(filename, std::ios_base::binary);
    if(!wavstream.good())
    {
      throw RuntimeError("Could not WAV file " + filename);
    }
  }

  template<typename DataType>
  void OutWavFilter<DataType>::process_impl(gsl::index size) const
  {
    gsl::index nb_inputs = converted_inputs.size();
    std::vector<DataType> buffer(nb_inputs * size);
    
    for(gsl::index i = 0; i < size; ++i)
    {
      for(gsl::index j = 0; j < nb_inputs; ++j)
      {
        buffer[j + i * nb_inputs] = converted_inputs[j][i];
      }
    }
    
    wavstream.write(reinterpret_cast<const char*>(buffer.data()), buffer.size() * sizeof(DataType));
    write_header();
  }
  
  template<typename DataType>
  void OutWavFilter<DataType>::set_nb_input_ports(gsl::index nb_ports)
  {
    Parent::set_nb_input_ports(nb_ports);
    setup();
  }
  
  template<typename DataType>
  void OutWavFilter<DataType>::setup()
  {
    write_header();
  }
  
  template<typename DataType>
  void OutWavFilter<DataType>::write_header() const
  {
    WavHeader header;
    WavFormat format;
    WavData data;
 
    std::strncpy(header.FileTypeBlocID, "RIFF", 4);
    std::strncpy(header.FileFormatID, "WAVE", 4);
    std::strncpy(format.FormatBlocID, "fmt ", 4);
    std::strncpy(data.DataBlocID, "data", 4);
    format.AudioFormat = WavTraits<DataType>::get_wav_type();
    format.Frequence = static_cast<int32_t>(input_sampling_rate);
    format.BitsPerSample = sizeof(DataType)* 8;
    format.BytePerBloc = format.NbChannels * format.BitsPerSample / 8;
    format.BytePerSec = static_cast<int32_t>(format.BytePerBloc * input_sampling_rate);
    format.NbChannels = static_cast<int16_t>(nb_input_ports);

    gsl::index total_size = wavstream.tellp();
    gsl::index bloc_size = sizeof(WavFormat);
    gsl::index data_size = total_size - sizeof(WavFormat) - sizeof(WavHeader) - sizeof(WavData);
    wavstream.seekp(0);
    header.FileSize = static_cast<std::int32_t>(total_size - 8);
    format.BlocSize = static_cast<std::int32_t>(bloc_size - 8);
    data.DataSize = static_cast<std::int32_t>(data_size);
    wavstream.write(reinterpret_cast<char*>(&header), sizeof(WavHeader));
    wavstream.write(reinterpret_cast<char*>(&format), sizeof(WavFormat));
    wavstream.write(reinterpret_cast<char*>(&data), sizeof(WavData));

    wavstream.seekp(0, std::ios_base::end);
  }

#if ATK_ENABLE_INSTANTIATION
  template class OutWavFilter<std::int16_t>;
  template class OutWavFilter<double>;
#endif
  template class OutWavFilter<float>;
}
