/**
 * \file TypeTraits.h
 */

#ifndef ATK_CORE_TYPETRAITS_H
#define ATK_CORE_TYPETRAITS_H

#include <limits>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/enable_if.hpp>

namespace ATK
{
  template<typename DataType>
  struct IntegralTypeTraits
  {
    static double to_double(DataType el)
    {
      return -static_cast<double>(el) / std::numeric_limits<DataType>::min();
    }

    static DataType from_double(double el)
    {
      return static_cast<DataType>(-el * std::numeric_limits<DataType>::min());
    }
  };
  
  template<typename DataType>
  struct RealTypeTraits
  {
    static double to_double(DataType el)
    {
      return static_cast<double>(el);
    }

    static DataType from_double(double el)
    {
      return static_cast<DataType>(el);
    }
  };

  template<typename DataType>
  struct TypeTraits : public boost::mpl::if_<typename boost::is_integral<DataType>::type, IntegralTypeTraits<DataType>, RealTypeTraits<DataType> >::type
  {
    //using typename boost::mpl::if_<typename boost::is_integral<DataType>::type, IntegralTypeTraits<DataType>, RealTypeTraits<DataType> >::type;
  };

}

#endif
