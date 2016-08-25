/**
 * \file FlushToZero.cpp
 */

#include <ATK/Utility/FlushToZero.h>

#include <fenv.h>

namespace ATK
{
  FlushToZero::FlushToZero()
  {
#ifdef _MSC_VER
    _controlfp_s(&previous_state, _MCW_DN, _DN_FLUSH);
#else
    fegetenv(&previous_state);
    fesetenv(FE_DFL_DISABLE_SSE_DENORMS_ENV);
#endif
  }
  
  FlushToZero::~FlushToZero()
  {
#ifdef _MSC_VER
    unsigned int new_state;
    _controlfp_s(&new_state, _MCW_DN, previous_state);    /// State to which the denormal flag must be set to
#else
    fesetenv(&previous_state);
#endif
  }
}
