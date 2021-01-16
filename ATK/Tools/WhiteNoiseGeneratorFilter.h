/**
 * \file WhiteNoiseGeneratorFilter.h
 */

#ifndef ATK_TOOLS_WHITENOISEGENERATORFILTER_H
#define ATK_TOOLS_WHITENOISEGENERATORFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

namespace ATK
{
  /// A uniform noise generator
  template<typename DataType_>
  class ATK_TOOLS_EXPORT WhiteNoiseGeneratorFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::outputs;
    using Parent::output_sampling_rate;

  public:
    /// Constructor
    WhiteNoiseGeneratorFilter();
    /// Destructor
    ~WhiteNoiseGeneratorFilter() override = default;

    /// Sets the output volume, doesn't update the cache
    void set_volume(DataType_ volume);
    /// Gets the output volume
    DataType_ get_volume() const;

    /// Sets the offset of the generated signal, doesn't update the cache
    void set_offset(DataType_ offset);
    /// Gets the offset
    DataType_ get_offset() const;

  protected:
    void process_impl(gsl::index size) const final;
    
  private:
    DataType_ volume{1};
    DataType_ offset{0};
    
    mutable boost::random::mt19937 gen; // Should use a random123 when they will be in Boost
    mutable boost::random::uniform_real_distribution<DataType_> dist{-1, 1};
  };
}

#endif
