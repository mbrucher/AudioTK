/**
 * \file HadamardFeedbackDelayNetworkFilter.cpp
 */

#include "HadamardFeedbackDelayNetworkFilter.h"

#if ATK_EIGEN == 1

#include <cmath>
#include <cstring>
#include <complex>
#include <stdexcept>

#include <ATK/Core/TypeTraits.h>

#include <Eigen/Dense>

namespace ATK
{
  template<class DataType, unsigned int nb_channels>
  class HadamardFeedbackDelayNetworkFilter<DataType, nb_channels>::HFDN_Impl
  {
  public:
    typedef Eigen::Matrix<DataType, nb_channels, 1> Vector;
    typedef Eigen::Matrix<DataType, nb_channels, nb_channels> Matrix;

    std::vector<Vector> delay_line;
    std::vector<Vector> processed_input;
    const Matrix transition;
    Vector ingain;
    Vector outgain;
    Vector feedback;

    HFDN_Impl(std::size_t max_delay)
      :transition(create()), ingain(Vector::Zero()), outgain(Vector::Zero()), feedback(Vector::Zero())
    {
      // reset the delay line
      processed_input.assign(max_delay, Vector::Zero());
    }

    void update_delay_line(std::size_t max_delay)
    {
      auto array_size = processed_input.size();
      // Update delay line
      ATK_VECTORIZE for (std::size_t i = 0; i < max_delay; ++i)
      {
        processed_input[i] = processed_input[array_size + i - max_delay];
      }
    }

    Vector mix(const Vector& x) const
    {
      return transition * x;
    }

    Matrix create() const
    {
      Matrix transition;
      transition << 1, 1, 1, 1,
        1, -1, 1, -1,
        -1, -1, 1, 1,
        -1, 1, 1, -1;
      return transition;
    }
  };

  template<class DataType, unsigned int nb_channels>
  HadamardFeedbackDelayNetworkFilter<DataType, nb_channels>::HadamardFeedbackDelayNetworkFilter(std::size_t max_delay)
    :Parent(1, 1), impl(new HFDN_Impl(max_delay)), max_delay(max_delay)
  {
    delay.fill(max_delay - 1);
  }

  template<class DataType, unsigned int nb_channels>
  HadamardFeedbackDelayNetworkFilter<DataType, nb_channels>::~HadamardFeedbackDelayNetworkFilter()
  {
  }

  template<class DataType, unsigned int nb_channels>
  void HadamardFeedbackDelayNetworkFilter<DataType, nb_channels>::set_delay(unsigned int channel, std::size_t delay)
  {
    if (delay == 0)
    {
      throw std::out_of_range("Delay must be strictly positive");
    }
    if (delay >= max_delay)
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    this->delay[channel] = delay;
  }

  template<class DataType, unsigned int nb_channels>
  std::size_t HadamardFeedbackDelayNetworkFilter<DataType, nb_channels>::get_delay(unsigned int channel) const
  {
    return delay[channel];
  }

  template<class DataType_, unsigned int nb_channels>
  void HadamardFeedbackDelayNetworkFilter<DataType_, nb_channels>::set_ingain(unsigned int channel, DataType_ ingain)
  {
    impl->ingain(channel) = ingain;
  }

  template<class DataType_, unsigned int nb_channels>
  DataType_ HadamardFeedbackDelayNetworkFilter<DataType_, nb_channels>::get_ingain(unsigned int channel) const
  {
    return impl->ingain(channel);
  }

  template<class DataType_, unsigned int nb_channels>
  void HadamardFeedbackDelayNetworkFilter<DataType_, nb_channels>::set_feedback(unsigned int channel, DataType_ feedback)
  {
    if (std::abs(feedback) > 1)
    {
      throw std::out_of_range("Feedback must be between -1 and 1 to avoid divergence");
    }
    impl->feedback(channel) = feedback;
  }

  template<class DataType_, unsigned int nb_channels>
  DataType_ HadamardFeedbackDelayNetworkFilter<DataType_, nb_channels>::get_feedback(unsigned int channel) const
  {
    return impl->feedback(channel);
  }

  template<class DataType_, unsigned int nb_channels>
  void HadamardFeedbackDelayNetworkFilter<DataType_, nb_channels>::set_outgain(unsigned int channel, DataType_ outgain)
  {
    impl->outgain(channel) = outgain;
  }

  template<class DataType_, unsigned int nb_channels>
  DataType_ HadamardFeedbackDelayNetworkFilter<DataType_, nb_channels>::get_outgain(unsigned int channel) const
  {
    return impl->outgain(channel);
  }

  template<class DataType, unsigned int nb_channels>
  void HadamardFeedbackDelayNetworkFilter<DataType, nb_channels>::full_setup()
  {
    // reset the delay line
    impl->processed_input.assign(max_delay, HFDN_Impl::Vector::Zero());
  }

  template<class DataType, unsigned int nb_channels>
  void HadamardFeedbackDelayNetworkFilter<DataType, nb_channels>::process_impl(std::size_t size) const
  {
    impl->update_delay_line(max_delay);

    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];

    impl->delay_line.resize(size);
    impl->processed_input.resize(max_delay + size);

    for (std::size_t i = 0; i < size; ++i)
    {
      auto j = i + max_delay;
      for (unsigned int channel = 0; channel < nb_channels; ++channel)
      {
        impl->delay_line[i](channel) = impl->processed_input[j - delay[channel]](channel);
      }
      impl->processed_input[j] = (impl->ingain * input[i]).array() + impl->mix(impl->delay_line[i]).array() * impl->feedback.array();

      output[i] = impl->outgain.dot(impl->delay_line[i]);
    }
  }

  template class HadamardFeedbackDelayNetworkFilter<float, 4>;
  template class HadamardFeedbackDelayNetworkFilter<double, 4>;
  template class HadamardFeedbackDelayNetworkFilter<std::complex<float>, 4>;
  template class HadamardFeedbackDelayNetworkFilter<std::complex<double>, 4>;
}

#endif