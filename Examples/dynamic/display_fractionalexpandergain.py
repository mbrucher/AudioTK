#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Dynamic import DoubleGainExpanderFilter
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

  gainfilter = DoubleGainExpanderFilter(1)
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

def fractional_filter(input, ratio=4, threshold=1, softness=1):
  input_thres = input/threshold
  input_tr = input_thres**(ratio-1)
  gain = (input_tr + input_tr * input_tr) / (1 + softness * input_tr + input_tr * input_tr)
  
  return input * gain

if __name__ == "__main__":
  import numpy as np
  size = 1000

  x = np.arange(size, dtype=np.float64).reshape(1, -1) / 100

  np.savetxt("input.txt", x)
  out_2_1_1 = filter(x, 2, 1, 1)
  out_4_1_1 = filter(x, 4, 1, 1)
  out_8_1_1 = filter(x, 8, 1, 1)
  out_10_01_001 = filter(x, 10, .1, 0.01)
  out_10_01_1 = filter(x, 10, .1, 1)
  out_10_01_10 = filter(x, 10, .1, 10)

  max_out_4_1_1 = fractional_filter(x, 4, 1, 1)
  max_out_4_1_2 = fractional_filter(x, 4, 1, 2)
  max_out_4_1_0 = fractional_filter(x, 4, 1, 0)
  max_out_4_1___5 = fractional_filter(x, 4, 1, -.5)

  plt.figure()
  #plt.loglog(x[0], out_2_1_1[0], label="ratio(2), threshold(1), softness(1)")
  plt.loglog(x[0], out_4_1_1[0], label="ratio(4), threshold(1), softness(1)")
  #plt.loglog(x[0], out_8_1_1[0], label="ratio(8), threshold(1), softness(1)")
  #plt.loglog(x[0], out_10_01_001[0], label="ratio(10), threshold(0.1), softness(1e-2)")
  #plt.loglog(x[0], out_10_01_1[0], label="ratio(10), threshold(0.1), softness(1)")
  #plt.loglog(x[0], out_10_01_10[0], label="ratio(10), threshold(0.1), softness(10)")

  plt.loglog(x[0], max_out_4_1_1[0], label="fractional, ratio(4), threshold(1), softness(1)")
  plt.loglog(x[0], max_out_4_1_2[0], label="fractional, ratio(4), threshold(1), softness(2)")
  plt.loglog(x[0], max_out_4_1_0[0], label="fractional, ratio(4), threshold(1), softness(0)")
  plt.loglog(x[0], max_out_4_1___5[0], label="fractional, ratio(4), threshold(1), softness(-.5)")
  
  plt.title("Expander gain")
  plt.legend(loc=4)
  plt.grid()
  plt.show()
