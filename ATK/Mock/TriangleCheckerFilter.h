/**
 * \file TriangleCheckerFilter.h
 */

#ifndef ATK_MOCK_TRIANGLECHECKERFILTER_H
#define ATK_MOCK_TRIANGLECHECKERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<class DataType_>
  class TriangleCheckerFilter : public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;

    TriangleCheckerFilter();
    virtual ~TriangleCheckerFilter();
    
    void set_amplitude(DataType amplitude);
    void set_frequency(int frequency);

  protected:
    virtual void process_impl(long size);
    
    double state;
    bool ascending;
    DataType amplitude;
    int frequency;
  };
}

#endif
