#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Delay import DoubleUniversalFixedDelayLineFilter

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

  delayfilter = DoubleUniversalFixedDelayLineFilter(5000)
  delayfilter.set_input_sampling_rate(sample_rate)
  delayfilter.set_input_port(0, infilter, 0)
  delayfilter.set_delay(4800) #50ms
  delayfilter.set_blend(blend)
  delayfilter.set_feedback(feedback)
  delayfilter.set_feedforward(feedforward)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, delayfilter, 0)
  outfilter.process(input.shape[1])

  return output

if __name__ == "__main__":
  import numpy as np
  samples = 2000000
  freq_max = 20000

  t = np.arange(samples, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(np.pi * (sample_rate * freq_max / samples * (t + .1)) * t)

  np.savetxt("input.txt", d)
  out = filter(d, feedforward=-1, blend=1, feedback=-.5)
  np.savetxt("output.txt", out)
  plt.figure()
  plot_me((d[0], out[0]), sample_rate)
  plt.gcf().suptitle("Delay")
  plt.legend()
  plt.show()
