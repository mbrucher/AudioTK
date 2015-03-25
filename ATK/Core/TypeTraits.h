/**
 * \file TypeTraits.h
 */

#ifndef ATK_CORE_TYPETRAITS_H
#define ATK_CORE_TYPETRAITS_H

#include <cstdint>
#include <limits>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
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

  template<>
  struct IntegralTypeTraits<char[3]>
  {
    static double to_double(const char el[3])
    {
      std::int64_t data = 0;
      char* temp = reinterpret_cast<char*>(&data);
      for(int i = 0; i < 3; ++i)
      {
        temp[3-i] = el[i];
      }
      return -static_cast<double>(data) / ((static_cast<double>(1 << 8) * std::numeric_limits<std::int32_t>::min()));
    }

    static std::int64_t from_double(double el)
    {
      return static_cast<std::int64_t>(-el * (static_cast<double>(1 << 8) * std::numeric_limits<std::int32_t>::min()));
    }
  };

  template<>
  struct IntegralTypeTraits<const char[3]>
  {
    static double to_double(const char el[3])
    {
      std::int64_t data = 0;
      char* temp = reinterpret_cast<char*>(&data);
      for(int i = 0; i < 3; ++i)
      {
        temp[3-i] = el[i];
      }
      return -static_cast<double>(data) / ((static_cast<double>(1 << 8) * std::numeric_limits<std::int32_t>::min()));
    }

    static std::int64_t from_double(double el)
    {
      return static_cast<std::int64_t>(-el * (static_cast<double>(1 << 8) * std::numeric_limits<std::int32_t>::min()));
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
  struct TypeTraits : public boost::mpl::if_<typename boost::is_floating_point<DataType>::type, RealTypeTraits<DataType>, IntegralTypeTraits<DataType> >::type
  {
  };

}

#endif
