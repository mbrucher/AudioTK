/**
 * \file TypeTraits.h
 */

#ifndef ATK_CORE_TYPETRAITS_H
#define ATK_CORE_TYPETRAITS_H

#include <ATK/config.h>

#include <algorithm>
#include <complex>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace ATK
{
  /// Traits to handle conversion integer full scale from/to double
  template<typename DataType>
  class IntegralTypeTraits
  {
  public:
    using Scalar = DataType;

    /// Converts an integer to a double
    static double to_double(DataType el)
    {
      return -static_cast<double>(el) / std::numeric_limits<DataType>::min();
    }

    /// Converts a double to an integer
    static DataType from_double(double el)
    {
      return static_cast<DataType>(-el * std::numeric_limits<DataType>::min());
    }

    static DataType conj(DataType el)
    {
      return el;
    }

    static DataType Zero()
    {
      return 0;
    }

    static DataType One()
    {
      return 1;
    }

    static DataType max(DataType a, DataType b)
    {
    return std::max(a, b);
    }
  };

  /// Special case for 24bits
  template<>
  class IntegralTypeTraits<char[3]>
  {
  public:
    using Scalar = int64_t;

    /// Converts an integer 24bits to a double
    static double to_double(const char el[3])
    {
      int32_t data = 0;
      char* temp = reinterpret_cast<char*>(&data);
      for(int i = 0; i < 3; ++i)
      {
        temp[1+i] = el[i];
      }
      data = data >> 8;
      return -static_cast<double>(data) / (static_cast<double>(1 << 8) * std::numeric_limits<std::int16_t>::min());
    }

    /// Converts a double to an integer 64bits
    static int32_t from_double(double el)
    {
      return static_cast<int32_t>(-el * (static_cast<double>(1 << 8) * std::numeric_limits<std::int16_t>::min()));
    }

    static int32_t Zero()
    {
      return 0;
    }

    static int32_t One()
    {
      return 1;
    }
  };

  /// Traits to handle conversion floating point numbers from/to double
  template<typename DataType>
  class RealTypeTraits
  {
  public:
    using Scalar = DataType;

    /// Converts to a double
    static double to_double(DataType el)
    {
      return static_cast<double>(el);
    }

    /// Converts from a double
    static DataType from_double(double el)
    {
      return static_cast<DataType>(el);
    }

    static DataType conj(DataType el)
    {
      return el;
    }

    static DataType Zero()
    {
      return 0;
    }

    static DataType One()
    {
      return 1;
    }

    static DataType max(DataType a, DataType b)
    {
      return std::max(a, b);
    }
  };

  /// Traits to handle conversion complex floating point numbers from/to double
  template<typename DataType>
  class ComplexRealTypeTraits
  {
  };

  /// Traits to handle conversion complex floating point numbers from/to double
  template<typename DataType>
  class ComplexRealTypeTraits<std::complex<DataType> >
  {
  public:
    using Scalar = typename std::complex<DataType>::value_type;

    /// Converts to a double
    static std::complex<double> to_double(std::complex<DataType> el)
    {
      return static_cast<std::complex<double> >(el);
    }

    /// Converts from a double
    static std::complex<DataType> from_double(std::complex<double> el)
    {
      return static_cast<std::complex<DataType> >(el);
    }

    static std::complex<DataType> conj(std::complex<DataType> el)
    {
      return std::conj(el);
    }

    static DataType Zero()
    {
      return 0;
    }

    static DataType One()
    {
      return 1;
    }
  };
  
  /// Common base class for conversion type traits
  template<typename DataType>
  class TypeTraits : public std::conditional<std::is_class<DataType>::value, ComplexRealTypeTraits<DataType>,
    typename std::conditional<std::is_floating_point<DataType>::value, RealTypeTraits<DataType>, IntegralTypeTraits<DataType>>::type>::type
  {
  };
}

#endif
