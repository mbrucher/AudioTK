/**
 * \file ChamberlinFilter.cpp
 */

#include "ChamberlinFilter.h"

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename DataType>
  ChamberlinFilter<DataType>::ChamberlinFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
  }
  
  template<typename DataType_>
  void ChamberlinFilter<DataType_>::set_cut_frequency(CoeffDataType cutoff_frequency)
  {
    this->cutoff_frequency = cutoff_frequency;
    setup();
  }

  template<typename DataType_>
  typename ChamberlinFilter<DataType_>::CoeffDataType ChamberlinFilter<DataType_>::get_cut_frequency() const
  {
    return cutoff_frequency;
  }
  
  template<typename DataType_>
  void ChamberlinFilter<DataType_>::set_attenuation(CoeffDataType attenuation)
  {
    this->attenuation = attenuation;
    setup();
  }

  template<typename DataType_>
  typename ChamberlinFilter<DataType_>::CoeffDataType ChamberlinFilter<DataType_>::get_attenuation() const
  {
    return attenuation;
  }
  
  template<typename DataType>
  void ChamberlinFilter<DataType>::select(int selection)
  {
    this->selected = selection;
  }
  
  template<typename DataType>
  int ChamberlinFilter<DataType>::get_selected() const
  {
    return selected;
  }
  
  template<typename DataType>
  void ChamberlinFilter<DataType>::setup()
  {
    numerical_frequency = 2 * std::sin(boost::math::constants::pi<DataType>() * cutoff_frequency / input_sampling_rate);
    numerical_attenuation = 2 * attenuation;
  }

  template<typename DataType>
  void ChamberlinFilter<DataType>::process_impl(gsl::index size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(gsl::index i = 0; i < size; ++i)
    {
      yh = input[i] - yl - numerical_attenuation * yb;
      yb = numerical_frequency * yh + yb;
      yl = numerical_frequency * yb + yl;
      if(selected == 0)
      {
        output[i] = yl;
      }
      else if(selected == 1)
      {
        output[i] = yb;
      }
      else
      {
        output[i] = yh;
      }
    }
  }
  
#if ATK_ENABLE_INSTANTIATION
  template class ChamberlinFilter<float>;
#endif
  template class ChamberlinFilter<double>;
}
