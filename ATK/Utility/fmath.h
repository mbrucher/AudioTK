
/**
	@brief fast math library for float
	@author herumi
	@url http://homepage1.nifty.com/herumi/
	@note modified new BSD license
	http://opensource.org/licenses/BSD-3-Clause
 
	cl /Ox /Ob2 /arch:SSE2 /fp:fast bench.cpp -I../xbyak /EHsc /DNOMINMAX
	g++ -O3 -fomit-frame-pointer -fno-operator-names -march=core2 -mssse3 -mfpmath=sse -ffast-math -fexcess-precision=fast
 */
/*
	function prototype list
 
	float fmath::exp(float);
	double fmath::expd(double);
	float fmath::log(float);
 
	__m128 fmath::exp_ps(__m128);
	__m256 fmath::exp_ps256(__m256);
	__m128 fmath::log_ps(__m128);
 
	double fmath::expd_v(double *, size_t n);
 
	if FMATH_USE_XBYAK is defined then Xbyak version are used
 */

#ifndef ATK_UTILITY_FMATH_H
#define ATK_UTILITY_FMATH_H

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cassert>
#include <limits>
#include <cstdint>
#include <cfloat>
#include <cstring> // for memcpy

#if defined(_WIN32) && !defined(__GNUC__)
# include <intrin.h>
# ifndef MIE_ALIGN
#  define MIE_ALIGN(x) __declspec(align(x))
# endif
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
/* GCC >= 4.4 and non-GCC compilers */
# include <x86intrin.h>
#endif
#ifndef MIE_ALIGN
# define MIE_ALIGN(x) __attribute__((aligned(x)))
#endif

namespace fmath {
  
  namespace local {
    
    constexpr size_t EXP_TABLE_SIZE = 10;
    constexpr size_t EXPD_TABLE_SIZE = 11;
    constexpr size_t LOG_TABLE_SIZE = 12;
    
    union fi {
      float f;
      unsigned int i;
    };
    
    union di {
      double d;
      uint64_t i;
    };
    
    inline unsigned int mask(int x)
    {
      return (1U << x) - 1;
    }
    
    inline uint64_t mask64(int x)
    {
      return (1ULL << x) - 1;
    }
    
    template<class T>
    inline const T* cast_to(const void *p)
    {
      return reinterpret_cast<const T*>(p);
    }
    
    template<class T, size_t N>
    size_t NumOfArray(const T (&)[N]) { return N; }
    
    /*
     exp(88.722839f) = inf ; 0x42b17218
     exp(-87.33655f) = 1.175491e-038f(007fffe6) denormal ; 0xc2aeac50
     exp(-103.972081f) = 0 ; 0xc2cff1b5
     */
    template<size_t N = EXP_TABLE_SIZE>
    class ExpVar {
    public:
      enum {
        s = N,
        n = 1 << s,
        f88 = 0x42b00000 /* 88.0 */
      };
      float minX[8];
      float maxX[8];
      float a[8];
      float b[8];
      float f1[8];
      unsigned int i127s[8];
      unsigned int mask_s[8];
      unsigned int i7fffffff[8];
      unsigned int tbl[n];
      ExpVar()
      {
        float log_2 = ::logf(2.0f);
        for (int i = 0; i < 8; i++) {
          maxX[i] = 88;
          minX[i] = -88;
          a[i] = n / log_2;
          b[i] = log_2 / n;
          f1[i] = 1.0f;
          i127s[i] = 127 << s;
          i7fffffff[i] = 0x7fffffff;
          mask_s[i] = mask(s);
        }
        
        for (int i = 0; i < n; i++) {
          float y = pow(2.0f, (float)i / n);
          fi fi;
          fi.f = y;
          tbl[i] = fi.i & mask(23);
        }
      }
    };
    
    template<size_t sbit_ = EXPD_TABLE_SIZE>
    class ExpdVar {
    public:
      enum {
        sbit = sbit_,
        s = 1UL << sbit,
        adj = (1UL << (sbit + 10)) - (1UL << sbit)
      };
      // A = 1, B = 1, C = 1/2, D = 1/6
      double C1[2]; // A
      double C2[2]; // D
      double C3[2]; // C/D
      uint64_t tbl[s];
      double a;
      double ra;
      ExpdVar()
      : a(s / ::log(2.0))
      , ra(1 / a)
      {
        for (int i = 0; i < 2; i++) {
          C1[i] = 1.0;
          C2[i] = 0.16666666685227835064;
          C3[i] = 3.0000000027955394;
        }
        for (int i = 0; i < s; i++) {
          di di;
          di.d = ::pow(2.0, i * (1.0 / s));
          tbl[i] = di.i & mask64(52);
        }
      }
    };
    
