/**
 * \file RemezBasedFilter.cpp
 */

#include <iostream>
#include <vector>

#include <boost/math/constants/constants.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "FIRFilter.h"
#include "RemezBasedFilter.h"

#if ATK_EIGEN == 1
#include <Eigen/Dense>

namespace
{
  template<class DataType>
  class RemezBuilder
  {
    const static int grid_size = 1024; // grid size, power of two better for FFT

    boost::random::mt19937 gen;
    boost::random::uniform_int_distribution<> dist;

    int M;
    std::vector<DataType> grid;
    std::vector<std::pair<std::pair<DataType, DataType>, DataType> > target;
    
    /// Computed coefficients
    std::vector<DataType> coeffs;
    /// Selected indices
    std::vector<int> indices;
    /// Weight function on the grid
    std::vector<DataType> weights;
    /// Objective function on the grid
    std::vector<DataType> objective;

  public:
    RemezBuilder(unsigned int order, const std::vector<std::pair<std::pair<DataType, DataType>, DataType> >& target)
    :dist(0, grid_size - 1), M((order - 1) / 2), target(target)
    {
      grid.resize(grid_size);
      for(int i = 0; i < grid_size; ++i)
      {
        grid[i] = i * boost::math::constants::pi<DataType>() / grid_size;
      }
    }
    
    void init()
    {
      coeffs.assign(M + 2, 0);
      indices.assign(M + 2, -1);
      
      for(std::size_t i = 0; i < indices.size(); ++i)
      {
        indices[i] = pickup_new_indice(indices);
      }
      
      weights.assign(grid_size, 0);
      objective.assign(grid_size, 0);

      int current_template = 0;
      for(int i = 0; i < grid_size; ++i)
      {
        if(grid[i] / boost::math::constants::pi<DataType>() > target[current_template].first.second && current_template + 1 < target.size())
        {
          ++current_template;
        }
        weights[i] = 1; //to update once we have weights for template
        objective[i] = target[current_template].second;
      }
    }
    
    std::vector<DataType> build()
    {
      if(target.empty())
      {
        coeffs.clear();
        return coeffs;
      }
      init();
      
      Eigen::Matrix<DataType, Eigen::Dynamic, Eigen::Dynamic> A(M+2, M+2);
      for(int i = 0; i < M+2; ++i)
      {
        for(int j = 0; j < M+1; ++j)
        {
          A(i, j) = std::cos(grid[indices[i]] * j);
        }
      }
      int flag = -1;
      for(int i = 0; i < M+2; ++i)
      {
        A(i, M+1) = flag / weights[indices[i]];
        flag = -flag;
      }
      
      Eigen::Matrix<DataType, Eigen::Dynamic, 1> b(M+2, 1);
      for(int i = 0; i < M+2; ++i)
      {
        b(i) = objective[indices[i]];
      }
      std::cout << "Here is the matrix A:\n" << A << std::endl;
      std::cout << "Here is the vector b:\n" << b << std::endl;
      Eigen::Matrix<DataType, Eigen::Dynamic, 1> x = A.colPivHouseholderQr().solve(b);
      std::cout << "Here is the result vector x:\n" << x << std::endl;
      return coeffs;
    }
    
  protected:
    int pickup_new_indice(const std::vector<int>& indices)
    {
      while(true)
      {
        int trial = dist(gen);
        if(std::find(indices.begin(), indices.end(), trial) == indices.end()) // not already used
        {
          DataType relative_freq = grid[trial] / boost::math::constants::pi<DataType>();
          for(std::size_t j = 0; j + 1 < target.size(); ++j)
          {
            if(relative_freq > target[j].first.second && relative_freq < target[j + 1].first.first)
            {
              continue;
            }
          }
          return trial;
        }
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
  void RemezBasedCoefficients<DataType>::set_order(unsigned int order)
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
    for(std::size_t i = 0; i + 1 < target.size(); ++i)
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

#endif