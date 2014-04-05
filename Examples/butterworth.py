#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.EQ import DoubleButterworthLowPassFilter

def filter(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(48000)
  lowpassfilter.set_cut_frequency(1000)
  lowpassfilter.set_order(5)
  lowpassfilter.set_input_port(0, infilter, 0)
  print lowpassfilter.get_coefficients_in()
  print lowpassfilter.get_coefficients_out()
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, lowpassfilter, 0)
  outfilter.process(input.shape[1])
  return output

if __name__ == "__main__":
  import numpy as np
  d = np.arange(1000000).reshape(1, -1)
  d = np.sin(d * 2 * np.pi * 1000 / 48000)
  out = filter(d)
  np.savetxt("output.txt", out)
  np.savetxt("input.txt", d)
