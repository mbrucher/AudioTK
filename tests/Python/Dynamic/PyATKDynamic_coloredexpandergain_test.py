#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Dynamic import DoubleGainExpanderFilter, DoubleGainColoredExpanderFilter, DoubleGainMaxColoredExpanderFilter
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

def colored_filter(input, ratio=4, threshold=1, softness=1, quality=1, color=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  input2 = input**2
  in2filter = DoubleInPointerFilter(input2, False)
  in2filter.input_sampling_rate = sample_rate
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate
  
  gainfilter = DoubleGainColoredExpanderFilter(1)
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

def max_colored_filter(input, ratio=4, threshold=1, softness=1, quality=1, color=1, max_reduction=-10):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  input2 = input**2
  in2filter = DoubleInPointerFilter(input2, False)
  in2filter.input_sampling_rate = sample_rate
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate
  
  gainfilter = DoubleGainMaxColoredExpanderFilter(1)
  gainfilter.input_sampling_rate = sample_rate
  gainfilter.set_input_port(0, in2filter, 0)
  gainfilter.threshold = threshold
  gainfilter.ratio = ratio
  gainfilter.color = color
  gainfilter.softness = softness
  gainfilter.quality = quality
  gainfilter.max_reduction = 10 ** (max_reduction / 20.)
  
  applygainfilter = DoubleApplyGainFilter(1)
  applygainfilter.input_sampling_rate = sample_rate
  applygainfilter.set_input_port(0, gainfilter, 0)
  applygainfilter.set_input_port(1, infilter, 0)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, applygainfilter, 0)
  outfilter.process(input.shape[1])
  
  return output

def expander_4_1_1_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorexpandergain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorexpandergain_4_1_1.dat", dtype=np.float64).reshape(1, -1)
  out = filter(x, 4, 1, 1)
  assert_almost_equal(out, ref)

def expander_4_1_1__5_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorexpandergain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorexpandergain_4_1_1__5.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 4, 1, 1, 1, .5)
  assert_almost_equal(out, ref)

def expander_4_1__1__5_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorexpandergain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorexpandergain_4_1__1__5.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 4, 1, 1, .1, .5)
  assert_almost_equal(out, ref)

def expander_4_1_1_0_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorexpandergain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorexpandergain_4_1_1_0.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 4, 1, 1, 1, 0)
  assert_almost_equal(out, ref)

def expander_4_1_1___5_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorexpandergain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorexpandergain_4_1_1___5.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 4, 1, 1, 1, -.5)
  assert_almost_equal(out, ref)

def expander_4_1__1___5_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorexpandergain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorexpandergain_4_1__1___5.dat", dtype=np.float64).reshape(1, -1)
  out = colored_filter(x, 4, 1, 1, .1, -.5)
  assert_almost_equal(out, ref)

def expander_max_4_1_1_0_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_colorexpandergain.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_colorexpandergain_max_4_1_1_0.dat", dtype=np.float64).reshape(1, -1)
  out = max_colored_filter(x, 4, 1, 1, 1, 0, -10)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  import matplotlib.pyplot as plt

  size = 1000

  x = np.arange(10, size, dtype=np.float64).reshape(1, -1) / 100
  x.tofile("input_colorexpandergain.dat")

  out_4_1_1 = filter(x, 4, 1, 1)
  out_4_1_1.tofile("output_colorexpandergain_4_1_1.dat")
  
  col_out_4_1_1__5 = colored_filter(x, 4, 1, 1, 1, .5)
  col_out_4_1_1__5.tofile("output_colorexpandergain_4_1_1__5.dat")
  col_out_4_1__1__5 = colored_filter(x, 4, 1, 1, .1, .5)
  col_out_4_1__1__5.tofile("output_colorexpandergain_4_1__1__5.dat")
  col_out_4_1_1_0 = colored_filter(x, 4, 1, 1, 1, 0)
  col_out_4_1_1_0.tofile("output_colorexpandergain_4_1_1_0.dat")
  col_out_4_1_1___5 = colored_filter(x, 4, 1, 1, 1, -.5)
  col_out_4_1_1___5.tofile("output_colorexpandergain_4_1_1___5.dat")
  col_out_4_1__1___5 = colored_filter(x, 4, 1, 1, .1, -.5)
  col_out_4_1__1___5.tofile("output_colorexpandergain_4_1__1___5.dat")

  max_out_4_1_1_0 = max_colored_filter(x, 4, 1, 1, 1, 0, -10)
  max_out_4_1_1_0.tofile("output_colorexpandergain_max_4_1_1_0.dat")

  plt.figure()
  plt.loglog(x[0], out_4_1_1[0], label="ratio(4), threshold(1), softness(1)")
  
  plt.loglog(x[0], col_out_4_1_1__5[0], label="colored, ratio(4), threshold(1), softness(1), quality(1), color(.5)")
  plt.loglog(x[0], col_out_4_1__1__5[0], label="colored, ratio(4), threshold(1), softness(1), quality(.1), color(.5)")
  plt.loglog(x[0], col_out_4_1_1_0[0], label="colored, ratio(4), threshold(1), softness(1), quality(1), color(0)")
  plt.loglog(x[0], col_out_4_1_1___5[0], label="colored, ratio(4), threshold(1), softness(1), quality(1), color(-.5)")
  plt.loglog(x[0], col_out_4_1__1___5[0], label="colored, ratio(4), threshold(1), softness(1), quality(.1), color(-.5)")

  plt.loglog(x[0], max_out_4_1_1_0[0], label="max colored, ratio(4), threshold(1), softness(1), quality(1), color(0), max recuc(-10dB)")
  
  plt.title("Expander gain")
  plt.legend(loc=4)
  plt.grid()
  plt.show()
