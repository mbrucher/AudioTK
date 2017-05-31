#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.EQ import DoubleBesselLowPassFilter, DoubleBesselHighPassFilter, DoubleBesselBandPassFilter, DoubleBesselBandStopFilter

def filter_low(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  lowpassfilter = DoubleBesselLowPassFilter()
  lowpassfilter.input_sampling_rate = 48000
  lowpassfilter.cut_frequency = 1000
  lowpassfilter.order = 5
  lowpassfilter.set_input_port(0, infilter, 0)
  print(lowpassfilter.coefficients_in)
  print(lowpassfilter.coefficients_out)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, lowpassfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_high(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  highpassfilter = DoubleBesselHighPassFilter()
  highpassfilter.input_sampling_rate = 48000
  highpassfilter.cut_frequency = 1000
  highpassfilter.order = 5
  highpassfilter.set_input_port(0, infilter, 0)
  print(highpassfilter.coefficients_in)
  print(highpassfilter.coefficients_out)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, highpassfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_band(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  bandpassfilter = DoubleBesselBandPassFilter()
  bandpassfilter.input_sampling_rate = 48000
  bandpassfilter.cut_frequencies = (200, 1000)
  bandpassfilter.order = 5
  bandpassfilter.set_input_port(0, infilter, 0)
  print(bandpassfilter.coefficients_in)
  print(bandpassfilter.coefficients_out)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, bandpassfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_bandstop(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  bandstopfilter = DoubleBesselBandStopFilter()
  bandstopfilter.input_sampling_rate = 48000
  bandstopfilter.cut_frequencies = (200, 1000)
  bandstopfilter.order = 5
  bandstopfilter.set_input_port(0, infilter, 0)
  print(bandstopfilter.coefficients_in)
  print(bandstopfilter.coefficients_out)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, bandstopfilter, 0)
  outfilter.process(input.shape[1])
  return output

if __name__ == "__main__":
  import numpy as np
  d = np.arange(1000000).reshape(1, -1)
  d = np.sin(d * 2 * np.pi * 1000 / 48000)
  print(d[0,0:100])
  out = filter_low(d)
  print(out[0,0:100])
  out = filter_high(d)
  print(out[0,0:100])
  out = filter_band(d)
  print(out[0,0:100])
  out = filter_bandstop(d)
  print(out[0,0:100])
