/**
 * \file VectorizedNewtonRaphson.h
 */

#ifndef ATK_UTILITY_VECTORIZEDNEWTONRAPHSON_H
#define ATK_UTILITY_VECTORIZEDNEWTONRAPHSON_H

#include <cmath>
#include <limits>

#include <ATK/config.h>

namespace ATK
{
  /// Vectorized Newton Raphson optimizer
  /*!
   * A NR optimizer, 10 iterations max
   */
  template<typename Function, int size, int max_iterations=10, bool check_convergence=true>
  class VectorizedNewtonRaphson
  {
    
    typedef typename Function::DataType DataType;
    
    Function function;
    
    DataType precision;
    DataType maxstep;
    
  public:
    /*!
     * @brief Constructs the optimizer
     * @param function is the function that we will try to optimize.
     *   It is a functor taking x[n-1], x[n], y[n-1] and an estimate y[n], returning the value of the cost function and its derivative according to y[n]
     * @param precision is the precision that the optimizer will try to achieve. By default uses $$\\sqrt{\\epsilon_{Datatype}}$$
     */
    VectorizedNewtonRaphson(Function&& function, DataType precision = 0)
    :function(std::move(function)), precision(precision), maxstep(static_cast<DataType>(.1))
    {
      if(precision == 0)
      {
        this->precision = std::sqrt(std::numeric_limits<DataType>::epsilon());
      }
    }
    
    /// Optimize the function and sets its internal state
    void optimize(const DataType* ATK_RESTRICT input, DataType* ATK_RESTRICT output)
    {
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
      int i;
      
      for(i = 0; i < max_iterations; ++i)
      {
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
