/**
 * \file ScalarNewtonRaphson.h
 */

#ifndef ATK_UTILITY_SCALAR_NEWTONRAPHSON_H
#define ATK_UTILITY_SCALAR_NEWTONRAPHSON_H

#include <ATK/config.h>

#include <cmath>
#if ATK_PROFILING == 1
#include <iostream>
#endif
#include <limits>

namespace ATK
{
  /// Scalar Newton Raphson optimizer
  /*!
   * A NR optimizer, 10 iterations max
   */
  template<typename Function, int max_iterations=10, bool check_convergence=true>
  class ScalarNewtonRaphson
  {
    using DataType = typename Function::DataType;
    
    Function function;
    
    DataType precision;
    DataType maxstep{1};
    
#if ATK_PROFILING == 1
    int64_t nb_iterations{0};
    int64_t nb_optimizations{0};
#endif
    
  public:
    /*!
     * @brief Constructs the optimizer
     * @param function is the function that we will try to optimize.
     *   It is a functor taking x[n-1], x[n], y[n-1] and an estimate y[n], returning the value of the cost function and its derivative according to y[n]
     * @param precision is the precision that the optimizer will try to achieve. By default uses $$\\sqrt{\\epsilon_{Datatype}}$$
     */
    ScalarNewtonRaphson(Function&& function, DataType precision = 0)
    :function(std::move(function)), precision(precision)
    {
      if(precision == 0)
      {
        this->precision = std::sqrt(std::numeric_limits<DataType>::epsilon());
      }
    }

#if ATK_PROFILING == 1
    ~ScalarNewtonRaphson()
    {
      std::cout << "nb optimizations: " << nb_optimizations << std::endl;
      std::cout << "nb iterations: " << nb_iterations << std::endl;
      std::cout << "average: " << nb_iterations / double(nb_optimizations) << std::endl;
    }
#endif
    
    ScalarNewtonRaphson(const ScalarNewtonRaphson&) = delete;
    ScalarNewtonRaphson& operator=(const ScalarNewtonRaphson&) = delete;

    /// Optimize the function and sets its internal state
    void optimize(const DataType* ATK_RESTRICT input, DataType* ATK_RESTRICT output)
    {
#if ATK_PROFILING == 1
      ++nb_optimizations;
#endif
      output[0] = optimize_impl(input, output);
    }

    /// Returns the function
    Function& get_function()
    {
      return function;
    }

    /// Returns the function
    const Function& get_function() const
    {
      return function;
    }

  protected:
    /// Just optimize the function
    DataType optimize_impl(const DataType* ATK_RESTRICT input, DataType* ATK_RESTRICT output)
    {
      DataType y1 = function.estimate(input, output);
      gsl::index i;
      
      for(i = 0; i < max_iterations; ++i)
      {
#if ATK_PROFILING == 1
        ++nb_iterations;
#endif
        std::pair<DataType, DataType> all = function(input, output, y1);
        if(std::abs(all.second) < std::numeric_limits<DataType>::epsilon() )
        {
          return y1;
        }
        DataType cx = all.first / all.second;
        if(cx < -maxstep)
        {
          cx = -maxstep;
        }
        if(cx > maxstep)
        {
          cx = maxstep;
        }
        DataType yk = y1 - cx;
        if( std::abs(yk - y1) < precision )
        {
          return yk;
        }
        y1 = yk;
      }
      if(check_convergence && i == max_iterations)
      {
        return output[-1]; // Stay the same
      }
      return y1;
    }
  };
}

#endif
