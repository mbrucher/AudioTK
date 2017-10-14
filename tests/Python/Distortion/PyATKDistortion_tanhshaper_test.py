#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Distortion import DoubleTanhShaperFilter, DoubleHalfTanhShaperFilter

sample_rate = 48000

def filter_asym(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  inputfilter = DoubleInPointerFilter(input, False)
  inputfilter.input_sampling_rate = sample_rate
  shaperfilter = DoubleHalfTanhShaperFilter()
  shaperfilter.input_sampling_rate = sample_rate
  shaperfilter.coefficient = 2
  shaperfilter.set_input_port(0, inputfilter, 0)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, shaperfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_sym(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  inputfilter = DoubleInPointerFilter(input, False)
  inputfilter.input_sampling_rate = sample_rate
  shaperfilter = DoubleTanhShaperFilter()
  shaperfilter.input_sampling_rate = sample_rate
  shaperfilter.coefficient = 2
  shaperfilter.set_input_port(0, inputfilter, 0)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, shaperfilter, 0)
  outfilter.process(input.shape[1])
  return output

def tanh_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_tanh.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_tanh.dat", dtype=np.float64).reshape(1, -1)
  out = filter_sym(x)
  assert_almost_equal(out, ref)

def half_tanh_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_tanh.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_halftanh.dat", dtype=np.float64).reshape(1, -1)
  out = filter_asym(x)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  size = 1200
  
  x = np.arange(size).reshape(1, -1) / 48000.
  d = np.sin(x * 2 * np.pi * 100)
  d.tofile("input_tanh.dat")
  out = filter_sym(d)
  out.tofile("output_tanh.dat")
  out2 = filter_asym(d)
  out2.tofile("output_halftanh.dat")

  import matplotlib.pyplot as plt
  plt.plot(x[0], d[0], label="input")
  plt.plot(x[0], out[0], label="tanh shaper")
  plt.plot(x[0], out2[0], label="half tanh shaper")
  plt.legend()
  plt.show()
