/**
 * \file GainFilter.h
 */

#ifndef ATK_DYNAMIC_GAINFILTER_H
#define ATK_DYNAMIC_GAINFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Dynamic/config.h>

#include <cassert>
#include <atomic>
#include <future>
#include <vector>

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
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    * @param LUTsize is the total LUT size used by the filter
    * @param LUTprecision is the number of elements used to compute values < 1
    */
    ParentGainFilter(gsl::index nb_channels = 1, size_t LUTsize = 128*1024, size_t LUTprecision = 64);
    /// Destructor
    ~ParentGainFilter() override = default;
    
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
    DataType_ threshold{1};
    /// Ratio
    DataType_ ratio{1};

    virtual void start_recomputeLUT() = 0;

    gsl::index LUTsize{0};
    gsl::index LUTprecision{0};
    std::vector<DataType_> gainLUT;
  };

  template<class ParentFilter>
  class GainFilter final : public ParentFilter
  {
  public:
    using Parent = ParentFilter;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::threshold;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::computeGain;
    using Parent::LUTsize;
    using Parent::LUTprecision;
    using Parent::gainLUT;

    GainFilter(gsl::index nb_channels = 1, gsl::index LUTsize = 128 * 1024, gsl::index LUTprecision = 64)
    :ParentFilter(nb_channels, LUTsize, LUTprecision)
    {
      start_recomputeLUT();
    }

    ~GainFilter() override
    {
      //Future has to be deleted in child destructor as it uses computeGain
      wait_for_LUT_completion();
    }

    void wait_for_LUT_completion()
    {
      if (recomputeFuture.valid())
      {
        recomputeFuture.wait();
      }
    }

  protected:
    /// Future used to track the thread recomputing the LUT
    std::future<void> recomputeFuture;
    /// Is the thread recomputing the LUT running (which way of computing the gain shall we use?)
    std::atomic<bool> isRunning{false};
    /// Indicates to start recomputing the LUT from the start, used when asked to change LUT parameters when the LUT is recomputed
    std::atomic<bool> resetRequest{false};

    void process_impl(gsl::index size) const final
    {
      assert(nb_input_ports == nb_output_ports);

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
    void process_impl_LUT(gsl::index size) const
    {
      for (gsl::index channel = 0; channel < nb_output_ports; ++channel)
      {
        const auto* ATK_RESTRICT input = converted_inputs[channel];
        auto* ATK_RESTRICT output = outputs[channel];
        for (gsl::index i = 0; i < size; ++i)
        {
          auto value = input[i] * threshold * LUTprecision;
          auto step = std::lround(std::ceil(value));
          if (step >= LUTsize - 1)
          {
            step = static_cast<int>(LUTsize) - 1;
            output[i] = gainLUT[step];
          }
          else
          {
            output[i] = (1 - (value - step)) * gainLUT[step] + (value - step) * gainLUT[step + 1];
          }
        }
      }
    }

    /// Computes the gain directly
    void process_impl_direct(gsl::index size) const
    {
      for (gsl::index channel = 0; channel < nb_output_ports; ++channel)
      {
        const auto* ATK_RESTRICT input = converted_inputs[channel];
        auto* ATK_RESTRICT output = outputs[channel];
        for (gsl::index i = 0; i < size; ++i)
        {
          output[i] = computeGain(*(input++) * threshold);
        }
      }
    }

    /// Asks to recompute the LUT
    void recomputeLUT()
    {
      auto gainLUT_ptr = gainLUT.data();

      for (gsl::index i = 0; i < LUTsize; i += 16)
      {
        if (resetRequest)
        {
          i = 0;
          resetRequest = false;
          gainLUT_ptr = gainLUT.data();
        }
        for (gsl::index j = 0; j < 16; ++j)
        {
          *(gainLUT_ptr++) = computeGain(static_cast<DataType>(i + j) / LUTprecision);
        }
      }
      isRunning = false;
    }

    /// Actually recomputes the LUT
    void start_recomputeLUT() final
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
