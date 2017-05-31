#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Dynamic import DoubleGainCompressorFilter, DoubleGainColoredCompressorFilter
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

def colored_filter(input, ratio=4, threshold=1, softness=1, quality=1, color=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  input2 = input**2
  in2filter = DoubleInPointerFilter(input2, False)
  in2filter.input_sampling_rate = sample_rate
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate
  
  gainfilter = DoubleGainColoredCompressorFilter(1)
  gainfilter.input_sampling_rate = sample_rate
  gainfilter.set_input_port(0, in2filter, 0)
  gainfilter.threshold = threshold
  gainfilter.ratio = ratio
  gainfilter.color = color
  gainfilter.softness = softness
  gainfilter.quality = quality

  applygainfilter = DoubleApplyGainFilter(1)
  applygainfilter.input_sampling_rate = sample_rate
  applygainfilter.set_input_port(0, gainfilter, 0)
  applygainfilter.set_input_port(1, infilter, 0)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, applygainfilter, 0)
  outfilter.process(input.shape[1])
  
  return output

def comp_4_1_1_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorcompgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorcompgain_4_1_1.dat", dtype=np.float64).reshape(1, -1)
  out = filter(x, 4, 1, 1)
  assert_almost_equal(out, ref)

def comp_4_1_1__5_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorcompgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorcompgain_4_1_1__5.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 4, 1, 1, 1, .5)
  assert_almost_equal(out, ref)

def comp_4_1__1__5_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorcompgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorcompgain_4_1__1__5.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 4, 1, 1, .1, .5)
  assert_almost_equal(out, ref)

def comp_4_1_1_0_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorcompgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorcompgain_4_1_1_0.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 4, 1, 1, 1, 0)
  assert_almost_equal(out, ref)

def comp_4_1_1___5_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorcompgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorcompgain_4_1_1___5.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 4, 1, 1, 1, -.5)
  assert_almost_equal(out, ref)

def comp_4_1__1___5_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorcompgain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorcompgain_4_1__1___5.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 4, 1, 1, .1, -.5)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  size = 1000

  x = np.arange(10, size, dtype=np.float64).reshape(1, -1) / 100
  x.tofile("input_colorcompgain.dat")

  out_4_1_1 = filter(x, 4, 1, 1)
  out_4_1_1.tofile("output_colorcompgain_4_1_1.dat")
  
  max_out_4_1_1__5 = colored_filter(x, 4, 1, 1, 1, .5)
  max_out_4_1_1__5.tofile("output_colorcompgain_4_1_1__5.dat")
  max_out_4_1__1__5 = colored_filter(x, 4, 1, 1, .1, .5)
  max_out_4_1__1__5.tofile("output_colorcompgain_4_1__1__5.dat")
  max_out_4_1_1_0 = colored_filter(x, 4, 1, 1, 1, 0)
  max_out_4_1_1_0.tofile("output_colorcompgain_4_1_1_0.dat")
  max_out_4_1_1___5 = colored_filter(x, 4, 1, 1, 1, -.5)
  max_out_4_1_1___5.tofile("output_colorcompgain_4_1_1___5.dat")
  max_out_4_1__1___5 = colored_filter(x, 4, 1, 1, .1, -.5)
  max_out_4_1__1___5.tofile("output_colorcompgain_4_1__1___5.dat")

  plt.figure()
  plt.loglog(x[0], out_4_1_1[0], label="ratio(4), threshold(1), softness(1)")
  
  plt.loglog(x[0], max_out_4_1_1__5[0], label="colored, ratio(4), threshold(1), softness(1), quality(1), color(.5)")
  plt.loglog(x[0], max_out_4_1__1__5[0], label="colored, ratio(4), threshold(1), softness(1), quality(.1), color(.5)")
  plt.loglog(x[0], max_out_4_1_1_0[0], label="colored, ratio(4), threshold(1), softness(1), quality(1), color(0)")
  plt.loglog(x[0], max_out_4_1_1___5[0], label="colored, ratio(4), threshold(1), softness(1), quality(1), color(-.5)")
  plt.loglog(x[0], max_out_4_1__1___5[0], label="colored, ratio(4), threshold(1), softness(1), quality(.1), color(-.5)")
  
  plt.title("Colored compressor gain")

  plt.legend(loc=4)
  plt.grid()
  plt.show()
