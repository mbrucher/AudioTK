#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.EQ import DoubleChebyshev1LowPassFilter, DoubleChebyshev1HighPassFilter, DoubleChebyshev1BandPassFilter, DoubleChebyshev1BandStopFilter

def filter_low(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  lowpassfilter = DoubleChebyshev1LowPassFilter()
  lowpassfilter.input_sampling_rate = 48000
  lowpassfilter.cut_frequency = 1000
  lowpassfilter.order = 5
  lowpassfilter.ripple = 3
  lowpassfilter.set_input_port(0, infilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, lowpassfilter, 0)
  outfilter.process(input.shape[1])
  return output, lowpassfilter.coefficients_in, lowpassfilter.coefficients_out

def filter_high(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  highpassfilter = DoubleChebyshev1HighPassFilter()
  highpassfilter.input_sampling_rate = 48000
  highpassfilter.cut_frequency = 1000
  highpassfilter.order = 5
  highpassfilter.ripple = 3
  highpassfilter.set_input_port(0, infilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, highpassfilter, 0)
  outfilter.process(input.shape[1])
  return output, highpassfilter.coefficients_in, highpassfilter.coefficients_out

def filter_band(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  bandpassfilter = DoubleChebyshev1BandPassFilter()
  bandpassfilter.input_sampling_rate = 48000
  bandpassfilter.cut_frequencies = (200, 1000)
  bandpassfilter.order = 5
  bandpassfilter.ripple = 3
  bandpassfilter.set_input_port(0, infilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, bandpassfilter, 0)
  outfilter.process(input.shape[1])
  return output, bandpassfilter.coefficients_in, bandpassfilter.coefficients_out

def filter_bandstop(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)
  
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  bandstopfilter = DoubleChebyshev1BandStopFilter()
  bandstopfilter.input_sampling_rate = 48000
  bandstopfilter.cut_frequencies = (200, 1000)
  bandstopfilter.order = 5
  bandstopfilter.ripple = 3
  bandstopfilter.set_input_port(0, infilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, bandstopfilter, 0)
  outfilter.process(input.shape[1])
  return output, bandstopfilter.coefficients_in, bandstopfilter.coefficients_out

def cheby1_lowpass_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  from scipy.signal import cheby1

  x = np.arange(1000).reshape(1, -1)
  d = np.sin(x * 2 * np.pi * 1000 / 48000)
  
  out, b, a = filter_low(d)
  
  bref, aref = cheby1(5, 3, 1000/24000.)
  
  assert_almost_equal(b, bref)
  assert_almost_equal(np.hstack(([1], -a[::-1])), aref)

def cheby1_highpass_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  from scipy.signal import cheby1

  x = np.arange(10000).reshape(1, -1)
  d = np.sin(x * 2 * np.pi * 1000 / 48000)
  
  out, b, a = filter_high(d)
  
  bref, aref = cheby1(5, 3, 1000/24000., btype='highpass')
  
  assert_almost_equal(-b, bref)
  assert_almost_equal(np.hstack(([1], -a[::-1])), aref)

def cheby1_bandpass_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  from scipy.signal import cheby1

  x = np.arange(10000).reshape(1, -1)
  d = np.sin(x * 2 * np.pi * 1000 / 48000)
  
  out, b, a = filter_band(d)
  
  bref, aref = cheby1(5, 3, (200/24000., 1000/24000.), btype='bandpass')
  
  assert_almost_equal(-b, bref)
  assert_almost_equal(np.hstack(([1], -a[::-1])), aref)

def cheby1_bandstop_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  from scipy.signal import cheby1

  x = np.arange(10000).reshape(1, -1)
  d = np.sin(x * 2 * np.pi * 1000 / 48000)
  
  out, b, a = filter_bandstop(d)
  
  bref, aref = cheby1(5, 3, (200/24000., 1000/24000.), btype='bandstop')
  
  assert_almost_equal(b, bref)
  assert_almost_equal(np.hstack(([1], -a[::-1])), aref)

if __name__ == "__main__":
  import numpy as np
  import matplotlib.pyplot as plt
  x = np.arange(1000).reshape(1, -1) / 48000.
  d = np.sin(x * 2 * np.pi * 1000)
  
  plt.figure()
  out, b, a = filter_low(d)
  plt.plot(x[0], out[0], label="Lowpass")
  out, b, a = filter_high(d)
  plt.plot(x[0], out[0], label="Highpass")
  out, b, a = filter_band(d)
  #plt.plot(x[0], out[0], label="Bandpass")
  out, b, a = filter_bandstop(d)
  #plt.plot(x[0], out[0], label="Bandstop")
  plt.legend()
  plt.show()
  