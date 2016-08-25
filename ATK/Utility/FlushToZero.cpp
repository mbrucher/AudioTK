/**
 * \file FlushToZero.cpp
 */

#include <ATK/Utility/FlushToZero.h>

#ifdef __GNUC__
#include <xmmintrin.h>
#define _MM_DENORMALS_ZERO_MASK   0x0040
#define _MM_DENORMALS_ZERO_ON     0x0040
#define _MM_DENORMALS_ZERO_OFF    0x0000

#else
#include <fenv.h>
#endif

namespace ATK
{
  FlushToZero::FlushToZero()
  {
#ifdef _MSC_VER
    _controlfp_s(&previous_state, _MCW_DN, _DN_FLUSH);
#else
  #ifdef __GNUC__
    previous_state = _mm_getcsr() & _MM_DENORMALS_ZERO_MASK;
    _mm_setcsr(_mm_getcsr() | (_MM_DENORMALS_ZERO_ON));
  #else
    fegetenv(&previous_state);
    fesetenv(FE_DFL_DISABLE_SSE_DENORMS_ENV);
  #endif
#endif
  }
  
  FlushToZero::~FlushToZero()
  {
#ifdef _MSC_VER
    unsigned int new_state;
    _controlfp_s(&new_state, _MCW_DN, previous_state);
#else
  #ifdef __GNUC__
    _mm_setcsr((_mm_getcsr() & ~_MM_DENORMALS_ZERO_MASK));
  #else
    fesetenv(&previous_state);
  #endif
#endif
  }
}
