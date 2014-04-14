/**
 * \file RemezBasedFilter.cpp
 */

#include <vector>

#include <boost/math/constants/constants.hpp>

#include "FIRFilter.h"
#include "RemezBasedFilter.h"

namespace
{
  template<class DataType>
  class RemezBuilder
  {
    const static int grid_size = 1000;
    
    std::vector<DataType> grid;
  public:
    RemezBuilder()
    {
      grid.resize(grid_size);
      for(int i = 0; i < grid_size; ++i)
      {
        grid[i] = i * boost::math::constants::pi<DataType>() / grid_size;
      }
    }
  };
}

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
    
    RemezBuilder<DataType> builder;
    
  }
  
  template class RemezBasedCoefficients<float>;
  template class RemezBasedCoefficients<double>;
  
  template class FIRFilter<RemezBasedCoefficients<float> >;
  template class FIRFilter<RemezBasedCoefficients<double> >;

}
