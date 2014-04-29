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
    const static int grid_size = 1024; // grid size, power of two better for FFT
    
    int M;
    std::vector<DataType> grid;
    std::vector<std::pair<std::pair<DataType, DataType>, DataType> > target;
  public:
    RemezBuilder(int order, const std::vector<std::pair<std::pair<DataType, DataType>, DataType> >& target)
    :M((order - 1) / 2), target(target)
    {
      grid.resize(grid_size);
      for(int i = 0; i < grid_size; ++i)
      {
        grid[i] = i * boost::math::constants::pi<DataType>() / grid_size;
      }
    }
    
    std::vector<DataType> build()
    {
      std::vector<DataType> coeffs;
      
      return coeffs;
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
  void RemezBasedCoefficients<DataType>::set_template(const std::vector<std::pair<std::pair<DataType, DataType>, DataType> >& target)
  {
    this->target = target;
    setup();
  }
  
  template<class DataType>
  const std::vector<std::pair<std::pair<typename RemezBasedCoefficients<DataType>::DataType, typename RemezBasedCoefficients<DataType>::DataType>, typename RemezBasedCoefficients<DataType>::DataType> >& RemezBasedCoefficients<DataType>::get_template() const
  {
    return target;
  }
  
  template<class DataType>
  void RemezBasedCoefficients<DataType>::set_order(int order)
  {
    if(order % 2 == 0)
    {
      throw std::range_error("Need an even filter order");
    }
    in_order = order;
    setup();
  }

  template<class DataType>
  void RemezBasedCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    std::sort(target.begin(), target.end());
    for(std::size_t i = 0; i < target.size() - 1; ++i)
    {
      if(target[i].first.second > target[i + 1].first.first)
      {
        target.clear();
        throw std::runtime_error("Bad template");
      }
    }
    
    RemezBuilder<DataType> builder(in_order, target);
    coefficients_in = builder.build();
  }
  
  template class RemezBasedCoefficients<float>;
  template class RemezBasedCoefficients<double>;
  
  template class FIRFilter<RemezBasedCoefficients<float> >;
  template class FIRFilter<RemezBasedCoefficients<double> >;

}
