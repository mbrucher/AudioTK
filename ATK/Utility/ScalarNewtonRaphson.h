/**
 * \file ScalarNewtonRaphson.h
 */

#ifndef ATK_UTILITY_SCALAR_NEWTONRAPHSON_H
#define ATK_UTILITY_SCALAR_NEWTONRAPHSON_H

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
    
    typedef typename Function::DataType DataType;
    
    Function function;
    
    DataType x0, y0;
    DataType precision;
    DataType maxstep;
    
  public:
    /*!
     * @brief Constructs the optimizer
     * @param function is the function that we will try to optimize.
     *   It is a functor taking x[n-1], x[n], y[n-1] and an estimate y[n], returning the value of the cost function and its derivative according to y[n]
     * @param precision is the precision that the optimizer will try to achieve. By default uses $$\\sqrt{\\epsilon_{Datatype}}$$
     */
    ScalarNewtonRaphson(Function&& function, DataType precision = 0)
    :function(std::move(function)), x0(0), y0(0), precision(precision), maxstep(static_cast<DataType>(.1))
    {
      if(precision == 0)
      {
        this->precision = std::sqrt(std::numeric_limits<DataType>::epsilon());
      }
    }
    
    /// Optimize the function and sets its internal state
    DataType optimize(DataType x1)
    {
      y0 = optimize_impl(x1);

      x0 = x1;
      return y0;
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
    DataType optimize_impl(DataType x1)
    {
      DataType y1 = function.estimate(x0, x1, y0);
      int i;
      
      for(i = 0; i < max_iterations; ++i)
      {
        std::pair<DataType, DataType> all = function(x0, x1, y0, y1);
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
        return y0; // Stay the same
      }
      return y1;
    }
  };
}

#endif
