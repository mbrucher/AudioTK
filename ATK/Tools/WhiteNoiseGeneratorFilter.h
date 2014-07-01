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
  /**
   *
   */
  template<typename DataType_>
  class ATK_TOOLS_EXPORT WhiteNoiseGeneratorFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs_size;
    using Parent::outputs;
    using Parent::output_sampling_rate;

  public:
    WhiteNoiseGeneratorFilter();
    ~WhiteNoiseGeneratorFilter();

    void set_volume(double volume);
    double get_volume() const;

    void set_offset(double offset);
    double get_offset() const;

  protected:
    virtual void process_impl(std::int64_t size);
    
  private:
    double volume;
    double offset;
    
    boost::random::mt19937 gen; // Should use a random123 when they will be in Boost
    boost::random::uniform_real_distribution<DataType_> dist;
  };
}

#endif
