/**
 * \file WhiteNoiseGeneratorFilter.h
 */

#ifndef ATK_TOOLS_WHITENOISEGENERATORFILTER_H
#define ATK_TOOLS_WHITENOISEGENERATORFILTER_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// A uniform noise generator
  template<typename DataType_>
  class ATK_TOOLS_EXPORT WhiteNoiseGeneratorFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs;
    using Parent::output_sampling_rate;

  public:
    /// Constructor
    WhiteNoiseGeneratorFilter();
    /// Destructor
    ~WhiteNoiseGeneratorFilter();

    /// Sets the output volume, doesn't update the cache
    void set_volume(DataType_ volume);
    /// Gets the output volume
    DataType_ get_volume() const;

    /// Sets the offset of the generated signal, doesn't update the cache
    void set_offset(DataType_ offset);
    /// Gets the offset
    DataType_ get_offset() const;

  protected:
    virtual void process_impl(std::size_t size) const override final;
    
  private:
    DataType_ volume;
    DataType_ offset;
    
    mutable boost::random::mt19937 gen; // Should use a random123 when they will be in Boost
    mutable boost::random::uniform_real_distribution<DataType_> dist;
  };
}

#endif
