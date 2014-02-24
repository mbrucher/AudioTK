/**
 * \file InWavFilter.cpp
 */

#include "InWavFilter.h"

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
  InWavFilter<DataType>::InWavFilter(const std::string& filename)
  :TypedBaseFilter<DataType>(0, 0)
  {
    wavstream.open(filename.c_str());
    if(!wavstream.good())
    {
      throw std::runtime_error("Could not WAV file " + filename);
    }
    wavstream.read(reinterpret_cast<char*>(&header), sizeof(WavHeader) + sizeof(WavFormat) + sizeof(WavData));
    set_nb_output_ports(format.NbChannels);
    temp_arrays.resize(format.NbChannels);
  }

  template<typename DataType>
  void InWavFilter<DataType>::process_impl(long size)
  {
    assert(output_sampling_rate == format.Frequence);
    read_from_file(size);

    for(long i = 0; i < size; ++i)
    {
      for(int j = 0; j < format.NbChannels; ++j)
      {
        outputs[j][i] = temp_arrays[j][i]; // FIXME add interpolation + there will be lag
      }
    }
  }
  
  template<typename DataType>
  void InWavFilter<DataType>::read_from_file(long size)
  {
    std::vector<char> buffer(size * format.NbChannels * format.BitsPerSample / 8);
    wavstream.read(buffer.data(), buffer.size());
    
    if(temp_arrays[0].size() < size)
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
