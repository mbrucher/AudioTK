/**
 * \file TriangleCheckerFilter.h
 */

#ifndef ATK_MOCK_TRIANGLECHECKERFILTER_H
#define ATK_MOCK_TRIANGLECHECKERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Core/TypeTraits.h>

#include <ATK/Mock/config.h>

namespace ATK
{
  ///  Filter that checks that the input is a synced triangle signal
  template<class DataType_>
  class ATK_MOCK_EXPORT TriangleCheckerFilter final : public TypedBaseFilter<DataType_>
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
    ~TriangleCheckerFilter() override;
    
    /// Sets the amplitude of the triangle
    void set_amplitude(DataType_ amplitude);
    /// Sets the frequency of the triangle
    void set_frequency(int frequency);

  protected:
    void process_impl(gsl::index size) const final;
    
  private:
    mutable double state;
    mutable bool ascending;
    DataType amplitude;
    int frequency;
  };
}

#endif
