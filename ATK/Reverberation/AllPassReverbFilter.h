/**
 * \file AllPassReverbFilter.h
 */

#ifndef ATK_REVERBERATION_ALLPASSREVERBFILTER_H
#define ATK_REVERBERATION_ALLPASSREVERBFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /**
   * Simple all pass reverb filter
   */
  template<typename DataType_>
  class ATK_REVERBERATION_EXPORT AllPassReverbFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_delay;
    using Parent::outputs;
    using Parent::output_delay;

  public:
    AllPassReverbFilter(int max_delay);
    ~AllPassReverbFilter();

    void set_delay(int64_t delay);
    int64_t get_delay() const;

    void set_feedback(DataType_ feedback);
    DataType_ get_feedback() const;
  protected:
    virtual void process_impl(int64_t size) const override final;

    int64_t delay;
    DataType_ feedback;
  };
}

#endif
