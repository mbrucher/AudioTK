/**
 * \file DelayInterface.h
 */

#ifndef ATK_DELAY_DELAYINTERFACE_H
#define ATK_DELAY_DELAYINTERFACE_H

#include <map>

#include <ATK/Delay/config.h>

namespace ATK
{
  /// Interface for a fixed filter
  class ATK_DELAY_EXPORT DelayInterface
  {
  public:
    virtual ~DelayInterface();
    /// Sets the delay of the filter
  virtual void set_delay(std::size_t delay) = 0;
    /// Returns the delay
    virtual std::size_t get_delay() const = 0;
  };
}

#endif
