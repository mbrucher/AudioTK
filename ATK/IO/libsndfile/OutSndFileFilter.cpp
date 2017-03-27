/**
 * \file OutSndFileFilter.cpp
 */

#include "OutSndFileFilter.h"

#include <sndfile.hh>

#include "sndfile_traits.h"

namespace ATK
{
  template<typename DataType>
  OutSndFileFilter<DataType>::OutSndFileFilter(const std::string& filename, int ports)
  :TypedBaseFilter<DataType>(0, 0), filename(filename)
  {
    set_nb_input_ports(ports);
  }
  
  template<typename DataType>
  void OutSndFileFilter<DataType>::setup()
  {
    stream.reset(new SndfileHandle(filename.c_str(), SFM_WRITE, SndfileTraits<DataType>::get_type() | SF_FORMAT_WAV, converted_inputs.size(), input_sampling_rate));
    stream->command(SFC_SET_SCALE_INT_FLOAT_WRITE, NULL, 1);
  }
  
  template<typename DataType>
  OutSndFileFilter<DataType>::~OutSndFileFilter()
  {
    
  }
  
  template<typename DataType>
  void OutSndFileFilter<DataType>::process_impl(std::size_t size) const
  {
    std::vector<DataType> temp(size * converted_inputs.size());
    
    for(std::size_t i = 0; i < size; ++i)
    {
      for(std::size_t j = 0; j < converted_inputs.size(); ++j)
      {
        temp[j + i * converted_inputs.size()] = converted_inputs[j][i];
      }
    }
    
    stream->write(temp.data(), size * converted_inputs.size());
  }
  
  template class OutSndFileFilter<std::int16_t>;
  template class OutSndFileFilter<std::int32_t>;
  template class OutSndFileFilter<float>;
  template class OutSndFileFilter<double>;
}
