/**
 * \file ButterworthFilter.cpp
 */

#include "ButterworthFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template <typename DataType>
  ButterworthLowPassCoefficients<DataType>::ButterworthLowPassCoefficients()
  :Parent(1, 1)
  {
  }
  
  template <typename DataType>
  void ButterworthLowPassCoefficients<DataType>::set_cut_frequency(DataType cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }

  template <typename DataType>
  typename ButterworthLowPassCoefficients<DataType>::DataType ButterworthLowPassCoefficients<DataType>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void ButterworthLowPassCoefficients<DataType>::setup()
  {
  }

  template class ButterworthLowPassCoefficients<float>;
  template class ButterworthLowPassCoefficients<double>;
  
  template class IIRFilter<ButterworthLowPassCoefficients<float> >;
  template class IIRFilter<ButterworthLowPassCoefficients<double> >;

}
