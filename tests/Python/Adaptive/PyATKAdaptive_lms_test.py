#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Adaptive import DoubleLMSFilter

def filter(input, reference):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  reffilter = DoubleInPointerFilter(reference, False)
  reffilter.input_sampling_rate = 48000
  rls = DoubleLMSFilter(10)
  rls.input_sampling_rate = 48000
  rls.memory = 0.99
  rls.set_input_port(0, infilter, 0)
  rls.set_input_port(1, reffilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, rls, 0)
  outfilter.process(input.shape[1])

  return output

def LMS_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)

  d = np.fromfile(dirname + os.sep + "input_lms.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_lms.dat", dtype=np.float64).reshape(1, -1)
  out = filter(d, d)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  size = 1200
  
  x = np.arange(size).reshape(1, -1) / 48000.
  d = np.sin(x * 2 * np.pi * 100, dtype=np.float64)
  d.tofile("input_lms.dat")
  out = filter(d, d)
  out.tofile("output_lms.dat")

  import matplotlib.pyplot as plt
  plt.plot(x[0], d[0], label="input")
  plt.plot(x[0], out[0], label="output")
  plt.legend()
  plt.show()
