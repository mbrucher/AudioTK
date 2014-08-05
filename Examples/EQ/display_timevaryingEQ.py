#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.EQ import DoubleTimeVaryingBandPassCoefficientsIIRFilter
from ATK.Tools import DoubleCachedSinusGeneratorFilter

import matplotlib.pyplot as plt

sample_rate = 96000

import sys, os
sys.path.append(os.path.dirname(os.path.realpath(__file__))+"/..")
from display.compare_spec import plot_me

def filter(input, blend=0, feedback=0, feedforward=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)

  noisefilter = DoubleCachedSinusGeneratorFilter(1, 2)
  noisefilter.set_input_sampling_rate(sample_rate)
  noisefilter.set_offset(10000)
  noisefilter.set_volume(2000)
  
  lowfilter = DoubleTimeVaryingBandPassCoefficientsIIRFilter()
  lowfilter.set_input_sampling_rate(sample_rate)
  lowfilter.set_Q(1)
  lowfilter.set_min_frequency(8000)
  lowfilter.set_max_frequency(12000)
  lowfilter.set_number_of_steps(10001)
  lowfilter.set_input_port(0, infilter, 0)
  lowfilter.set_input_port(1, noisefilter, 0)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, lowfilter, 0)
  outfilter.process(input.shape[1])

  return output

if __name__ == "__main__":
  import numpy as np
  samples = 2000000
  freq_max = 20000

  t = np.arange(samples, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.random.randn(*t.shape) #np.sin(np.pi * (sample_rate * freq_max / samples * (t + .1)) * t)

  np.savetxt("input.txt", d)
  out = filter(d, feedforward=1, blend=0.7, feedback=-0.7)
  np.savetxt("output.txt", out)
  plt.figure()
  plot_me((d[0], out[0]), sample_rate)
  plt.clim(-55,-45)
  a = plt.subplot(2, 1, 1)
  plt.clim(-55,-45)
  plt.gcf().suptitle("Amplitude for a time-varying filter")
  plt.legend()
  plt.show()
