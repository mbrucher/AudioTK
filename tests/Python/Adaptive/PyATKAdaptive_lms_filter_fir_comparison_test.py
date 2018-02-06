#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Adaptive import DoubleLMSFilter
from ATK.EQ import DoubleCustomFIRFilter

import numpy as np

fs = 48000

class Filter:
  def __init__(self):
    self.lms = DoubleLMSFilter(40)
    self.lms.input_sampling_rate = fs
    self.lms.memory = 0.999
    self.lms.mu = 0.015
    self.lms.w = np.ones((40,))
    self.lms.learning = False

  def process(self, input, ref):
    import numpy as np
    output = np.zeros(input.shape, dtype=np.float64)

    infilter = DoubleInPointerFilter(input, False)
    infilter.input_sampling_rate = fs
    reffilter = DoubleInPointerFilter(ref, False)
    reffilter.input_sampling_rate = fs
    self.lms.set_input_port(0, infilter, 0)
    self.lms.set_input_port(1, reffilter, 0)
    outfilter = DoubleOutPointerFilter(output, False)
    outfilter.input_sampling_rate = fs
    outfilter.set_input_port(0, self.lms, 0)
    outfilter.process(input.shape[1])

    return output

class FIRFilter:
  def __init__(self):
    self.filter = DoubleCustomFIRFilter()
    self.filter.input_sampling_rate = fs
    self.filter.coefficients_in = np.ones((40,))

  def process(self, input):
    import numpy as np
    output = np.zeros(input.shape, dtype=np.float64)

    infilter = DoubleInPointerFilter(input, False)
    infilter.input_sampling_rate = fs
    self.filter.set_input_port(0, infilter, 0)
    outfilter = DoubleOutPointerFilter(output, False)
    outfilter.input_sampling_rate = fs
    outfilter.set_input_port(0, self.filter, 0)
    outfilter.process(input.shape[1])

    return output

def LMS_IIR_test():
  import numpy as np
  from numpy.testing import assert_almost_equal

  filter = Filter()
  firFilter = FIRFilter()

  x = np.sin(np.arange(1000) * np.pi * 2 / 48000. * 100)[None, :]
  output1 = filter.process(x, x)
  output2 = firFilter.process(x)

  assert_almost_equal(output1, output2)
  assert_almost_equal(filter.lms.w, np.ones((40,)))

if __name__ == "__main__":
  size = 48000
  window = size//10

  filter = Filter()
  firFilter = FIRFilter()

  t = np.arange(1000) / 4800.
  x = np.sin(t * np.pi * 200)[None, :]
  output1 = filter.process(x, x)
  output2 = firFilter.process(x)

  plt.figure()
  plt.plot(t, output1[0], label="LMS filter")
  plt.plot(t, output2[0], label="FIR filter")
  plt.legend()
  plt.grid(True)
  plt.title("LMS vs FIR")
  
  plt.show()
