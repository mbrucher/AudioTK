#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleOversampling6points5order_32Filter, DoubleOversampling6points5order_16Filter, DoubleOversampling6points5order_8Filter, DoubleOversampling6points5order_4Filter, DoubleDecimationFilter
from ATK.EQ import DoubleButterworthLowPassFilter
from ATK.Preamplifier import DoubleKorenTriodeFilter

import numpy as np
import scipy.signal as signal
import matplotlib.pyplot as plt

sample_rate = 96000

import sys
import os
sys.path.append(os.getcwd()+"/..")
from display.compare_spec import plot_me

def filter_32(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)
  overfilter = DoubleOversampling6points5order_32Filter()
  overfilter.set_input_sampling_rate(sample_rate)
  overfilter.set_output_sampling_rate(sample_rate * 32)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleKorenTriodeFilter.build_standard_filter()
  overdrivefilter.set_input_sampling_rate(sample_rate * 32)
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(sample_rate * 32)
  lowpassfilter.set_cut_frequency(sample_rate/2)
  lowpassfilter.set_order(10)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(sample_rate * 32)
  decimationfilter.set_output_sampling_rate(sample_rate)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_16(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)
  overfilter = DoubleOversampling6points5order_16Filter()
  overfilter.set_input_sampling_rate(sample_rate)
  overfilter.set_output_sampling_rate(sample_rate * 16)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleKorenTriodeFilter.build_standard_filter()
  overdrivefilter.set_input_sampling_rate(sample_rate * 16)
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(sample_rate * 16)
  lowpassfilter.set_cut_frequency(sample_rate/2)
  lowpassfilter.set_order(10)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(sample_rate * 16)
  decimationfilter.set_output_sampling_rate(sample_rate)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_8(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)
  overfilter = DoubleOversampling6points5order_8Filter()
  overfilter.set_input_sampling_rate(sample_rate)
  overfilter.set_output_sampling_rate(sample_rate * 8)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleKorenTriodeFilter.build_standard_filter()
  overdrivefilter.set_input_sampling_rate(sample_rate * 8)
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(sample_rate * 8)
  lowpassfilter.set_cut_frequency(20000)
  lowpassfilter.set_order(10)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(sample_rate * 8)
  decimationfilter.set_output_sampling_rate(sample_rate)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_4(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)
  overfilter = DoubleOversampling6points5order_4Filter()
  overfilter.set_input_sampling_rate(sample_rate)
  overfilter.set_output_sampling_rate(sample_rate * 4)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleKorenTriodeFilter.build_standard_filter()
  overdrivefilter.set_input_sampling_rate(sample_rate * 4)
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(sample_rate * 4)
  lowpassfilter.set_cut_frequency(20000)
  lowpassfilter.set_order(10)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(sample_rate * 4)
  decimationfilter.set_output_sampling_rate(sample_rate)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

if __name__ == "__main__":
  import numpy as np
  
  samples = 2000000
  freq_max = 20000

  t = np.arange(samples, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(np.pi * (sample_rate * freq_max / samples * (t + .1)) * t)

  np.savetxt("input.txt", d)
  out = filter_32(d)
  plt.figure()
  plt.title("Oversampling 32")
  plot_me((d[0], out[0]), sample_rate)
  np.savetxt("output32.txt", out)
  out = filter_16(d)
  plt.figure()
  plt.title("Oversampling 16")
  plot_me((d[0], out[0]), sample_rate)
  np.savetxt("output16.txt", out)
  out = filter_8(d)
  plt.figure()
  plt.title("Oversampling 8")
  plot_me((d[0], out[0]), sample_rate)
  np.savetxt("output8.txt", out)
  out = filter_4(d)
  plt.figure()
  plt.title("Oversampling 4")
  plot_me((d[0], out[0]), sample_rate)
  np.savetxt("output4.txt", out)
  plt.show()
