/**
 * \file TypeTraits.h
 */

#ifndef ATK_CORE_TYPETRAITS_H
#define ATK_CORE_TYPETRAITS_H

#include <complex>
#include <cstdint>
#include <limits>
#include <type_traits>

#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>

namespace ATK
{
  /// Traits to handle conversion integer full scale from/to double
  template<typename DataType>
  struct IntegralTypeTraits
  {
    typedef double Scalar;

    /// Converts an integer to a double
    static Scalar to_double(DataType el)
    {
      return -static_cast<Scalar>(el) / std::numeric_limits<DataType>::min();
    }

    /// Converts a double to an integer
    static DataType from_double(Scalar el)
    {
      return static_cast<DataType>(-el * std::numeric_limits<DataType>::min());
    }
  };

  /// Special case for 24bits
  template<>
  struct IntegralTypeTraits<char[3]>
  {
    typedef double Scalar;

    /// Converts an integer 24bits to a double
    static Scalar to_double(const char el[3])
    {
      int64_t data = 0;
      char* temp = reinterpret_cast<char*>(&data);
      for(int i = 0; i < 3; ++i)
      {
        temp[i] = el[i];
      }
      return -static_cast<Scalar>(data) / ((static_cast<double>(1 << 8) * std::numeric_limits<std::int32_t>::min()));
    }

    /// Converts a double to an integer 64bits
    static int64_t from_double(Scalar el)
    {
      return static_cast<int64_t>(-el * (static_cast<double>(1 << 8) * std::numeric_limits<std::int32_t>::min()));
    }
  };

  /// Special case for 24bits
  template<>
  struct IntegralTypeTraits<const char[3]>
  {
    typedef double Scalar;

    /// Converts an integer 24bits to a double
    static Scalar to_double(const char el[3])
    {
      int64_t data = 0;
      char* temp = reinterpret_cast<char*>(&data);
      for(int i = 0; i < 3; ++i)
      {
        temp[i] = el[i];
      }
      return -static_cast<Scalar>(data) / ((static_cast<double>(1 << 8) * std::numeric_limits<std::int32_t>::min()));
    }

    /// Converts a double to an integer 64bits
    static int64_t from_double(Scalar el)
    {
      return static_cast<int64_t>(-el * (static_cast<double>(1 << 8) * std::numeric_limits<std::int32_t>::min()));
    }
  };

  /// Traits to handle conversion floating point numbers from/to double
  template<typename DataType>
  struct RealTypeTraits
  {
    typedef double Scalar;

    /// Converts to a double
    static Scalar to_double(DataType el)
    {
      return static_cast<Scalar>(el);
    }

    /// Converts from a double
    static DataType from_double(Scalar el)
    {
      return static_cast<DataType>(el);
    }
  };

  /// Traits to handle conversion complex floating point numbers from/to double
  template<typename DataType>
  struct ComplexRealTypeTraits
  {
    typedef std::complex<double> Scalar;

    /// Converts to a double
    static Scalar to_double(DataType el)
    {
      return static_cast<Scalar>(el);
    }

    /// Converts from a double
    static DataType from_double(Scalar el)
    {
      return static_cast<DataType>(el);
    }
  };

  /// Common base class for conversion type traits
  template<typename DataType>
  struct TypeTraits : public std::conditional_t<std::is_class_v<DataType>, ComplexRealTypeTraits<DataType>,
      std::conditional_t<std::is_floating_point_v<DataType>, RealTypeTraits<DataType>, IntegralTypeTraits<DataType>>>
  {
  };

}

#endif
