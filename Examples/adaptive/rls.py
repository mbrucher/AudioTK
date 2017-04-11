#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Adaptive import DoubleRLSFilter

def filter(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  rls = DoubleRLSFilter(10)
  rls.set_input_sampling_rate(48000)
  rls.set_memory(0.99)
  rls.set_learning(True)
  rls.set_input_port(0, infilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, rls, 0)
  outfilter.process(1000)
  rls.set_learning(False)
  outfilter.process(input.shape[1] - 1000)

  return output

if __name__ == "__main__":
  import numpy as np
  size = 5000
  
  x = np.arange(size).reshape(1, -1) / 48000.
  d = np.sin(x * 2 * np.pi * 100)
  d.tofile("input.dat")
  out = filter(d)
  out.tofile("output_rls.dat")

  import matplotlib.pyplot as plt
  plt.plot(x[0], d[0], label="input")
  plt.plot(x[0], out[0], label="output")
  plt.legend()
  plt.show()
