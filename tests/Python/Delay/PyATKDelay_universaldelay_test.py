#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Delay import DoubleUniversalFixedDelayLineFilter

sample_rate = 96000

def filter(input, blend=0, feedback=0, feedforward=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate

  delayfilter = DoubleUniversalFixedDelayLineFilter(5000)
  delayfilter.input_sampling_rate = sample_rate
  delayfilter.set_input_port(0, infilter, 0)
  delayfilter.delay = 4800 #50ms
  delayfilter.blend = blend
  delayfilter.feedback = feedback
  delayfilter.feedforward = feedforward
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, delayfilter, 0)
  outfilter.process(input.shape[1])

  return output

def universaldelay_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  d = np.fromfile(dirname + os.sep + "input_UD.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_UD.dat", dtype=np.float64).reshape(1, -1)
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

  d[:,:1000].tofile("input_UD.dat")
  out = filter(d, feedforward=-1, blend=1, feedback=-.5)
  out[:,:1000].tofile("output_UD.dat")
  plt.figure()
  plot_me((d[0], out[0]), sample_rate)
  plt.gcf().suptitle("Delay")
  plt.legend()
  plt.show()
