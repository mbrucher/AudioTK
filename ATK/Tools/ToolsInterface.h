/**
 * \file ToolsInterface.h
 */

#ifndef ATK_TOOLS_TOOLSINTERFACE_H
#define ATK_TOOLS_TOOLSINTERFACE_H

#include <ATK/Tools/config.h>

namespace ATK
{
  /// Interface for a variable order filter
  class ATK_TOOLS_EXPORT DryWetInterface
  {
  public:
    virtual ~DryWetInterface() = default;
    /// Sets the amount of input signal in the output signal
    virtual void set_dry(double dry) = 0;
    /// Returns the amount of dry signal in the output
    virtual double get_dry() const = 0;
  };
}

#endif
