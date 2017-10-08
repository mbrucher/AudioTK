/**
 * \file QInterface.cpp
 */

#include <ATK/EQ/EQInterface.h>

#include <complex>

namespace ATK
{
  OrderInterface::~OrderInterface()
  {
  }
  
  template<typename DataType>
  SingleCutFrequencyInterface<DataType>::~SingleCutFrequencyInterface()
  {
  }
  
  template<typename DataType>
  DualCutFrequencyInterface<DataType>::~DualCutFrequencyInterface()
  {
  }
  
  template<typename DataType>
  QInterface<DataType>::~QInterface()
  {
  }
  
  template<typename DataType>
  GainInterface<DataType>::~GainInterface()
  {
  }
  
  template<typename DataType>
  RippleInterface<DataType>::~RippleInterface()
  {
  }
  
  template class SingleCutFrequencyInterface<float>;
  template class DualCutFrequencyInterface<float>;
  template class QInterface<float>;
  template class GainInterface<float>;
  template class RippleInterface<float>;
  template class SingleCutFrequencyInterface<double>;
  template class DualCutFrequencyInterface<double>;
  template class QInterface<double>;
  template class GainInterface<double>;
  template class RippleInterface<double>;
  template class SingleCutFrequencyInterface<std::complex<float> >;
  template class DualCutFrequencyInterface<std::complex<float> >;
  template class QInterface<std::complex<float> >;
  template class GainInterface<std::complex<float> >;
  template class RippleInterface<std::complex<float> >;
  template class SingleCutFrequencyInterface<std::complex<double> >;
  template class DualCutFrequencyInterface<std::complex<double> >;
  template class QInterface<std::complex<double> >;
  template class GainInterface<std::complex<double> >;
  template class RippleInterface<std::complex<double> >;
}
