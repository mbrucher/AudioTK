/**
 * \file FlushToZero.h
 */

#ifndef ATK_UTILITY_FLUSHTOZERO_H
#define ATK_UTILITY_FLUSHTOZERO_H

#include <fenv.h>

#include "config.h"

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

  protected:
    /// State to which the denormal flag must be set to
    fenv_t previous_state;
  };
}

#endif