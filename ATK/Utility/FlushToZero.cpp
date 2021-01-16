/**
 * \file FlushToZero.cpp
 */

#include "FlushToZero.h"

#if defined(__APPLE__)
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
/* GCC-compatible compiler, targeting x86/x86-64 */
# include <x86intrin.h>
# ifndef _MM_DENORMALS_ZERO_OFF
#  define _MM_DENORMALS_ZERO_MASK   0x0040
#  define _MM_DENORMALS_ZERO_ON     0x0040
#  define _MM_DENORMALS_ZERO_OFF    0x0000
# endif
#endif

namespace ATK
{
  FlushToZero::FlushToZero()
  {
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
    _controlfp_s(&previous_state, _MCW_DN, _DN_FLUSH);
#elif defined(__APPLE__)
    fegetenv(&previous_state);
    fesetenv(FE_DFL_DISABLE_SSE_DENORMS_ENV);
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
    previous_state = _mm_getcsr() & _MM_DENORMALS_ZERO_MASK;
    _mm_setcsr(_mm_getcsr() | (_MM_DENORMALS_ZERO_ON));
#endif
  }
  
  FlushToZero::~FlushToZero()
  {
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
    unsigned int new_state;
    _controlfp_s(&new_state, _MCW_DN, previous_state);
#elif defined(__APPLE__)
    fesetenv(&previous_state);
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
    _mm_setcsr(_mm_getcsr() & ~_MM_DENORMALS_ZERO_MASK);
#endif
  }
}
