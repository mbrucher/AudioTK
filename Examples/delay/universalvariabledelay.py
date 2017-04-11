#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Delay import DoubleUniversalVariableDelayLineFilter
from ATK.Tools import DoubleCachedSinusGeneratorFilter

sample_rate = 96000

import matplotlib.pyplot as plt

def filter(input, delay, blend=0, feedback=0, feedforward=1):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)

  generator = DoubleInPointerFilter(delay, False)
  generator.set_input_sampling_rate(sample_rate)

  delayfilter = DoubleUniversalVariableDelayLineFilter(5000)
  delayfilter.set_input_sampling_rate(sample_rate)
  delayfilter.set_input_port(0, infilter, 0)
  delayfilter.set_input_port(1, generator, 0)
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
  size = 200
  
  x = np.arange(size, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(x * 2 * np.pi * 1000)
  delay = (1.5e-3 + 1.e-3 * np.sin(x * 2 * np.pi*10)) * sample_rate

  np.savetxt("input.txt", d)
  out = filter(d, delay, feedforward=-1, blend=1, feedback=-.5)
  np.savetxt("output.txt", out)
  plt.plot(x[0], d[0], label="Input")
  plt.plot(x[0], out[0], label="Output")
  plt.legend()
  plt.grid(True)
  plt.show()
