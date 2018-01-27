#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Adaptive import DoubleRLSFilter

from nose.tools import raises

def filter(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  rls = DoubleRLSFilter(10)
  rls.input_sampling_rate = 48000
  rls.memory = 0.99
  rls.learning = True
  rls.set_input_port(0, infilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, rls, 0)
  outfilter.process(1000)
  rls.learning = False
  outfilter.process(input.shape[1] - 1000)

  return output

def RLS_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  d = np.fromfile(dirname + os.sep + "input_rls.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_rls.dat", dtype=np.float64).reshape(1, -1)
  out = filter(d)
  assert_almost_equal(out, ref)

@raises(ValueError)
def RLS_bad_w_dim_test():
  import numpy as np

  rls = DoubleRLSFilter(100)
  rls.w = np.array(())

@raises(ValueError)
def RLS_bad_w_size_test():
  import numpy as np

  rls = DoubleRLSFilter(100)
  rls.w = np.ones((10,))

@raises(ValueError)
def RLS_bad_P_dim_test():
  import numpy as np

  rls = DoubleRLSFilter(100)
  rls.P = np.array((100,))

@raises(ValueError)
def RLS_bad_P_size_test():
  import numpy as np

  rls = DoubleRLSFilter(100)
  rls.P = np.ones((10,10))

if __name__ == "__main__":
  import numpy as np
  size = 5000
  
  x = np.arange(size).reshape(1, -1) / 48000.
  d = np.sin(x * 2 * np.pi * 100)
  d.tofile("input_rls.dat")
  out = filter(d)
  out.tofile("output_rls.dat")

  import matplotlib.pyplot as plt
  plt.plot(x[0], d[0], label="input")
  plt.plot(x[0], out[0], label="output")
  plt.legend()
  plt.show()
