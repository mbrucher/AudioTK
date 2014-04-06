#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.EQ import DoubleButterworthLowPassFilter, DoubleButterworthHighPassFilter, DoubleButterworthBandPassFilter, DoubleButterworthBandStopFilter

def filter_low(input):
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

def filter_high(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  highpassfilter = DoubleButterworthHighPassFilter()
  highpassfilter.set_input_sampling_rate(48000)
  highpassfilter.set_cut_frequency(1000)
  highpassfilter.set_order(5)
  highpassfilter.set_input_port(0, infilter, 0)
  print highpassfilter.get_coefficients_in()
  print highpassfilter.get_coefficients_out()
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, highpassfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_band(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  bandpassfilter = DoubleButterworthBandPassFilter()
  bandpassfilter.set_input_sampling_rate(48000)
  bandpassfilter.set_cut_frequencies(200, 1000)
  bandpassfilter.set_order(5)
  bandpassfilter.set_input_port(0, infilter, 0)
  print bandpassfilter.get_coefficients_in()
  print bandpassfilter.get_coefficients_out()
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, bandpassfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_bandstop(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  bandstopfilter = DoubleButterworthBandStopFilter()
  bandstopfilter.set_input_sampling_rate(48000)
  bandstopfilter.set_cut_frequencies(200, 1000)
  bandstopfilter.set_order(5)
  bandstopfilter.set_input_port(0, infilter, 0)
  print bandstopfilter.get_coefficients_in()
  print bandstopfilter.get_coefficients_out()
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, bandstopfilter, 0)
  outfilter.process(input.shape[1])
  return output

if __name__ == "__main__":
  import numpy as np
  d = np.arange(1000000).reshape(1, -1)
  d = np.sin(d * 2 * np.pi * 1000 / 48000)
  print d[0,0:100]
  out = filter_low(d)
  print out[0,0:100]
  out = filter_high(d)
  print out[0,0:100]
  out = filter_band(d)
  print out[0,0:100]
  out = filter_bandstop(d)
  print out[0,0:100]
