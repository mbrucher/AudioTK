#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Dynamic import DoubleGainExpanderFilter, DoubleGainMaxExpanderFilter
from ATK.Tools import DoubleApplyGainFilter

sample_rate = 96000

def filter(input, ratio=4, threshold=1, softness=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  input2 = input**2
  in2filter = DoubleInPointerFilter(input2, False)
  in2filter.input_sampling_rate = sample_rate

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate

  gainfilter = DoubleGainExpanderFilter(1)
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

def max_filter(input, ratio=4, threshold=1, softness=1, max_reduction=0.1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  input2 = input**2
  in2filter = DoubleInPointerFilter(input2, False)
  in2filter.input_sampling_rate = sample_rate

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate

  gainfilter = DoubleGainMaxExpanderFilter(1)
  gainfilter.input_sampling_rate = sample_rate
  gainfilter.set_input_port(0, in2filter, 0)
  gainfilter.threshold = threshold
  gainfilter.ratio = ratio
  gainfilter.softness = softness
  gainfilter.max_reduction = max_reduction

  applygainfilter = DoubleApplyGainFilter(1)
  applygainfilter.input_sampling_rate = sample_rate
  applygainfilter.set_input_port(0, gainfilter, 0)
  applygainfilter.set_input_port(1, infilter, 0)

  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, applygainfilter, 0)
  outfilter.process(input.shape[1])

  return output

def expander_out_2_1_1_test():
  import numpy as np
  from numpy.testing import assert_almost_equal

  import os
  dirname = os.path.dirname(__file__)

  x = np.fromfile(dirname + os.sep + "input_expgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_expgain_2_1_1.dat", dtype=np.float64).reshape(1, -1)
  out = filter(x, 2, 1, 1)
  assert_almost_equal(out, ref)

def expander_out_4_1_1_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_expgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_expgain_4_1_1.dat", dtype=np.float64).reshape(1, -1)
  out = filter(x, 4, 1, 1)
  assert_almost_equal(out, ref)

def expander_out_8_1_1_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_expgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_expgain_8_1_1.dat", dtype=np.float64).reshape(1, -1)
  out = filter(x, 8, 1, 1)
  assert_almost_equal(out, ref)

def expander_out_10_01_001_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_expgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_expgain_10_01_001.dat", dtype=np.float64).reshape(1, -1)
  out = filter(x, 10, .1, 0.01)
  assert_almost_equal(out, ref)

def expander_out_10_01_10_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_expgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_expgain_10_01_10.dat", dtype=np.float64).reshape(1, -1)
  out = filter(x, 10, .1, 10)
  assert_almost_equal(out, ref)

def expander_out_10_01_1_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_expgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_expgain_10_01_1.dat", dtype=np.float64).reshape(1, -1)
  out = filter(x, 10, .1, 1)
  assert_almost_equal(out, ref)

def maxexpander_out_4_1_1__001_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_expgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_maxexpgain_4_1_1__001.dat", dtype=np.float64).reshape(1, -1)
  out = max_filter(x, 4, 1, 1, .001)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  import matplotlib.pyplot as plt

  size = 1000

  x = np.arange(size, dtype=np.float64).reshape(1, -1) / 100
  x.tofile("input_expgain.dat")
  out_2_1_1 = filter(x, 2, 1, 1)
  out_2_1_1.tofile("output_expgain_2_1_1.dat")
  out_4_1_1 = filter(x, 4, 1, 1)
  out_4_1_1.tofile("output_expgain_4_1_1.dat")
  out_8_1_1 = filter(x, 8, 1, 1)
  out_8_1_1.tofile("output_expgain_8_1_1.dat")
  out_10_01_001 = filter(x, 10, .1, 0.01)
  out_10_01_001.tofile("output_expgain_10_01_001.dat")
  out_10_01_1 = filter(x, 10, .1, 1)
  out_10_01_1.tofile("output_expgain_10_01_1.dat")
  out_10_01_10 = filter(x, 10, .1, 10)
  out_10_01_10.tofile("output_expgain_10_01_10.dat")

  max_out_4_1_1 = max_filter(x, 4, 1, 1, .001)
  max_out_4_1_1.tofile("output_maxexpgain_4_1_1__001.dat")

  plt.figure()
  plt.loglog(x[0], out_2_1_1[0], label="ratio(2), threshold(1), softness(1)")
  plt.loglog(x[0], out_4_1_1[0], label="ratio(4), threshold(1), softness(1)")
  plt.loglog(x[0], out_8_1_1[0], label="ratio(8), threshold(1), softness(1)")
  plt.loglog(x[0], out_10_01_001[0], label="ratio(10), threshold(0.1), softness(1e-2)")
  plt.loglog(x[0], out_10_01_1[0], label="ratio(10), threshold(0.1), softness(1)")
  plt.loglog(x[0], out_10_01_10[0], label="ratio(10), threshold(0.1), softness(10)")

  plt.loglog(x[0], max_out_4_1_1[0], label="ratio(4), threshold(1), softness(1), max_reduction(1e-3)")
  
  plt.title("Expander gain")
  plt.legend(loc=4)
  plt.grid()
  plt.show()
