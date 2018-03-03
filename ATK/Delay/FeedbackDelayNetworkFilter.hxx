/**
 * \file FeedbackDelayNetworkFilter.hxx
 */

#ifndef ATK_DELAY_FEEDBACKDELAYNETWORKFILTER_HXX
#define ATK_DELAY_FEEDBACKDELAYNETWORKFILTER_HXX

#include <ATK/Delay/FeedbackDelayNetworkFilter.h>

#include <complex>

#include <Eigen/Dense>

namespace ATK
{
  template<typename Mixture>
  class FeedbackDelayNetworkFilter<Mixture>::HFDN_Impl: public Mixture::MixtureImpl
  {
  public:
    typedef typename Mixture::MixtureImpl::Vector Vector;
    typedef typename Mixture::MixtureImpl::Matrix Matrix;

    std::vector<Vector, boost::alignment::aligned_allocator<Vector, 32>> delay_line;
    std::vector<Vector, boost::alignment::aligned_allocator<Vector, 32>> processed_input;
    int64_t index;
    Vector ingain;
    Vector outgain;
    Vector feedback;

    HFDN_Impl(std::size_t max_delay)
      :processed_input(max_delay, Vector::Zero()), index(0), ingain(Vector::Zero()), outgain(Vector::Zero()), feedback(Vector::Zero())
    {
    }
  };

  template<typename Mixture>
  FeedbackDelayNetworkFilter<Mixture>::FeedbackDelayNetworkFilter(std::size_t max_delay)
    :Parent(1, 2), impl(new HFDN_Impl(max_delay)), max_delay(max_delay)
  {
    delay.fill(max_delay - 1);
  }

  template<typename Mixture>
  FeedbackDelayNetworkFilter<Mixture>::~FeedbackDelayNetworkFilter()
  {
  }

  template<typename Mixture>
  void FeedbackDelayNetworkFilter<Mixture>::set_delay(unsigned int channel, std::size_t delay)
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

  template<typename Mixture>
  std::size_t FeedbackDelayNetworkFilter<Mixture>::get_delay(unsigned int channel) const
  {
    return delay[channel];
  }

  template<typename Mixture>
  void FeedbackDelayNetworkFilter<Mixture>::set_ingain(unsigned int channel, DataType ingain)
  {
    impl->ingain(channel) = ingain;
  }

  template<typename Mixture>
  typename FeedbackDelayNetworkFilter<Mixture>::DataType FeedbackDelayNetworkFilter<Mixture>::get_ingain(unsigned int channel) const
  {
    return impl->ingain(channel);
  }

  template<typename Mixture>
  void FeedbackDelayNetworkFilter<Mixture>::set_feedback(unsigned int channel, DataType feedback)
  {
    if (std::abs(feedback * static_cast<DataType>(Mixture::gain_factor)) >= 1)
    {
      throw std::out_of_range("Feedback must be between " + std::to_string(-Mixture::gain_factor) + " and " + std::to_string(Mixture::gain_factor) + " to avoid divergence");
    }
    impl->feedback(channel) = feedback * static_cast<DataType>(Mixture::gain_factor);
  }

  template<typename Mixture>
  typename FeedbackDelayNetworkFilter<Mixture>::DataType FeedbackDelayNetworkFilter<Mixture>::get_feedback(unsigned int channel) const
  {
    return impl->feedback(channel) / static_cast<DataType>(Mixture::gain_factor);
  }

  template<typename Mixture>
  void FeedbackDelayNetworkFilter<Mixture>::set_outgain(unsigned int channel, DataType outgain)
  {
    impl->outgain(channel) = outgain;
  }

  template<typename Mixture>
  typename FeedbackDelayNetworkFilter<Mixture>::DataType FeedbackDelayNetworkFilter<Mixture>::get_outgain(unsigned int channel) const
  {
    return impl->outgain(channel);
  }

  template<typename Mixture>
  void FeedbackDelayNetworkFilter<Mixture>::full_setup()
  {
    // reset the delay line
    impl->processed_input.assign(max_delay, HFDN_Impl::Vector::Zero());
  }

  template<typename Mixture>
  void FeedbackDelayNetworkFilter<Mixture>::process_impl(std::size_t size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];

    impl->delay_line.resize(size);

    for (gsl::index i = 0; i < size; ++i)
    {
      for (gsl::index channel = 0; channel < nb_channels; ++channel)
      {
        auto j = impl->index - static_cast<int64_t>(delay[channel]);
        if (j < 0)
        {
          j += max_delay;
        }

        impl->delay_line[i](channel) = impl->processed_input[j](channel);
      }
      impl->processed_input[impl->index] = (impl->ingain * input[i]).array() + impl->mix(impl->delay_line[i]).array() * impl->feedback.array();

      output[i] = impl->outgain.dot(impl->delay_line[i]);

      ++impl->index;
      if(impl->index == max_delay)
        impl->index = 0;
    }
  }
}

#endif
