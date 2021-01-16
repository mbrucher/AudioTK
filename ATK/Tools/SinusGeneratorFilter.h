/**
 * \file SinusGeneratorFilter.h
 */

#ifndef ATK_TOOLS_SINUSGENERATORFILTER_H
#define ATK_TOOLS_SINUSGENERATORFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

#include <vector>

namespace ATK
{
  /// A sin/cos generator
  template<typename DataType_>
  class ATK_TOOLS_EXPORT SinusGeneratorFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::outputs;
    using Parent::output_sampling_rate;

  public:
    /// Constructor
    SinusGeneratorFilter();
    /// Destructor
    ~SinusGeneratorFilter() override = default;

    /// Sets the frequency of the oscillator, without resetting it
    void set_frequency(DataType_ frequency);
    /// Gets the frequency of the oscillator
    DataType_ get_frequency() const;

    /// Sets the output volume, doesn't update the cache
    void set_volume(DataType_ volume);
    /// Gets the output volume
    DataType_ get_volume() const;

    /// Sets the offset of the generated signal, doesn't update the cache
    void set_offset(DataType_ offset);
    /// Gets the offset
    DataType_ get_offset() const;

    void full_setup() final;

  protected:
    void process_impl(gsl::index size) const final;
    
  private:
    DataType_ volume{1};
    DataType_ offset{0};
    DataType_ frequency{0};
    DataType_ frequ_cos{1};
    DataType_ frequ_sin{0};

    mutable DataType_ cos{1};
    mutable DataType_ sin{0};
  };
}

#endif
