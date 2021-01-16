/**
 * \file InWavFilter.cpp
 */

#include "InWavFilter.h"
#include <ATK/Core/Utilities.h>

#include <stdexcept>

namespace
{
  template<typename DataType1, typename DataType2>
  void convert(std::vector<std::vector<DataType1> >& outputs, const std::vector<char>& inputs)
  {
    gsl::index nbChannels = outputs.size();
    gsl::index size = outputs[0].size();
    for(gsl::index j = 0; j < nbChannels; ++j)
    {
      ATK::ConversionUtilities<DataType2, DataType1>::convert_array(reinterpret_cast<const DataType2*>(inputs.data()), outputs[j].data(), size, j, static_cast<int>(nbChannels));
    }
  }
}

namespace ATK
{
  template<typename DataType>
  InWavFilter<DataType>::InWavFilter(const std::string& filename)
  :TypedBaseFilter<DataType>(0, 0), filename(filename)
  {
    wavstream.open(filename, std::ios_base::binary);
    if(!wavstream.good())
    {
      throw RuntimeError("Could not open WAV file " + filename);
    }
    // Read wave header
    wavstream.read(reinterpret_cast<char*>(&header), sizeof(WavHeader));

    // Get the format block
    wavstream.read(reinterpret_cast<char*>(&format), 4+4);
    if(format.FormatBlocID[0] != 'f') // OK, assume we have bext instead
    {
      wavstream.seekg(static_cast<int32_t>(wavstream.tellg()) + format.BlocSize);
      wavstream.read(reinterpret_cast<char*>(&format), sizeof(WavFormat));
    }
    else
    {
      wavstream.read(reinterpret_cast<char*>(&format) + 4 + 4, sizeof(WavFormat) - 4 - 4);
    }

    // Get the data block
    wavstream.read(reinterpret_cast<char*>(&data), sizeof(WavData));
    while(data.DataBlocID[0] != 'd')
    {
      wavstream.seekg(static_cast<int32_t>(wavstream.tellg()) + data.DataSize);
      wavstream.read(reinterpret_cast<char*>(&data), sizeof(WavData));
    }

    offset = wavstream.tellg();
    wavstream.close();

    set_nb_output_ports(format.NbChannels);
    set_output_sampling_rate(format.Frequence);
    temp_arrays.resize(format.NbChannels);
  }

  template<typename DataType>
  void InWavFilter<DataType>::process_impl(gsl::index size) const
  {
    assert(output_sampling_rate == format.Frequence);
    read_from_file(size);

    for(gsl::index i = 0; i < size; ++i)
    {
      for(gsl::index j = 0; j < format.NbChannels; ++j)
      {
        outputs[j][i] = temp_arrays[j][i];
      }
    }
  }
  
  template<typename DataType>
  void InWavFilter<DataType>::read_from_file(gsl::index size) const
  {
    if(!wavstream.is_open())
    {
      wavstream.open(filename, std::ios_base::binary);
      wavstream.seekg(offset);
    }
    std::vector<char> buffer(size * format.NbChannels * format.BitsPerSample / 8);
    wavstream.read(buffer.data(), buffer.size());

    if(temp_arrays[0].size() != static_cast<gsl::index>(size))
    {
      for(gsl::index j = 0; j < format.NbChannels; ++j)
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
      throw RuntimeError("Don't know how to process bits per sample=" + std::to_string(format.BitsPerSample));
    }
  }
  
#if ATK_ENABLE_INSTANTIATION
  template class InWavFilter<std::int16_t>;
  template class InWavFilter<std::int32_t>;
  template class InWavFilter<int64_t>;
#endif
  template class InWavFilter<float>;
  template class InWavFilter<double>;
}
