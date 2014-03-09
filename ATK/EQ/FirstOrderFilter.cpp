/**
 * \file FirstOrderFilter.cpp
 */

#include "FirstOrderFilter.h"

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename DataType>
  FirstOrderFilter<DataType>::FirstOrderFilter()
  :TypedBaseFilter<DataType>(1, 1), numerical_frequency(0), numerical_attenuation(1), yh(0), yb(0), yl(0), selected(0), attenuation(1), cutoff_frequency(0)
  {
  }
  
  template<typename DataType>
  void FirstOrderFilter<DataType>::set_cut_frequency(DataType cutoff_frequency)
  {
    this->cutoff_frequency = cutoff_frequency;
    setup();
  }

  template<typename DataType>
  typename FirstOrderFilter<DataType>::DataType FirstOrderFilter<DataType>::get_cut_frequency() const
  {
    return cutoff_frequency;
  }
  
  template<typename DataType>
  void FirstOrderFilter<DataType>::set_attenuation(DataType attenuation)
  {
    this->attenuation = attenuation;
    setup();
  }

  template<typename DataType>
  typename FirstOrderFilter<DataType>::DataType FirstOrderFilter<DataType>::get_attenuation() const
  {
    return attenuation;
  }
  
  template<typename DataType>
  void FirstOrderFilter<DataType>::select(int selection)
  {
    this->selected = selection;
  }
  
  template<typename DataType>
  int FirstOrderFilter<DataType>::get_selected() const
  {
    return selected;
  }
  
  template<typename DataType>
  void FirstOrderFilter<DataType>::setup()
  {
    numerical_frequency = 2 * std::sin(boost::math::constants::pi<DataType>() * cutoff_frequency / input_sampling_rate);
    numerical_attenuation = 2 * attenuation;
  }

  template<typename DataType>
  void FirstOrderFilter<DataType>::process_impl(long size)
  {
    for(long i = 0; i < size; ++i)
    {
      yh = converted_inputs[0][i] - yl - numerical_attenuation * yb;
      yb = numerical_frequency * yh + yb;
      yl = numerical_frequency * yb + yl;
      if(selected == 0)
      {
        outputs[0][i] = yl;
      }
      else if(selected == 1)
      {
        outputs[0][i] = yb;
      }
      else
      {
        outputs[0][i] = yh;
      }
    }
  }
  
  template class FirstOrderFilter<float>;
  template class FirstOrderFilter<double>;
}
