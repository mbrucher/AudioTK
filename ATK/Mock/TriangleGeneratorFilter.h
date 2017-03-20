/**
 * \file TriangleGeneratorFilter.h
 */

#ifndef ATK_MOCK_TRIANGLEGENERATORFILTER_H
#define ATK_MOCK_TRIANGLEGENERATORFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

#include "config.h"

namespace ATK
{
  /// A triangle signal generator for test purposes
  template<class DataType_>
  class ATK_MOCK_EXPORT TriangleGeneratorFilter : public TypedBaseFilter<DataType_>
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
    virtual ~TriangleGeneratorFilter();
    
    /// Sets the amplitude of the triangle
    void set_amplitude(DataType_ amplitude);
    /// Sets the frequency of the triangle
    void set_frequency(int frequency);
    
  protected:
    virtual void process_impl(std::size_t size) const override final;

  private:
    mutable double state;
    mutable bool ascending;
    DataType_ amplitude;
    int frequency;
  };
}

#endif
