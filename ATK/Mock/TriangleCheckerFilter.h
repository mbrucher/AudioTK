/**
 * \file TriangleCheckerFilter.h
 */

#ifndef ATK_MOCK_TRIANGLECHECKERFILTER_H
#define ATK_MOCK_TRIANGLECHECKERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

#include "config.h"

namespace ATK
{
  ///  Filter that checks that the input is a synced triangle signal
  template<class DataType_>
  class ATK_MOCK_EXPORT TriangleCheckerFilter : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;

    /// Constructor
    TriangleCheckerFilter();
    /// Destructor
    virtual ~TriangleCheckerFilter();
    
    /// Sets the amplitude of the triangle
    void set_amplitude(DataType_ amplitude);
    /// Sets the frequency of the triangle
    void set_frequency(int frequency);

  protected:
    virtual void process_impl(std::size_t size) const override final;
    
  private:
    mutable double state;
    mutable bool ascending;
    DataType amplitude;
    int frequency;
  };
}

#endif
