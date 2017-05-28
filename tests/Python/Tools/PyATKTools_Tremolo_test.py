#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleSinusGeneratorFilter, DoubleApplyGainFilter

import matplotlib.pyplot as plt

sample_rate = 96000
size = 9600

def filter(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate

  sinusfilter = DoubleSinusGeneratorFilter()
  sinusfilter.input_sampling_rate = sample_rate
  sinusfilter.offset = 0.5
  sinusfilter.volume = 0.5
  sinusfilter.frequency = 10
  
  gainfilter = DoubleApplyGainFilter(1)
  gainfilter.input_sampling_rate = sample_rate
  gainfilter.set_input_port(0, infilter, 0)
  gainfilter.set_input_port(1, sinusfilter, 1)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, gainfilter, 0)
  outfilter.process(input.shape[0])

  return output

def tremolo_test():
  from numpy.testing import assert_almost_equal
  import numpy as np

  x = np.arange(size, dtype=np.float64) / sample_rate
  d = np.sin(x * 2 * np.pi * 100)
  
  out = filter(d)
  assert_almost_equal(out, d * (.5 + .5 * np.sin(2 * np.pi * 10 * x)), decimal = 2)

if __name__ == "__main__":
  import numpy as np
  
  x = np.arange(size, dtype=np.float64) / sample_rate
  d = np.sin(x * 2 * np.pi * 100)

  out = filter(d)
  plt.plot(x, d, label="Input")
  plt.plot(x, out, label="Output")
  plt.legend()
  plt.show()
  
