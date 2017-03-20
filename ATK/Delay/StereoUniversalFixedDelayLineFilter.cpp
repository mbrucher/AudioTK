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
  template<typename DataType>
  class StereoUniversalFixedDelayLineFilter<DataType>::SUFDLF_Impl
  {
  public:
    std::vector<DataType> delay_line_l;
    std::vector<DataType> delay_line_r;
    std::vector<DataType> processed_input_l;
    std::vector<DataType> processed_input_r;

    SUFDLF_Impl(std::size_t max_delay)
      :processed_input_l(max_delay, 0), processed_input_r(max_delay, 0)
    {
    }

    void update_delay_line(std::size_t max_delay)
    {
      auto array_size_r = processed_input_l.size();
      // Update delay line
      ATK_VECTORIZE for (std::size_t i = 0; i < max_delay; ++i)
      {
        processed_input_l[i] = processed_input_l[array_size_r + i - max_delay];
        processed_input_r[i] = processed_input_r[array_size_r + i - max_delay];
      }
    }
  };

  template<typename DataType_>
  StereoUniversalFixedDelayLineFilter<DataType_>::StereoUniversalFixedDelayLineFilter(std::size_t max_delay)
    :Parent(2, 2), impl(new SUFDLF_Impl(max_delay)), delay_l(0), delay_r(0), max_delay(max_delay), blend_l(0), blend_r(0),
    feedback_l_l(0), feedback_l_r(0), feedback_r_l(0), feedback_r_r(0), feedforward_l_l(1), feedforward_l_r(0), feedforward_r_l(0), feedforward_r_r(1)
  {
  }
  
  template<typename DataType_>
  StereoUniversalFixedDelayLineFilter<DataType_>::~StereoUniversalFixedDelayLineFilter()
  {
  }
  
  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_delay_ch1(std::size_t delay)
  {
    if(delay == 0)
    {
      throw std::out_of_range("Delay must be strictly positive");
    }
    if(delay >= max_delay)
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    delay_l = delay;
  }

  template<typename DataType_>
  std::size_t StereoUniversalFixedDelayLineFilter<DataType_>::get_delay_ch1() const
  {
    return delay_l;
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::set_delay_ch2(std::size_t delay)
  {
    if(delay <= 0)
    {
      throw std::out_of_range("Delay must be strictly positive");
    }
    if(delay >= max_delay)
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    delay_r = delay;
  }

  template<typename DataType_>
  std::size_t StereoUniversalFixedDelayLineFilter<DataType_>::get_delay_ch2() const
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
  void StereoUniversalFixedDelayLineFilter<DataType_>::full_setup()
  {
    // reset the delay line
    impl->processed_input_l.assign(max_delay, 0);
    impl->processed_input_r.assign(max_delay, 0);
  }

  template<typename DataType_>
  void StereoUniversalFixedDelayLineFilter<DataType_>::process_impl(std::size_t size) const
  {
    impl->update_delay_line(max_delay);

    impl->delay_line_l.resize(size);
    impl->delay_line_r.resize(size);
    impl->processed_input_l.resize(max_delay + size);
    impl->processed_input_r.resize(max_delay + size);

    const DataType* ATK_RESTRICT inputl = converted_inputs[0];
    const DataType* ATK_RESTRICT inputr = converted_inputs[1];
    DataType* ATK_RESTRICT outputl = outputs[0];
    DataType* ATK_RESTRICT outputr = outputs[1];

    DataType* ATK_RESTRICT delay_line_l = impl->delay_line_l.data();
    DataType* ATK_RESTRICT delay_line_r = impl->delay_line_r.data();
    DataType* ATK_RESTRICT processed_input_l = impl->processed_input_l.data();
    DataType* ATK_RESTRICT processed_input_r = impl->processed_input_r.data();

    ATK_VECTORIZE for(std::size_t i = 0; i < size; ++i)
    {
      delay_line_l[i] = processed_input_l[i + max_delay - delay_l];
      delay_line_r[i] = processed_input_r[i + max_delay - delay_r];
      processed_input_l[max_delay + i] = inputl[i] + feedback_l_l * processed_input_l[max_delay + i - delay_l] + feedback_r_l * processed_input_r[max_delay + i - delay_r];
      processed_input_r[max_delay + i] = inputr[i] + feedback_l_r * processed_input_l[max_delay + i - delay_l] + feedback_r_r * processed_input_r[max_delay + i - delay_r];
      outputl[i] = blend_l * processed_input_l[max_delay + i] + feedforward_l_l * delay_line_l[i] + feedforward_r_l * delay_line_r[i];
      outputr[i] = blend_r * processed_input_r[max_delay + i] + feedforward_l_r * delay_line_l[i] + feedforward_r_r * delay_line_r[i];
    }
  }
  
  template class StereoUniversalFixedDelayLineFilter<float>;
  template class StereoUniversalFixedDelayLineFilter<double>;
}
