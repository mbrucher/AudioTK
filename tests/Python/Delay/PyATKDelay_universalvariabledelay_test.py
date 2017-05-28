#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Delay import DoubleUniversalVariableDelayLineFilter
from ATK.Tools import DoubleSinusGeneratorFilter

sample_rate = 96000

def filter(input, blend=0, feedback=0, feedforward=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.output_sampling_rate = sample_rate

  generator = DoubleSinusGeneratorFilter()
  generator.output_sampling_rate = sample_rate
  generator.frequency = 1
  generator.volume = 1e-3*sample_rate
  generator.offset = 1.5e-3*sample_rate

  delayfilter = DoubleUniversalVariableDelayLineFilter(5000)
  delayfilter.input_sampling_rate = sample_rate
  delayfilter.set_input_port(0, infilter, 0)
  delayfilter.set_input_port(1, generator, 0)
  delayfilter.blend = blend
  delayfilter.feedback = feedback
  delayfilter.feedforward = feedforward
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, delayfilter, 0)
  outfilter.process(input.shape[1])

  return output

def universalvariabledelay_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  d = np.fromfile(dirname + os.sep + "input_VUD.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_VUD.dat", dtype=np.float64).reshape(1, -1)
  out = filter(d, feedforward=-1, blend=1, feedback=-.5)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  samples = 2000000
  freq_max = 20000

  import matplotlib.pyplot as plt
  import sys, os
  sys.path.append(os.path.dirname(os.path.realpath(__file__))+"/..")
  from display.compare_spec import plot_me

  t = np.arange(samples, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(np.pi * (sample_rate * freq_max / samples * (t + .1)) * t)

  d[:,:1000].tofile("input_VUD.dat")
  out = filter(d, feedforward=-1, blend=1, feedback=-.5)
  out[:,:1000].tofile("output_VUD.dat")
  plt.figure()
  plot_me((d[0], out[0]), sample_rate)
  plt.gcf().suptitle("Delay")
  plt.legend()
  plt.show()
