#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter, PipelineGlobalSinkFilter
from ATK.EQ import DoubleCustomIIRFilter
from ATK.Tools import DoubleCachedSinusGeneratorFilter, DoubleCachedCosinusGeneratorFilter, DoubleApplyGainFilter, DoubleVolumeFilter, DoubleSumFilter

sample_rate = 96000

def filter(input, blend=0, feedback=0, feedforward=1):
  import numpy as np
  output1 = np.zeros(input.shape, dtype=np.float64)
  output2 = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)

  allpass1filter = DoubleCustomIIRFilter()
  allpass1filter.set_input_sampling_rate(sample_rate)
  allpass1filter.set_input_port(0, infilter, 0)
  allpass1filter.set_coefficients_in((0.0000, 0.3855, 0.0000, 1.3313, 0.0000, 1.0000)[::-1])
  allpass1filter.set_coefficients_out((-0.0000, -1.3313, 0.0000, -0.3855, 0)[::-1])

  allpass2filter = DoubleCustomIIRFilter()
  allpass2filter.set_input_sampling_rate(sample_rate)
  allpass2filter.set_input_port(0, infilter, 0)
  allpass2filter.set_coefficients_in((0.0947, 0.0000, 0.8335, 0.0000, 1.0000)[::-1])
  allpass2filter.set_coefficients_out((0.0000, -0.8335, 0.0000, -0.0947)[::-1])

  sinusfilter = DoubleCachedSinusGeneratorFilter(100, 1)
  sinusfilter.set_input_sampling_rate(sample_rate)

  cosinusfilter = DoubleCachedCosinusGeneratorFilter(100, 1)
  cosinusfilter.set_input_sampling_rate(sample_rate)
  
  applygainFilter = DoubleApplyGainFilter(2)
  applygainFilter.set_input_sampling_rate(sample_rate)
  applygainFilter.set_input_port(0, allpass1filter, 0)
  applygainFilter.set_input_port(1, sinusfilter, 0)
  applygainFilter.set_input_port(2, allpass2filter, 0)
  applygainFilter.set_input_port(3, cosinusfilter, 0)

  volumeFilter = DoubleVolumeFilter()
  volumeFilter.set_input_sampling_rate(sample_rate)
  volumeFilter.set_volume(-1)
  volumeFilter.set_input_port(0, applygainFilter, 1)

  sum1Filter = DoubleSumFilter()
  sum1Filter.set_input_sampling_rate(sample_rate)
  sum1Filter.set_input_port(0, applygainFilter, 0)
  sum1Filter.set_input_port(1, volumeFilter, 0)

  sum2Filter = DoubleSumFilter()
  sum2Filter.set_input_sampling_rate(sample_rate)
  sum2Filter.set_input_port(0, applygainFilter, 0)
  sum2Filter.set_input_port(1, applygainFilter, 1)

  out1filter = DoubleOutPointerFilter(output1, False)
  out1filter.set_input_sampling_rate(sample_rate)
  out1filter.set_input_port(0, sum1Filter, 0)

  out2filter = DoubleOutPointerFilter(output2, False)
  out2filter.set_input_sampling_rate(sample_rate)
  out2filter.set_input_port(0, sum2Filter, 0)

  pipelinesink = PipelineGlobalSinkFilter()
  pipelinesink.set_input_sampling_rate(sample_rate)
  pipelinesink.add_filter(out1filter)
  pipelinesink.add_filter(out2filter)
  pipelinesink.process(input.shape[1])

  return output1, output2
if __name__ == "__main__":
  import numpy as np
  size = 960000
  
  x = np.arange(size, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(x * 2 * np.pi * 1000)

  np.savetxt("input.txt", d)
  out1, out2 = filter(d, feedforward=1, blend=0.7, feedback=-0.7)
  np.savetxt("output1.txt", out1)
  np.savetxt("output2.txt", out2)
