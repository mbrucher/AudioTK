/**
 * \file GainFilter.cpp
 */

#include "GainFilter.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  GainFilter<DataType_>::GainFilter(int nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, nb_channels), threshold(1), ratio(1), softness(static_cast<DataType_>(.0001)), LUTsize(LUTsize), LUTprecision(LUTprecision), gainLUT(LUTsize, 0),
  isRunning(false), resetRequest(false)
  {
  }
  
  template<typename DataType_>
  GainFilter<DataType_>::~GainFilter()
  {
  }

  template<typename DataType_>
  void GainFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);

    if(isRunning)
    {
      process_impl_direct(size);
    }
    else
    {
      process_impl_LUT(size);
    }
  }

  template<typename DataType_>
  void GainFilter<DataType_>::process_impl_LUT(int64_t size) const
  {
    for(int channel = 0; channel < nb_output_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(int64_t i = 0; i < size; ++i)
      {
        DataType_ value = *(input++) * threshold;
        int step = static_cast<int>(value * LUTprecision);
        if(step >= LUTsize)
        {
          step = static_cast<int>(LUTsize) - 1;
        }
        *(output++) = gainLUT[step];
      }
    }
  }

  template<typename DataType_>
  void GainFilter<DataType_>::process_impl_direct(int64_t size) const
  {
    for(int channel = 0; channel < nb_output_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(int64_t i = 0; i < size; ++i)
      {
        *(output++) = computeGain(*(input++) * threshold);
      }
    }
  }

  template<typename DataType_>
  void GainFilter<DataType_>::set_threshold(DataType_ threshold)
  {
    if (threshold <= 0)
    {
      throw std::out_of_range("Threshold factor must be strictly positive value");
    }
    this->threshold = 1 / threshold;
  }

  template<typename DataType_>
  void GainFilter<DataType_>::set_threshold_db(DataType_ threshold_db)
  {
    this->threshold = static_cast<DataType_>(std::pow(10, - threshold_db / 10));
  }

  template<typename DataType_>
  DataType_ GainFilter<DataType_>::get_threshold() const
  {
    return 1 / threshold;
  }

  template<typename DataType_>
  void GainFilter<DataType_>::set_ratio(DataType_ ratio)
  {
    if (ratio <= 0)
    {
      throw std::out_of_range("Ratio factor must be higher than 0");
    }
    this->ratio = ratio;
    start_recomputeLUT();
  }

  template<typename DataType_>
  DataType_ GainFilter<DataType_>::get_ratio() const
  {
    return ratio;
  }

  template<typename DataType_>
  void GainFilter<DataType_>::set_softness(DataType_ softness)
  {
    if (softness <= 0)
    {
      throw std::out_of_range("Softness factor must be strictly positive value");
    }
    this->softness = softness;
    start_recomputeLUT();
  }

  template<typename DataType_>
  DataType_ GainFilter<DataType_>::get_softness() const
  {
    return softness;
  }

  template<typename DataType_>
  void GainFilter<DataType_>::recomputeLUT()
  {
    auto gainLUT_ptr = gainLUT.data();

    for(int i = 0; i < LUTsize; ++i)
    {
      if(resetRequest)
      {
        i = 0;
        resetRequest = false;
        gainLUT_ptr = gainLUT.data();
      }
      *(gainLUT_ptr++) = computeGain(static_cast<DataType>(i) / LUTprecision);
    }
    isRunning = false;
  }

  template<typename DataType_>
  void GainFilter<DataType_>::start_recomputeLUT()
  {
    if(isRunning)
    {
      resetRequest = true; // Tell the thread to start over
    }
    else
    {
      isRunning = true; // starting a new thread
      recomputeFuture = std::async(&GainFilter<DataType_>::recomputeLUT, this);
    }
  }

  template class GainFilter<float>;
  template class GainFilter<double>;
}
