/**
 * \file ScalarNewtonRaphson.h
 */

#ifndef ATK_TOOLS_SCALAR_NEWTONRAPHSON_H
#define ATK_TOOLS_SCALAR_NEWTONRAPHSON_H

#include <boost/scoped_ptr.hpp>

namespace ATK
{
  template<typename Function>
  class ScalarNewtonRaphson
  {
    static const int max_iterations = 100;
    
    typedef typename Function::DataType DataType;
    
    const boost::scoped_ptr<Function>& function;
    
    DataType x0, y0;
    DataType precision;
    
  public:
    ScalarNewtonRaphson(const boost::scoped_ptr<Function>& function)
    :function(function), x0(0), y0(0), precision(0.00001)
    {
      
    }
    
    DataType optimize(DataType x1)
    {
      if(x0 == x1)
      {
        return y0;
      }
      y0 = optimize_impl(x1);
      x0 = x1;
      return y0;
    }
    
  protected:
    DataType optimize_impl(DataType x1)
    {
      DataType y1 = y0;
      int i;
      
      for(i = 0; i < max_iterations; ++i)
      {
        std::pair<DataType, DataType> all = (*function)(x0, x1, y0, y1);
        if(std::abs(all.second) < std::numeric_limits<DataType>::epsilon() )
        {
          return y1;
        }
        DataType yk = y1 - all.first / all.second;
        if( std::abs(yk - y1) < precision )
        {
          return yk;
        }
        y1 = yk;
      }
      if(i == max_iterations)
      {
        std::cout << "Failed to converge for " << x0 << "," << x1 << "," << y0 << "," << y1 << std::endl;
      }
      return y1;
    }
  };
}

#endif
