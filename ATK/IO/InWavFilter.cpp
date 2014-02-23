/**
 * \file InWavFilter.cpp
 */

#include "InWavFilter.h"

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
    set_nb_output_ports(format.NbrCanaux);
  }

  template<typename DataType>
  void InWavFilter<DataType>::process_impl(long size)
  {
    assert(output_sampling_rate == format.Frequence);
    
  }
  
  template class InWavFilter<std::int16_t>;
  template class InWavFilter<std::int32_t>;
  template class InWavFilter<std::int64_t>;
  template class InWavFilter<float>;
  template class InWavFilter<double>;
}
