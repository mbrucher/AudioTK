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

#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>

#if ATK_USE_SIMD
#include <simdpp/simd.h>
#endif

namespace ATK
{
  /// Traits to handle conversion integer full scale from/to double
  template<typename DataType>
  struct IntegralTypeTraits
  {
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
  };

  /// Special case for 24bits
  template<>
  struct IntegralTypeTraits<char[3]>
  {
    typedef int64_t Scalar;

    /// Converts an integer 24bits to a double
    static Scalar to_double(const char el[3])
    {
      int64_t data = 0;
      char* temp = reinterpret_cast<char*>(&data);
      for(int i = 0; i < 3; ++i)
      {
        temp[i] = el[i];
      }
      return -static_cast<double>(data) / ((static_cast<double>(1 << 8) * std::numeric_limits<std::int32_t>::min()));
    }

    /// Converts a double to an integer 64bits
    static int64_t from_double(double el)
    {
      return static_cast<int64_t>(-el * (static_cast<double>(1 << 8) * std::numeric_limits<std::int32_t>::min()));
    }

    static int64_t Zero()
    {
      return 0;
    }
  };

  /// Traits to handle conversion floating point numbers from/to double
  template<typename DataType>
  struct RealTypeTraits
  {
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
  };

  /// Traits to handle conversion complex floating point numbers from/to double
  template<typename DataType>
  struct ComplexRealTypeTraits
  {
  };
  
  /// Traits to handle conversion complex floating point numbers from/to double
  template<typename DataType>
  struct ComplexRealTypeTraits<std::complex<DataType> >
  {
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
  };
  
#if ATK_USE_SIMD
  /// Traits to handle conversion complex floating point numbers from/to double
  template<>
  struct ComplexRealTypeTraits<simdpp::float32<4> >
  {
    static const std::size_t VECTOR_LANES = 4;
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
  };

  /// Traits to handle conversion complex floating point numbers from/to double
  template<>
  struct ComplexRealTypeTraits<simdpp::float32<8> >
  {
    static const std::size_t VECTOR_LANES = 8;
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
  };
  
  /// Traits to handle conversion complex floating point numbers from/to double
  template<>
  struct ComplexRealTypeTraits<simdpp::float64<4> >
  {
    static const std::size_t VECTOR_LANES = 4;
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
  };

  /// Traits to handle conversion complex floating point numbers from/to double
  template<>
  struct ComplexRealTypeTraits<simdpp::float64<8> >
  {
    static const std::size_t VECTOR_LANES = 8;
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
  };
  
  /// Traits to retrieve SIMD typename
  template<typename DataType>
  struct SIMDTypeTraits
  {
  };

  template<>
  struct SIMDTypeTraits<float>
  {
    template<int size>
    using SIMDType = simdpp::float32<size>;
  };

  template<>
  struct SIMDTypeTraits<double>
  {
    template<int size>
    using SIMDType = simdpp::float64<size>;
  };

#endif

  /// Common base class for conversion type traits
  template<typename DataType>
  struct TypeTraits : public std::conditional<std::is_class<DataType>::value, ComplexRealTypeTraits<DataType>,
    typename std::conditional<std::is_floating_point<DataType>::value, RealTypeTraits<DataType>, IntegralTypeTraits<DataType>>::type>::type
  {
  };

}

#endif
