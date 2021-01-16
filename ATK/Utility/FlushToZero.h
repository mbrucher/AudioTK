/**
 * \file FlushToZero.h
 */

#ifndef ATK_UTILITY_FLUSHTOZERO_H
#define ATK_UTILITY_FLUSHTOZERO_H

#include <ATK/Utility/config.h>

#include <fenv.h>

namespace ATK
{
  /// Flushes denormal numbers to zero while the instance exists, sets the flag the way it was before
  class ATK_UTILITY_EXPORT FlushToZero
  {
  public:
    /*!
     * @brief Constructor, with the number of steps and scale
     */
    FlushToZero();
    
    ~FlushToZero();

    FlushToZero(const FlushToZero&) = delete;
    FlushToZero& operator=(const FlushToZero&) = delete;
  protected:
/// State to which the denormal flag must be set to
#if defined(_MSC_VER)
    unsigned int previous_state;
#elif defined(__APPLE__)
    fenv_t previous_state;
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
    int previous_state;
#endif
  };
}

#endif
