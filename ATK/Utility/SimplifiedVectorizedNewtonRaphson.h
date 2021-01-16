/**
 * \file SimplifiedVectorizedNewtonRaphson.h
 */

#ifndef ATK_UTILITY_SIMPLIFIEDVECTORIZEDNEWTONRAPHSON_H
#define ATK_UTILITY_SIMPLIFIEDVECTORIZEDNEWTONRAPHSON_H

#include <ATK/config.h>

#include <Eigen/Dense>

#include <cmath>
#include <limits>

namespace ATK
{
  /// Simplified Vectorized Newton Raphson optimizer
  /*!
   * A NR optimizer, 10 iterations max, for stabilized computation
   */
  template<typename Function, int size, int max_iterations=10>
  class SimplifiedVectorizedNewtonRaphson
  {
    using DataType = typename Function::DataType;
    using Vector = Eigen::Matrix<DataType, size, 1>;

    Function function;
    
    DataType precision;
    DataType maxstep{10};
    Vector y0{Vector::Zero()};
    
  public:
    /*!
     * @brief Constructs the optimizer
     * @param function is the function that we will try to optimize.
     *   It is a functor taking x[n-1], x[n], y[n-1] and an estimate y[n], returning the value of the cost function and its derivative according to y[n]
     * @param precision is the precision that the optimizer will try to achieve. By default uses $$\\sqrt{\\epsilon_{Datatype}}$$
     */
    SimplifiedVectorizedNewtonRaphson(Function&& function, DataType precision = 0)
    :function(std::move(function)), precision(precision)
    {
      if(precision == 0)
      {
        this->precision = std::sqrt(std::numeric_limits<DataType>::epsilon());
      }
    }

    SimplifiedVectorizedNewtonRaphson(Function&& function, Vector&& y0, DataType precision = 0)
      :function(std::move(function)), precision(precision), y0(y0)
    {
      if (precision == 0)
      {
        this->precision = std::sqrt(std::numeric_limits<DataType>::epsilon());
      }
    }


    SimplifiedVectorizedNewtonRaphson(const SimplifiedVectorizedNewtonRaphson&) = delete;
    SimplifiedVectorizedNewtonRaphson& operator=(const SimplifiedVectorizedNewtonRaphson&) = delete;

    /// Optimize the function and sets its internal state
    Vector optimize()
    {
      Vector y1 = y0;
      gsl::index j;
      for(j = 0; j < max_iterations; ++j)
      {
        Vector cx = function(y1);
        auto maximum = cx.maxCoeff();
        auto minimum = cx.minCoeff();
        auto r = std::max(maximum, -minimum);
        if(r > maxstep)
        {
          cx *= maxstep/r;
        }

        auto yk = y1 - cx;
        if((cx.array().abs() < precision).all())
        {
          return yk;
        }
        y1 = yk;
      }
      return y1;
    }
  };
}

#endif
