/**
 * \file WaveshapperFilter.h
 */

#ifndef ATK_DISTORTION_WAVESHAPER_H
#define ATK_DISTORTION_WAVESHAPER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Distortion/config.h>

#include <cassert>
#include <vector>

namespace ATK
{
  /// Waveshapper generic filter. Based on a LUT table, compute the shape.
  template<class ParentFilter>
  class WaveshaperFilter final : public ParentFilter
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

    WaveshaperFilter(gsl::index nb_channels = 1, size_t LUTsize = 128 * 1024, size_t LUTprecision = 1024)
    :Parent(nb_channels, nb_channels), LUTsize(LUTsize), LUTprecision(LUTprecision), positiveShaperLUT(LUTsize, 0), negativeShaperLUT(LUTsize, 0)
    {
    }

    ~WaveshaperFilter() override
    {
    }

  protected:
    void process_impl(gsl::index size) const final
    {
      assert(nb_input_ports == nb_output_ports);

      for (gsl::index channel = 0; channel < nb_output_ports; ++channel)
      {
        const auto* ATK_RESTRICT input = converted_inputs[channel];
        auto* ATK_RESTRICT output = outputs[channel];
        for (gsl::index i = 0; i < size; ++i)
        {
          if(input[i] < 0)
          {
            size_t step = static_cast<size_t>(-input[i] * LUTprecision);
            if (step >= LUTsize)
            {
              step = static_cast<int>(LUTsize) - 1;
            }
            output[i] = negativeShaperLUT[step];
          }
          else
          {
            size_t step = static_cast<size_t>(input[i] * LUTprecision);
            if (step >= LUTsize)
            {
              step = static_cast<int>(LUTsize) - 1;
            }
            output[i] = positiveShaperLUT[step];
          }
        }
      }
    }

    size_t LUTsize;
    size_t LUTprecision;
    std::vector<DataType_> positiveShaperLUT;
    std::vector<DataType_> negativeShaperLUT;
  };
}

#endif
