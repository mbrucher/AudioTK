#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleOversampling6points5order_32Filter, DoubleOversampling6points5order_16Filter, DoubleOversampling6points5order_8Filter, DoubleOversampling6points5order_4Filter, DoubleDecimationFilter
from ATK.EQ import DoubleButterworthLowPassFilter
from ATK.Preamplifier import DoubleEnhancedKorenTriodeFilter

def filter_32(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  overfilter = DoubleOversampling6points5order_32Filter()
  overfilter.input_sampling_rate = 48000
  overfilter.output_sampling_rate = 48000 * 32
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleEnhancedKorenTriodeFilter.build_standard_filter()
  overdrivefilter.input_sampling_rate = 48000 * 32
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.input_sampling_rate = 48000 * 32
  lowpassfilter.cut_frequency = 48000
  lowpassfilter.order = 5
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.input_sampling_rate = 48000 * 32
  decimationfilter.output_sampling_rate = 48000
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_16(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  overfilter = DoubleOversampling6points5order_16Filter()
  overfilter.input_sampling_rate = 48000
  overfilter.output_sampling_rate = 48000 * 16
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleEnhancedKorenTriodeFilter.build_standard_filter()
  overdrivefilter.input_sampling_rate = 48000 * 16
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.input_sampling_rate = 48000 * 16
  lowpassfilter.cut_frequency = 48000
  lowpassfilter.order = 5
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.input_sampling_rate = 48000 * 16
  decimationfilter.output_sampling_rate = 48000
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_8(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  overfilter = DoubleOversampling6points5order_8Filter()
  overfilter.input_sampling_rate = 48000
  overfilter.output_sampling_rate = 48000 * 8
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleEnhancedKorenTriodeFilter.build_standard_filter()
  overdrivefilter.input_sampling_rate = 48000 * 8
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.input_sampling_rate = 48000 * 8
  lowpassfilter.cut_frequency = 48000
  lowpassfilter.order = 5
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.input_sampling_rate = 48000 * 8
  decimationfilter.output_sampling_rate = 48000
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_4(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  overfilter = DoubleOversampling6points5order_4Filter()
  overfilter.input_sampling_rate = 48000
  overfilter.output_sampling_rate = 48000 * 4
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleEnhancedKorenTriodeFilter.build_standard_filter()
  overdrivefilter.input_sampling_rate = 48000 * 4
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.input_sampling_rate = 48000 * 4
  lowpassfilter.cut_frequency = 48000
  lowpassfilter.order = 5
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.input_sampling_rate = 48000 * 4
  decimationfilter.output_sampling_rate = 48000
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def enhanced_koren_32_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_tube.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_tube_32ek.dat", dtype=np.float64).reshape(1, -1)
  out = filter_32(x)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  size = 1200
  
  x = np.arange(size).reshape(1, -1) / 48000.
  d = np.sin(x * 2 * np.pi * 200) * 10
  d.tofile("input_tube.dat")
  out = filter_32(d)
  out.tofile("output_tube_32ek.dat")
  out = filter_16(d)
  out.tofile("output_tube_16ek.dat")
  out = filter_8(d)
  out.tofile("output_tube_8ek.dat")
  out = filter_4(d)
  out.tofile("output_tube_4ek.dat")

  import matplotlib.pyplot as plt
  plt.plot(x[0], d[0], label="input")
  plt.plot(x[0], out[0], label="output")
  plt.legend()
  plt.show()

