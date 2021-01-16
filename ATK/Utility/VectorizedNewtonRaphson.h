/**
 * \file VectorizedNewtonRaphson.h
 */

#ifndef ATK_UTILITY_VECTORIZEDNEWTONRAPHSON_H
#define ATK_UTILITY_VECTORIZEDNEWTONRAPHSON_H

#include <cmath>
#if ATK_PROFILING == 1
#include <iostream>
#endif
#include <limits>

#include <ATK/config.h>

#include <Eigen/Dense>

namespace ATK
{
  /// Vectorized Newton Raphson optimizer
  /*!
   * A NR optimizer, 10 iterations max
   */
  template<typename Function, gsl::index size, gsl::index max_iterations=10, bool check_convergence=true>
  class VectorizedNewtonRaphson
  {
    using DataType = typename Function::DataType;
    
    Function function;
    
    DataType precision;
    
#if ATK_PROFILING == 1
    int64_t nb_iterations{0};
    int64_t nb_optimizations{0};
#endif
    using Vector = Eigen::Matrix<DataType, size, 1>;
    
  public:
    /*!
     * @brief Constructs the optimizer
     * @param function is the function that we will try to optimize.
     *   It is a functor taking x[n-1], x[n], y[n-1] and an estimate y[n], returning the value of the cost function and its derivative according to y[n]
     * @param precision is the precision that the optimizer will try to achieve. By default uses $$\\sqrt{\\epsilon_{Datatype}}$$
     */
    VectorizedNewtonRaphson(Function&& function, DataType precision = 0)
    :function(std::move(function)), precision(precision)
    {
      if(precision == 0)
      {
        this->precision = std::sqrt(std::numeric_limits<DataType>::epsilon());
      }
    }
    
#if ATK_PROFILING == 1
    ~VectorizedNewtonRaphson()
    {
      std::cout << "nb optimizations: " << nb_optimizations << std::endl;
      std::cout << "nb iterations: " << nb_iterations << std::endl;
      std::cout << "average: " << nb_iterations / double(nb_optimizations) << std::endl;
    }
#endif
    
    VectorizedNewtonRaphson(const VectorizedNewtonRaphson&) = delete;
    VectorizedNewtonRaphson& operator=(const VectorizedNewtonRaphson&) = delete;

    /// Optimize the function and sets its internal state
    void optimize(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
#if ATK_PROFILING == 1
      ++nb_optimizations;
#endif
      auto res = optimize_impl(i, input, output);
      for(gsl::index j = 0; j < size; ++j)
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
    Vector optimize_impl(gsl::index i, const DataType* const * ATK_RESTRICT input, DataType* const * ATK_RESTRICT output)
    {
      Vector y1 = function.estimate(i, input, output);
      
      gsl::index j;
      for(j = 0; j < max_iterations; ++j)
      {
#if ATK_PROFILING == 1
        ++nb_iterations;
#endif
        auto cx = function(i, input, output, y1);
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
        for(gsl::index j = 0; j < size; ++j)
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
