#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleOversampling6points5order_32Filter, DoubleDecimationFilter
from ATK.EQ import DoubleButterworthLowPassFilter
from ATK.Distortion import DoubleSimpleOverdriveFilter

def filter(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  overfilter = DoubleOversampling6points5order_32Filter()
  overfilter.set_input_sampling_rate(48000)
  overfilter.set_output_sampling_rate(48000 * 32)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleSimpleOverdriveFilter()
  overdrivefilter.set_input_sampling_rate(48000 * 32)
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(48000 * 32)
  lowpassfilter.set_cut_frequency(48000)
  lowpassfilter.set_order(5)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(48000 * 32)
  decimationfilter.set_output_sampling_rate(48000)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

if __name__ == "__main__":
  import numpy as np
  d = np.arange(100000).reshape(1, -1)
  d = np.sin(d * 2 * np.pi * 1000 / 48000)
  out = filter(d)
  np.savetxt("output.txt", out)
  np.savetxt("input.txt", d)
