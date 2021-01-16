/**
 * \file TriangleGeneratorFilter.h
 */

#ifndef ATK_MOCK_TRIANGLEGENERATORFILTER_H
#define ATK_MOCK_TRIANGLEGENERATORFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Core/TypeTraits.h>
#include <ATK/Mock/config.h>

namespace ATK
{
  /// A triangle signal generator for test purposes
  template<class DataType_>
  class ATK_MOCK_EXPORT TriangleGeneratorFilter final : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::outputs;
    using Parent::output_sampling_rate;

    /// Constructor
    TriangleGeneratorFilter();
    /// Destructor
    ~TriangleGeneratorFilter() override = default;
    
    /// Sets the amplitude of the triangle
    void set_amplitude(DataType_ amplitude);
    /// Sets the frequency of the triangle
    void set_frequency(int frequency);
    
  protected:
    void process_impl(gsl::index size) const final;

  private:
    mutable double state = 0;
    mutable bool ascending = true;
    DataType_ amplitude{1};
    int frequency{1};
  };
}

#endif
