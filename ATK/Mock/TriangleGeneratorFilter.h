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
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs;
    using Parent::output_sampling_rate;

    /// Constructor
    TriangleGeneratorFilter();
    /// Destructor
    ~TriangleGeneratorFilter() override;
    
    /// Sets the amplitude of the triangle
    void set_amplitude(DataType_ amplitude);
    /// Sets the frequency of the triangle
    void set_frequency(int frequency);
    
  protected:
    void process_impl(std::size_t size) const final;

  private:
    mutable double state;
    mutable bool ascending;
    DataType_ amplitude;
    int frequency;
  };
}

#endif
