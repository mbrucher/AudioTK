/**
 * \file StereoUniversalFixedDelayLineFilter.cpp
 */

#include "StereoUniversalFixedDelayLineFilter.h"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  StereoUniversalFixedDelayLineFilter<DataType_>::StereoUniversalFixedDelayLineFilter(int max_delay)
    :Parent(2, 2), delay_line_l(max_delay, 0), delay_line_r(max_delay, 0), delay_l(0), delay_r(0), blend_l(0), blend_r(0),
    feedback_l_l(0), feedback_l_r(0), feedback_r_l(0), feedback_r_r(0), feedforward_l_l(1), feedforward_l_r(0), feedforward_r_l(0), feedforward_r_r(1)
  {
  }
  
  template<typename DataType_>
  StereoUniversalFixedDelayLineFilter<DataType_>::~StereoUniversalFixedDelayLineFilter()
  {
    
  }
  
  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_delay_ch1(std::int64_t delay)
  {
    if(delay < 0)
    {
      throw std::out_of_range("Delay must be positive");
    }
    if(delay >= delay_line_l.size())
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    delay_l = delay;
  }

  template<typename DataType_>
  std::int64_t StereoUniversalFixedDelayLineFilter<DataType_>::get_delay_ch1() const
  {
    return delay_l;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_delay_ch2(std::int64_t delay)
  {
    if(delay < 0)
    {
      throw std::out_of_range("Delay must be positive");
    }
    if(delay >= delay_line_l.size())
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    delay_r = delay;
  }

  template<typename DataType_>
  std::int64_t StereoUniversalFixedDelayLineFilter<DataType_>::get_delay_ch2() const
  {
    return delay_r;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_blend_ch1(DataType_ blend)
  {
    blend_l = blend;
  }

  template<typename DataType_>
  DataType_ StereoUniversalFixedDelayLineFilter<DataType_>::get_blend_ch1() const
  {
    return blend_l;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_blend_ch2(DataType_ blend)
  {
    blend_r = blend;
  }

  template<typename DataType_>
  DataType_ StereoUniversalFixedDelayLineFilter<DataType_>::get_blend_ch2() const
  {
    return blend_r;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_feedback_ch1_ch1(DataType_ feedback)
  {
    if(std::abs(feedback) > 1)
    {
      throw std::out_of_range("Feedback must be between -1 and 1 to avoid divergence");
    }
    feedback_l_l = feedback;
  }

  template<typename DataType_>
  DataType_ StereoUniversalFixedDelayLineFilter<DataType_>::get_feedback_ch1_ch1() const
  {
    return feedback_l_l;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_feedback_ch1_ch2(DataType_ feedback)
  {
    if(std::abs(feedback) > 1)
    {
      throw std::out_of_range("Feedback must be between -1 and 1 to avoid divergence");
    }
    feedback_l_r = feedback;
  }

  template<typename DataType_>
  DataType_ StereoUniversalFixedDelayLineFilter<DataType_>::get_feedback_ch1_ch2() const
  {
    return feedback_l_r;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_feedback_ch2_ch1(DataType_ feedback)
  {
    if(std::abs(feedback) > 1)
    {
      throw std::out_of_range("Feedback must be between -1 and 1 to avoid divergence");
    }
    feedback_r_l = feedback;
  }

  template<typename DataType_>
  DataType_ StereoUniversalFixedDelayLineFilter<DataType_>::get_feedback_ch2_ch1() const
  {
    return feedback_r_l;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_feedback_ch2_ch2(DataType_ feedback)
  {
    if(std::abs(feedback) > 1)
    {
      throw std::out_of_range("Feedback must be between -1 and 1 to avoid divergence");
    }
    feedback_r_r = feedback;
  }

  template<typename DataType_>
  DataType_ StereoUniversalFixedDelayLineFilter<DataType_>::get_feedback_ch2_ch2() const
  {
    return feedback_r_r;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_feedforward_ch1_ch1(DataType_ feedforward)
  {
    feedforward_l_l = feedforward;
  }

  template<typename DataType_>
  DataType_ StereoUniversalFixedDelayLineFilter<DataType_>::get_feedforward_ch1_ch1() const
  {
    return feedforward_l_l;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_feedforward_ch1_ch2(DataType_ feedforward)
  {
    feedforward_l_r = feedforward;
  }

  template<typename DataType_>
  DataType_ StereoUniversalFixedDelayLineFilter<DataType_>::get_feedforward_ch1_ch2() const
  {
    return feedforward_r_r;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_feedforward_ch2_ch1(DataType_ feedforward)
  {
    feedforward_r_l = feedforward;
  }
  template<typename DataType_>
  DataType_ StereoUniversalFixedDelayLineFilter<DataType_>::get_feedforward_ch2_ch1() const
  {
    return feedforward_r_l;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_feedforward_ch2_ch2(DataType_ feedforward)
  {
    feedforward_r_r = feedforward;
  }

  template<typename DataType_>
  DataType_ StereoUniversalFixedDelayLineFilter<DataType_>::get_feedforward_ch2_ch2() const
  {
    return feedforward_r_r;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::process_impl(std::int64_t size)
  {
    processed_input_l.resize(size);
    processed_input_r.resize(size);

    const DataType* ATK_RESTRICT inputl = converted_inputs[0];
    const DataType* ATK_RESTRICT inputr = converted_inputs[1];
    DataType* ATK_RESTRICT outputl = outputs[0];
    DataType* ATK_RESTRICT outputr = outputs[1];

    std::int64_t delay_line_usage_l = std::min(delay_l, size);
    std::int64_t delay_line_usage_r = std::min(delay_r, size);

    // Update intermediate input
    for(std::int64_t i = 0; i < delay_line_usage_l; ++i)
    {
      processed_input_l[i] = inputl[i] + feedback_l_l * delay_line_l[delay_line_l.size() + i - delay_l] + feedback_r_l * delay_line_r[delay_line_r.size() + i - delay_r];
      processed_input_r[i] = inputr[i] + feedback_l_r * delay_line_l[delay_line_l.size() + i - delay_l] + feedback_r_l * delay_line_r[delay_line_r.size() + i - delay_r];
    }
    for(std::int64_t i = delay_l; i < size; ++i)
    {
      processed_input_l[i] = inputl[i] + feedback_l_l * processed_input_l[i - delay_l] + feedback_r_l * processed_input_r[i - delay_r];
      processed_input_r[i] = inputr[i] + feedback_l_r * processed_input_r[i - delay_l] + feedback_r_r * processed_input_r[i - delay_r];
    }

    //update output
    for(std::int64_t i = 0; i < delay_line_usage_l; ++i)
    {
      outputl[i] = blend_l * processed_input_l[i] + feedforward_l_l *  delay_line_l[delay_line_l.size() + i - delay_l] + feedforward_r_l *  delay_line_r[delay_line_r.size() + i - delay_r];
      outputr[i] = blend_r * processed_input_r[i] + feedforward_l_r *  delay_line_l[delay_line_l.size() + i - delay_l] + feedforward_r_r *  delay_line_r[delay_line_r.size() + i - delay_r];
    }
    for(std::int64_t i = delay_l; i < size; ++i)
    {
      outputl[i] = blend_l * processed_input_l[i] + feedforward_l_l * processed_input_l[i - delay_l] + feedforward_r_l * processed_input_r[i - delay_r];
      outputr[i] = blend_r * processed_input_r[i] + feedforward_l_r * processed_input_l[i - delay_l] + feedforward_r_r * processed_input_r[i - delay_r];
    }

    // Update delay line
    for(std::int64_t i = 0; i < std::int64_t(delay_line_l.size()) - size; ++i)
    {
      delay_line_l[i] = delay_line_l[i + size];
      delay_line_r[i] = delay_line_r[i + size];
    }
    std::int64_t minimum = std::max(std::int64_t(0), std::int64_t(delay_line_l.size()) - size);
    for(std::int64_t i = minimum; i < delay_line_l.size(); ++i)
    {
      delay_line_r[i] = processed_input_l[size + i - delay_line_r.size()];
      delay_line_r[i] = processed_input_r[size + i - delay_line_r.size()];
    }
  }
  
  template class StereoUniversalFixedDelayLineFilter<float>;
  template class StereoUniversalFixedDelayLineFilter<double>;
}
