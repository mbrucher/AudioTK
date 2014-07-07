/**
 * \file InWavFilter.cpp
 */

#include "InWavFilter.h"

#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <ATK/Core/Utilities.h>

namespace
{
  template<typename DataType1, typename DataType2>
  void convert(std::vector<std::vector<DataType1> >& outputs, const std::vector<char>& inputs)
  {
    std::size_t nbChannels = outputs.size();
    std::int64_t size = outputs[0].size();
    for(std::size_t j = 0; j < nbChannels; ++j)
    {
      ATK::ConversionUtilities<DataType2, DataType1>::convert_array(reinterpret_cast<const DataType2*>(inputs.data()), outputs[j].data(), size, j, nbChannels);
    }
  }
}

namespace ATK
{
  template<typename DataType>
  InWavFilter<DataType>::InWavFilter(const std::string& filename)
  :TypedBaseFilter<DataType>(0, 0), filename(filename)
  {
    wavstream.open(filename.c_str(), std::ios_base::binary);
    if(!wavstream.good())
    {
      throw std::runtime_error("Could not open WAV file " + filename);
    }
    wavstream.read(reinterpret_cast<char*>(&header), sizeof(WavHeader) + sizeof(WavFormat) + sizeof(WavData));
    wavstream.close();

    set_nb_output_ports(format.NbChannels);
    set_output_sampling_rate(format.Frequence);
    temp_arrays.resize(format.NbChannels);
  }

  template<typename DataType>
  void InWavFilter<DataType>::process_impl(std::int64_t size)
  {
    assert(output_sampling_rate == format.Frequence);
    read_from_file(size);

    for(std::int64_t i = 0; i < size; ++i)
    {
      for(int j = 0; j < format.NbChannels; ++j)
      {
        outputs[j][i] = temp_arrays[j][i];
      }
    }
  }
  
  template<typename DataType>
  void InWavFilter<DataType>::read_from_file(std::int64_t size)
  {
    if(!wavstream.is_open())
    {
      wavstream.open(filename.c_str(), std::ios_base::binary);
      wavstream.seekg(sizeof(WavHeader) + sizeof(WavFormat) + sizeof(WavData));
    }
    std::vector<char> buffer(size * format.NbChannels * format.BitsPerSample / 8);
    wavstream.read(buffer.data(), buffer.size());

    if(temp_arrays[0].size() != static_cast<std::size_t>(size))
    {
      for(int j = 0; j < format.NbChannels; ++j)
      {
        temp_arrays[j].resize(size);
      }
    }
    
    switch(format.BitsPerSample)
    {
      case 8:
        convert<DataType, std::int8_t>(temp_arrays, buffer);
        break;
      case 16:
        convert<DataType, std::int16_t>(temp_arrays, buffer);
        break;
      case 24:
        convert<DataType, char[3]>(temp_arrays, buffer);
        break;
      case 32:
        convert<DataType, float>(temp_arrays, buffer);
        break;
      case 64:
        convert<DataType, double>(temp_arrays, buffer);
        break;
      default:
        throw std::runtime_error("Don't know how to process bits per sample=" + boost::lexical_cast<std::string>(format.BitsPerSample));
    }
  }
  
  template class InWavFilter<std::int16_t>;
  template class InWavFilter<std::int32_t>;
  template class InWavFilter<std::int64_t>;
  template class InWavFilter<float>;
  template class InWavFilter<double>;
}