    template<size_t N = LOG_TABLE_SIZE>
    class LogVar {
    public:
      enum {
        LEN = N - 1
      };
      unsigned int m1[4]; // 0
      unsigned int m2[4]; // 16
      unsigned int m3[4]; // 32
      float m4[4];		// 48
      unsigned int m5[4]; // 64
      struct {
        float app;
        float rev;
      } tbl[1 << LEN];
      float c_log2;
      LogVar()
      : c_log2(::logf(2.0f) / (1 << 23))
      {
        const double e = 1 / double(1 << 24);
        const double h = 1 / double(1 << LEN);
        constexpr size_t n = 1U << LEN;
        for (size_t i = 0; i < n; i++) {
          double x = 1 + double(i) / n;
          double a = ::log(x);
          tbl[i].app = (float)a;
          if (i < n - 1) {
            double b = ::log(x + h - e);
            tbl[i].rev = (float)((b - a) / ((h - e) * (1 << 23)));
          } else {
            tbl[i].rev = (float)(1 / (x * (1 << 23)));
          }
        }
        for (int i = 0; i < 4; i++) {
          m1[i] = mask(8) << 23;
          m2[i] = mask(LEN) << (23 - LEN);
          m3[i] = mask(23 - LEN);
          m4[i] = c_log2;
          m5[i] = 127U << 23;
        }
      }
    };
    /* to define static variables in fmath.hpp */
    template<size_t EXP_N = EXP_TABLE_SIZE, size_t LOG_N = LOG_TABLE_SIZE, size_t EXPD_N = EXPD_TABLE_SIZE>
    struct C {
      static const ExpVar<EXP_N> expVar;
      static const LogVar<LOG_N> logVar;
      static const ExpdVar<EXPD_N> expdVar;
    };
    
    template<size_t EXP_N, size_t LOG_N, size_t EXPD_N>
    MIE_ALIGN(32) const ExpVar<EXP_N> C<EXP_N, LOG_N, EXPD_N>::expVar;
    
    template<size_t EXP_N, size_t LOG_N, size_t EXPD_N>
    MIE_ALIGN(32) const LogVar<LOG_N> C<EXP_N, LOG_N, EXPD_N>::logVar;
    
    template<size_t EXP_N, size_t LOG_N, size_t EXPD_N>
    MIE_ALIGN(32) const ExpdVar<EXPD_N> C<EXP_N, LOG_N, EXPD_N>::expdVar;
    
  } // fmath::local
  
#if defined(__GNUC__) && !(defined(__x86_64__) || defined(__i386__))
  using std::exp;
  using std::log;
#else
  inline double exp(double x)
  {
    if (x <= -708.39641853226408) return 0;
    if (x >= 709.78271289338397) return std::numeric_limits<double>::infinity();

    const auto& c = local::C<>::expdVar;
    const double _b = double(uint64_t(3) << 51);
    __m128d b = _mm_load_sd(&_b);
    __m128d xx = _mm_load_sd(&x);
    __m128d d = _mm_add_sd(_mm_mul_sd(xx, _mm_load_sd(&c.a)), b);
    uint64_t di = _mm_cvtsi128_si32(_mm_castpd_si128(d));
    uint64_t iax = c.tbl[di & mask(c.sbit)];
    __m128d _t = _mm_sub_sd(_mm_mul_sd(_mm_sub_sd(d, b), _mm_load_sd(&c.ra)), xx);
    uint64_t u = ((di + c.adj) >> c.sbit) << 52;
    double t;
    _mm_store_sd(&t, _t);
    double y = (c.C3[0] - t) * (t * t) * c.C2[0] - t + c.C1[0];
    double did;
    u |= iax;
    memcpy(&did, &u, sizeof(did));
    return y * did;
  }

  inline float exp(float x)
  {
    return static_cast<float>(exp(static_cast<double>(x)));
  }

  inline float log(float x)
  {
    const auto& logVar = local::C<>::logVar;
    constexpr size_t logLen = logVar.LEN;
    
    local::fi fi;
    fi.f = x;
    int a = fi.i & (local::mask(8) << 23);
    unsigned int b1 = fi.i & (local::mask(logLen) << (23 - logLen));
    unsigned int b2 = fi.i & local::mask(23 - logLen);
    int idx = b1 >> (23 - logLen);
    float f = float(a - (127 << 23)) * logVar.c_log2 + logVar.tbl[idx].app + float(b2) * logVar.tbl[idx].rev;
    return f;
  }
  
  inline float log2(float x) { return fmath::log(x) * 1.442695f; }

  inline double log(double x)
  {
    return std::log(x);
  }
#endif

  inline double pow(double x, double y)
  {
    return exp(y * fmath::log(x));
  }

  inline float pow(float x, float y)
  {
    return exp(y * fmath::log(x));
  }

  template<typename T>
  T log10(T x)
  {
    return log(x) / log(static_cast<T>(10));
  }

  /*
   for given y > 0
   get f_y(x) := pow(x, y) for x >= 0
   */
  class PowGenerator {
    enum {
      N = 11
    };
    float tbl0_[256];
    struct {
      float app;
      float rev;
    } tbl1_[1 << N];
  public:
    explicit PowGenerator(float y)
    {
      for (int i = 0; i < 256; i++) {
        tbl0_[i] = ::powf(2, (i - 127) * y);
      }
      const double e = 1 / double(1 << 24);
      const double h = 1 / double(1 << N);
      constexpr size_t n = 1U << N;
      for (size_t i = 0; i < n; i++) {
        double x = 1 + double(i) / n;
        double a = ::pow(x, (double)y);
        tbl1_[i].app = (float)a;
        double b = ::pow(x + h - e, (double)y);
        tbl1_[i].rev = (float)((b - a) / (h - e) / (1 << 23));
      }
    }
    float get(float x) const
    {
      local::fi fi;
      fi.f = x;
      int a = (fi.i >> 23) & local::mask(8);
      unsigned int b = fi.i & local::mask(23);
      unsigned int b1 = b & (local::mask(N) << (23 - N));
      unsigned int b2 = b & local::mask(23 - N);
      float f;
      int idx = b1 >> (23 - N);
      f = tbl0_[a] * (tbl1_[idx].app + float(b2) * tbl1_[idx].rev);
      return f;
    }
  };
  
  // exp2(x) = pow(2, x)
  inline float exp2(float x) { return fmath::exp(x * 0.6931472f); }
  
} // fmath

#endif
