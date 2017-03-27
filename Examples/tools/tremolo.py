#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleCachedSinusGeneratorFilter, DoubleApplyGainFilter

import matplotlib.pyplot as plt

sample_rate = 96000

def filter(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)

  sinusfilter = DoubleCachedSinusGeneratorFilter(20, 5)
  sinusfilter.set_input_sampling_rate(sample_rate)
  sinusfilter.set_offset(0.5)
  sinusfilter.set_volume(0.5)
  
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
  size = 960000
  
  x = np.arange(size, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(x * 2 * np.pi * 1000)

  np.savetxt("input.txt", d)
  out = filter(d)
  np.savetxt("output.txt", d)
