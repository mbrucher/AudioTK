/**
 * \file RemezBasedFilter.cpp
 */

#include "FIRFilter.h"
#include "RemezBasedFilter.h"

namespace ATK
{
  template<class DataType>
  RemezBasedCoefficients<DataType>::RemezBasedCoefficients()
  :Parent(1, 1), in_order(0)
  {
    
  }
  
  template<class DataType>
  void RemezBasedCoefficients<DataType>::set_target(const std::vector<std::pair<std::pair<DataType, DataType>, DataType> >& target)
  {
    this->target = target;
    setup();
  }
  
  template<class DataType>
  const std::vector<std::pair<std::pair<typename RemezBasedCoefficients<DataType>::DataType, typename RemezBasedCoefficients<DataType>::DataType>, typename RemezBasedCoefficients<DataType>::DataType> >& RemezBasedCoefficients<DataType>::get_target() const
  {
    return target;
  }
  
  template<class DataType>
  void RemezBasedCoefficients<DataType>::set_order(int order)
  {
    in_order = order;
    setup();
  }

  template<class DataType>
  void RemezBasedCoefficients<DataType>::setup()
  {
    Parent::setup();
  }
  
  template class RemezBasedCoefficients<float>;
  template class RemezBasedCoefficients<double>;
  
  template class FIRFilter<RemezBasedCoefficients<float> >;
  template class FIRFilter<RemezBasedCoefficients<double> >;

}
