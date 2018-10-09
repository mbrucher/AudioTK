/**
 * \file TypeTraits.h
 */

#ifndef ATK_CORE_TYPETRAITS_H
#define ATK_CORE_TYPETRAITS_H

#include <ATK/config.h>

#include <complex>
#include <cstdint>
#include <limits>
#include <type_traits>

#if ATK_USE_SIMD
#include <experimental/simd>
#endif

namespace ATK
{
  /// Traits to handle conversion integer full scale from/to double
  template<typename DataType>
  class IntegralTypeTraits
  {
  public:
    typedef DataType Scalar;

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
    typedef int64_t Scalar;

    /// Converts an integer 24bits to a double
    static Scalar to_double(const char el[3])
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
    typedef DataType Scalar;

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
    typedef typename std::complex<DataType>::value_type Scalar;

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
  
#if ATK_USE_SIMD
  /// Traits to handle conversion complex floating point numbers from/to double
  template<>
  class ComplexRealTypeTraits<simdpp::float64<2> >
  {
  public:
    static constexpr int VECTOR_LANES = 2;
    typedef double Scalar;
    
    /// Converts to a double
    static simdpp::float64<VECTOR_LANES> to_double(simdpp::float64<VECTOR_LANES> el)
    {
      return el;
    }

    /// Converts from a double
    static simdpp::float64<VECTOR_LANES> from_double(simdpp::float64<VECTOR_LANES> el)
    {
      return el;
    }

    static simdpp::float64<VECTOR_LANES> Zero()
    {
      return simdpp::make_float(0, 0);
    }

    static simdpp::float64<VECTOR_LANES> One()
    {
      return simdpp::make_float(1, 1);
    }

    static simdpp::float64<VECTOR_LANES> max(simdpp::float64<VECTOR_LANES> a, simdpp::float64<VECTOR_LANES> b)
    {
      return simdpp::max(a, b);
    }
  };

  /// Traits to handle conversion complex floating point numbers from/to double
  template<>
  class ComplexRealTypeTraits<simdpp::float32<4> >
  {
  public:
    static const int VECTOR_LANES = 4;
    typedef float Scalar;

    /// Converts to a double
    static simdpp::float32<VECTOR_LANES> to_double(simdpp::float32<VECTOR_LANES> el)
    {
      return el;
    }

    /// Converts from a double
    static simdpp::float32<VECTOR_LANES> from_double(simdpp::float32<VECTOR_LANES> el)
    {
      return el;
    }

    static simdpp::float32<VECTOR_LANES> Zero()
    {
      return simdpp::make_float(0, 0, 0, 0);
    }

    static simdpp::float32<VECTOR_LANES> One()
    {
      return simdpp::make_float(1, 1, 1, 1);
    }

    static simdpp::float32<VECTOR_LANES> max(simdpp::float32<VECTOR_LANES> a, simdpp::float32<VECTOR_LANES> b)
    {
      return simdpp::max(a, b);
    }
  };

  /// Traits to handle conversion complex floating point numbers from/to double
  template<>
  class ComplexRealTypeTraits<simdpp::float32<8> >
  {
  public:
    static const int VECTOR_LANES = 8;
    typedef float Scalar;

    /// Converts to a double
    static simdpp::float32<VECTOR_LANES> to_double(simdpp::float32<VECTOR_LANES> el)
    {
      return el;
    }

    /// Converts from a double
    static simdpp::float32<VECTOR_LANES> from_double(simdpp::float32<VECTOR_LANES> el)
    {
      return el;
    }

    static simdpp::float32<VECTOR_LANES> Zero()
    {
      return simdpp::make_float(0, 0, 0, 0, 0, 0, 0, 0);
    }

    static simdpp::float32<VECTOR_LANES> One()
    {
      return simdpp::make_float(1, 1, 1, 1, 1, 1, 1, 1);
    }

    static simdpp::float32<VECTOR_LANES> max(simdpp::float32<VECTOR_LANES> a, simdpp::float32<VECTOR_LANES> b)
    {
      return simdpp::max(a, b);
    }
  };
  
  /// Traits to handle conversion complex floating point numbers from/to double
  template<>
  class ComplexRealTypeTraits<simdpp::float64<4> >
  {
  public:
    static const int VECTOR_LANES = 4;
    typedef double Scalar;

    /// Converts to a double
    static simdpp::float64<VECTOR_LANES> to_double(simdpp::float64<VECTOR_LANES> el)
    {
      return el;
    }

    /// Converts from a double
    static simdpp::float64<VECTOR_LANES> from_double(simdpp::float64<VECTOR_LANES> el)
    {
      return el;
    }

    static simdpp::float64<VECTOR_LANES> Zero()
    {
      return simdpp::make_float(0, 0, 0, 0);
    }

    static simdpp::float64<VECTOR_LANES> One()
    {
      return simdpp::make_float(1, 1, 1, 1);
    }

    static simdpp::float64<VECTOR_LANES> max(simdpp::float64<VECTOR_LANES> a, simdpp::float64<VECTOR_LANES> b)
    {
      return simdpp::max(a, b);
    }
  };

  /// Traits to handle conversion complex floating point numbers from/to double
  template<>
  class ComplexRealTypeTraits<simdpp::float64<8> >
  {
  public:
    static const int VECTOR_LANES = 8;
    typedef double Scalar;

    /// Converts to a double
    static simdpp::float64<VECTOR_LANES> to_double(simdpp::float64<VECTOR_LANES> el)
    {
      return el;
    }

    /// Converts from a double
    static simdpp::float64<VECTOR_LANES> from_double(simdpp::float64<VECTOR_LANES> el)
    {
      return el;
    }

    static simdpp::float64<VECTOR_LANES> Zero()
    {
      return simdpp::make_float(0, 0, 0, 0, 0, 0, 0, 0);
    }

    static simdpp::float64<VECTOR_LANES> One()
    {
      return simdpp::make_float(1, 1, 1, 1, 1, 1, 1, 1);
    }

    static simdpp::float64<VECTOR_LANES> max(simdpp::float64<VECTOR_LANES> a, simdpp::float64<VECTOR_LANES> b)
    {
      return simdpp::max(a, b);
    }
  };

  /// Traits to retrieve SIMD typename
  template<typename DataType>
  class SIMDTypeTraits
  {
  };

  template<>
  class SIMDTypeTraits<float>
  {
  public:
    template<int size>
    using SIMDType = simdpp::float32<size>;
  };

  template<>
  class SIMDTypeTraits<double>
  {
  public:
    template<int size>
    using SIMDType = simdpp::float64<size>;
  };

#endif

  /// Common base class for conversion type traits
  template<typename DataType>
  class TypeTraits : public std::conditional<std::is_class<DataType>::value, ComplexRealTypeTraits<DataType>,
    typename std::conditional<std::is_floating_point<DataType>::value, RealTypeTraits<DataType>, IntegralTypeTraits<DataType>>::type>::type
  {
  };
}

#endif
