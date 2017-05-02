#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleSinusGeneratorFilter, DoubleApplyGainFilter

import matplotlib.pyplot as plt

sample_rate = 96000

def filter(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)

  sinusfilter = DoubleSinusGeneratorFilter()
  sinusfilter.set_input_sampling_rate(sample_rate)
  sinusfilter.set_offset(0.5)
  sinusfilter.set_volume(0.5)
  sinusfilter.set_frequency(10)
  
  gainfilter = DoubleApplyGainFilter(1)
  gainfilter.set_input_sampling_rate(sample_rate)
  gainfilter.set_input_port(0, infilter, 0)
  gainfilter.set_input_port(1, sinusfilter, 0)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, gainfilter, 0)
  outfilter.process(input.shape[1])

  return output

if __name__ == "__main__":
  import numpy as np
  size = 9600
  
  x = np.arange(size, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(x * 2 * np.pi * 100)

  out = filter(d)
  plt.plot(x[0], d[0], label="Input")
  plt.plot(x[0], out[0], label="Output")
  plt.legend()
  plt.show()
  