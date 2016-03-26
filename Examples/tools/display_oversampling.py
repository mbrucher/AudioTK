#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleOversampling6points5order_32Filter

import matplotlib.pyplot as plt

sample_rate = 96000

def filter(input):
  import numpy as np
  output = np.zeros((1, input.shape[1] * 32), dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)
  
  overfilter = DoubleOversampling6points5order_32Filter()
  overfilter.set_input_sampling_rate(sample_rate)
  overfilter.set_output_sampling_rate(sample_rate * 32)
  overfilter.set_input_port(0, infilter, 0)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate * 32)
  outfilter.set_input_port(0, overfilter, 0)
  for i in range(10):
    outfilter.process(input.shape[1] / 10)

  return output

if __name__ == "__main__":
  import numpy as np
  import matplotlib.pyplot as plt
  samples = 1000

  t = np.arange(samples, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(t * 2 * np.pi * 100)

  t2 = np.arange(samples * 32, dtype=np.float64).reshape(1, -1) / (sample_rate * 32)
  d2 = filter(d)
  plt.plot(t[0], d[0], label="input")
  plt.plot(t2[0], d2[0], label="output")
  plt.gcf().suptitle("Oversampling")
  plt.legend()
  plt.show()
