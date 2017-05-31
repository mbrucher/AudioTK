#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Dynamic import DoubleGainCompressorFilter, DoubleGainSwellFilter
from ATK.Tools import DoubleApplyGainFilter

import matplotlib.pyplot as plt

sample_rate = 96000

def filter(input, ratio=4, threshold=1, softness=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  input2 = input**2
  in2filter = DoubleInPointerFilter(input2, False)
  in2filter.input_sampling_rate = sample_rate

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate

  gainfilter = DoubleGainCompressorFilter(1)
  gainfilter.input_sampling_rate = sample_rate
  gainfilter.set_input_port(0, in2filter, 0)
  gainfilter.threshold = threshold
  gainfilter.ratio = ratio
  gainfilter.softness = softness

  applygainfilter = DoubleApplyGainFilter(1)
  applygainfilter.input_sampling_rate = sample_rate
  applygainfilter.set_input_port(0, gainfilter, 0)
  applygainfilter.set_input_port(1, infilter, 0)

  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, applygainfilter, 0)
  outfilter.process(input.shape[1])

  return output

def colored_filter(input, ratio=4, threshold=1, softness=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  input2 = input**2
  in2filter = DoubleInPointerFilter(input2, False)
  in2filter.input_sampling_rate = sample_rate
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate
  
  gainfilter = DoubleGainSwellFilter(1)
  gainfilter.input_sampling_rate = sample_rate
  gainfilter.set_input_port(0, in2filter, 0)
  gainfilter.threshold = threshold
  gainfilter.ratio = ratio
  gainfilter.softness = softness

  applygainfilter = DoubleApplyGainFilter(1)
  applygainfilter.input_sampling_rate = sample_rate
  applygainfilter.set_input_port(0, gainfilter, 0)
  applygainfilter.set_input_port(1, infilter, 0)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, applygainfilter, 0)
  outfilter.process(input.shape[1])
  
  return output

def swell_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_swellgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_swellgain.dat", dtype=np.float64).reshape(1, -1)
  out = filter(x, 1, 1, 1)
  assert_almost_equal(out, ref)

def swell_1_1_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_swellgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_swellgain_1_1.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 1, 1, 1)
  assert_almost_equal(out, ref)

def swell_2_1_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_swellgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_swellgain_2_1.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 2, 1, 1)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  size = 1000

  x = np.arange(10, size, dtype=np.float64).reshape(1, -1) / 100
  x.tofile("input_swellgain.dat")

  out_1_1_1 = filter(x, 1, 1, 1)
  out_1_1_1.tofile("output_swellgain.dat")
  
  max_out_1_1 = colored_filter(x, 1, 1, 1)
  max_out_1_1.tofile("output_swellgain_1_1.dat")
  max_out_2_1 = colored_filter(x, 2, 1, 1)
  max_out_2_1.tofile("output_swellgain_2_1.dat")

  plt.figure()
  plt.loglog(x[0], out_1_1_1[0], label="compressor, ratio(1), threshold(1), softness(1)")
  
  plt.loglog(x[0], max_out_1_1[0], label="swell, ratio(1), threshold(1), softness(1)")
  plt.loglog(x[0], max_out_2_1[0], label="swell, ratio(2), threshold(1), softness(1)")

  plt.title("Swell gain")
  plt.legend(loc=4)
  plt.grid()
  plt.show()
