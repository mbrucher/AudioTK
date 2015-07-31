#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Dynamic import DoubleGainCompressorFilter, DoubleGainFractionalCompressorFilter
from ATK.Tools import DoubleApplyGainFilter

import matplotlib.pyplot as plt

sample_rate = 96000

def filter(input, ratio=4, threshold=1, softness=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  input2 = input**2
  in2filter = DoubleInPointerFilter(input2, False)
  in2filter.set_input_sampling_rate(sample_rate)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)

  gainfilter = DoubleGainCompressorFilter(1)
  gainfilter.set_input_sampling_rate(sample_rate)
  gainfilter.set_input_port(0, in2filter, 0)
  gainfilter.set_threshold(threshold)
  gainfilter.set_ratio(ratio)
  gainfilter.set_softness(softness)

  applygainfilter = DoubleApplyGainFilter(1)
  applygainfilter.set_input_sampling_rate(sample_rate)
  applygainfilter.set_input_port(0, gainfilter, 0)
  applygainfilter.set_input_port(1, infilter, 0)

  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, applygainfilter, 0)
  outfilter.process(input.shape[1])

  return output

def fractional_filter(input, ratio=4, threshold=1, color=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  input2 = input**2
  in2filter = DoubleInPointerFilter(input2, False)
  in2filter.set_input_sampling_rate(sample_rate)
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)
  
  gainfilter = DoubleGainFractionalCompressorFilter(1)
  gainfilter.set_input_sampling_rate(sample_rate)
  gainfilter.set_input_port(0, in2filter, 0)
  gainfilter.set_threshold(threshold)
  gainfilter.set_ratio(ratio)
  gainfilter.set_color(color)
  
  applygainfilter = DoubleApplyGainFilter(1)
  applygainfilter.set_input_sampling_rate(sample_rate)
  applygainfilter.set_input_port(0, gainfilter, 0)
  applygainfilter.set_input_port(1, infilter, 0)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, applygainfilter, 0)
  outfilter.process(input.shape[1])
  
  return output

if __name__ == "__main__":
  import numpy as np
  size = 10000

  x = np.arange(size, dtype=np.float64).reshape(1, -1) / 100

  np.savetxt("input.txt", x)
  out_3_1_1 = filter(x, 3, 1, 1)
  out_4_1_1 = filter(x, 4, 1, 1)
  
  max_out_3_1___5 = fractional_filter(x, 3, 1, -.5)
  max_out_4_1__5 = fractional_filter(x, 4, 1, .5)
  max_out_4_1_0 = fractional_filter(x, 4, 1, 0)
  max_out_4_1___5 = fractional_filter(x, 4, 1, -.5)

  plt.figure()
  plt.loglog(x[0], out_4_1_1[0], label="ratio(4), threshold(1), softness(1)")
  plt.loglog(x[0], out_3_1_1[0], label="ratio(3), threshold(1), softness(1)")
  
  plt.loglog(x[0], max_out_4_1__5[0], label="fractional, ratio(4), threshold(1), color(.5)")
  plt.loglog(x[0], max_out_4_1_0[0], label="fractional, ratio(4), threshold(1), color(0)")
  plt.loglog(x[0], max_out_4_1___5[0], label="fractional, ratio(4), threshold(1), color(-.5)")
  plt.loglog(x[0], max_out_3_1___5[0], label="fractional, ratio(3), threshold(1), color(-.5)")
  
  plt.title("Compressor gain")
  plt.legend(loc=4)
  plt.grid()
  plt.show()
