/**
 * \file FlushToZero.cpp
 */

#include <ATK/Utility/FlushToZero.h>


namespace ATK
{
  FlushToZero::FlushToZero()
  {
    fegetenv(&previous_state);
    fesetenv(FE_DFL_DISABLE_SSE_DENORMS_ENV);
  }
  
  FlushToZero::~FlushToZero()
  {
    fesetenv(&previous_state);
  }
}
