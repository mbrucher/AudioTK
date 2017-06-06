#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Delay import DoubleUniversalVariableDelayLineFilter
from ATK.EQ import DoubleSecondOrderLowPassFilter

sample_rate = 96000

def filter(noise, input, blend=0, feedback=0, feedforward=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate

  noisefilter = DoubleInPointerFilter(noise, False)
  noisefilter.input_sampling_rate = sample_rate

  lownoisefilter = DoubleSecondOrderLowPassFilter()
  lownoisefilter.input_sampling_rate = sample_rate
  lownoisefilter.cut_frequency = 5
  lownoisefilter.set_input_port(0, noisefilter, 0)
  
  delayfilter = DoubleUniversalVariableDelayLineFilter(5000)
  delayfilter.input_sampling_rate = sample_rate
  delayfilter.set_input_port(0, infilter, 0)
  delayfilter.set_input_port(1, lownoisefilter, 0)
  delayfilter.blend = blend
  delayfilter.feedback = feedback
  delayfilter.feedforward = feedforward
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, delayfilter, 0)
  outfilter.process(input.shape[1])

  return output

def chorus_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_chorus.dat", dtype=np.float64).reshape(1, -1)
  noise = np.fromfile(dirname + os.sep + "noise_chorus.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_chorus.dat", dtype=np.float64).reshape(1, -1)
  out = filter(noise, x, feedforward=1, blend=0.7, feedback=-0.7)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  import matplotlib.pyplot as plt

  samples = 2000000
  freq_max = 20000
  
  import sys, os
  sys.path.append(os.path.dirname(os.path.realpath(__file__))+"/..")
  from display.compare_spec import plot_me

  t = np.arange(samples, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(np.pi * (sample_rate * freq_max / samples * (t + .1)) * t)
  d[:,:1000].tofile("input_chorus.dat")
  noise = 20e-3 * sample_rate + 5e-3 * sample_rate * np.random.randn(1, samples)
  noise[:,:1000].tofile("noise_chorus.dat")
  out = filter(noise, d, feedforward=1, blend=0.7, feedback=-0.7)
  out[:,:1000].tofile("output_chorus.dat")

  plt.figure()
  plot_me((d[0], out[0]), sample_rate)
  plt.gcf().suptitle("Delay")
  plt.legend()
  plt.show()
