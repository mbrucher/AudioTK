/**
 * \file VectorizedNewtonRaphson.h
 */

#ifndef ATK_UTILITY_VECTORIZEDNEWTONRAPHSON_H
#define ATK_UTILITY_VECTORIZEDNEWTONRAPHSON_H

#include <cmath>
#include <limits>

#include <ATK/config.h>

#include <Eigen/Dense>

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
    
    typedef Eigen::Matrix<DataType, size, 1> Vector;
    
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
    void optimize(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      auto res = optimize_impl(i, input, output);
      for(int j = 0; j < size; ++j)
      {
        output[j][i] = res.data()[j];
      }
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
    Vector optimize_impl(int64_t i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      Vector y1 = function.estimate(i, input, output);
      
      int j;
      for(j = 0; j < max_iterations; ++j)
      {
        auto all = function(i, input, output, y1);
        Vector cx = all.second.colPivHouseholderQr().solve(all.first);
        auto yk = y1 - cx;
        if((cx.array().abs() < precision).all())
        {
          return yk;
        }
        y1 = yk;
      }
      if(check_convergence && j == max_iterations)
      {
        Vector y0;
        for(int j = 0; j < size; ++j)
        {
          y0.data()[j] = output[j][i-1];
        }

        return y0; // Stay the same
      }
      return y1;
    }
  };
}

#endif
