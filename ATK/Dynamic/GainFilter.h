/**
 * \file GainFilter.h
 */

#ifndef ATK_DYNAMIC_GAINFILTER_H
#define ATK_DYNAMIC_GAINFILTER_H

#include <atomic>
#include <future>
#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Gain generic filter. Based on a LUT table, compute the gain.
  /*!
   * Be aware that the threshold is taken as a power measure contrary to the gain (there is a factor 2 in the dB computation)
   */
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT ParentGainFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    * @param LUTsize is the total LUT size used by the filter
    * @param LUTprecision is the number of elements used to compute values < 1
    */
    ParentGainFilter(int nb_channels = 1, size_t LUTsize = 128*1024, size_t LUTprecision = 64);
    /// Destructor
    ~ParentGainFilter();
    
    /// Sets the threshold (superior to 0)
    void set_threshold(DataType_ threshold);
    /// Sets the threshold in dB
    void set_threshold_db(DataType_ threshold_db);
    /// Returns the threshold
    DataType_ get_threshold() const;
    /// 1:ratio is defined as the reduction factor. 1:1 is a reduction of 0, 1:2 is a reduction by a factor of 2...
    void set_ratio(DataType_ ratio);
    /// Returns ratio
    DataType_ get_ratio() const;

  protected:
    /// Threshold
    DataType_ threshold;
    /// Ratio
    DataType_ ratio;

    virtual void start_recomputeLUT() = 0;

    size_t LUTsize;
    size_t LUTprecision;
    std::vector<DataType_> gainLUT;
  };

  template<class ParentFilter>
  class GainFilter: public ParentFilter
  {
  using ParentFilter::DataType;

  public:
    GainFilter(int nb_channels = 1, size_t LUTsize = 128 * 1024, size_t LUTprecision = 64)
    :ParentFilter(nb_channels, LUTsize, LUTprecision), isRunning(false), resetRequest(false)
    {
      start_recomputeLUT();
    }

    ~GainFilter()
    {
      //Future has to be deleted in child destructor as it uses computeGain
      if (recomputeFuture.valid())
      {
        recomputeFuture.wait();
      }
    }

  protected:
    /// Future used to track the thread recomputing the LUT
    std::future<void> recomputeFuture;
    /// Is the thread recomputing the LUT running (which way of computing the gain shall we use?)
    std::atomic<bool> isRunning;
    /// Indicates to start recomputing the LUT from the start, used when asked to change LUT parameters when the LUT is recomputed
    std::atomic<bool> resetRequest;

    virtual void process_impl(int64_t size) const override final
    {
//      assert(nb_input_ports == nb_output_ports);

      if (isRunning)
      {
        process_impl_direct(size);
      }
      else
      {
        process_impl_LUT(size);
      }
    }

    /// Computes the gain based on the LUT
    void process_impl_LUT(int64_t size) const
    {
      for (int channel = 0; channel < nb_output_ports; ++channel)
      {
        const DataType* ATK_RESTRICT input = converted_inputs[channel];
        DataType* ATK_RESTRICT output = outputs[channel];
        for (int64_t i = 0; i < size; ++i)
        {
          DataType value = *(input++) * threshold;
          int step = static_cast<int>(value * LUTprecision);
          if (step >= LUTsize)
          {
            step = static_cast<int>(LUTsize) - 1;
          }
          *(output++) = gainLUT[step];
        }
      }
    }

    /// Computes the gain directly
    void process_impl_direct(int64_t size) const
    {
      for (int channel = 0; channel < nb_output_ports; ++channel)
      {
        const DataType* ATK_RESTRICT input = converted_inputs[channel];
        DataType* ATK_RESTRICT output = outputs[channel];
        for (int64_t i = 0; i < size; ++i)
        {
          *(output++) = computeGain(*(input++) * threshold);
        }
      }
    }

    /// Asks to recompute the LUT
    virtual void recomputeLUT()
    {
      auto gainLUT_ptr = gainLUT.data();

      for (int i = 0; i < LUTsize; i += 16)
      {
        if (resetRequest)
        {
          i = 0;
          resetRequest = false;
          gainLUT_ptr = gainLUT.data();
        }
        for (int j = 0; j < 16; ++j)
        {
          *(gainLUT_ptr++) = computeGain(static_cast<DataType>(16 * i + j) / LUTprecision);
        }
      }
      isRunning = false;
    }

    /// Actually recomputes the LUT
    void start_recomputeLUT() override final
    {
      if (isRunning)
      {
        resetRequest = true; // Tell the thread to start over
      }
      else
      {
        isRunning = true; // starting a new thread
        recomputeFuture = std::async(&GainFilter<ParentFilter>::recomputeLUT, this);
      }
    }

  };
}

#endif
