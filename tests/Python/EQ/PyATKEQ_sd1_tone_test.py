#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.EQ import DoubleSD1ToneFilter

sampling = 48000

def tone_filter(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sampling
  tonefilter = DoubleSD1ToneFilter()
  tonefilter.input_sampling_rate = sampling
  tonefilter.set_input_port(0, infilter, 0)
  tonefilter.tone = 0.5
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sampling
  outfilter.set_input_port(0, tonefilter, 0)
  outfilter.process(input.shape[1])
  return output, tonefilter.coefficients_in, tonefilter.coefficients_out

def create_coeffs(alpha):
  R1 = 10e3
  C1 = 0.018e-6
  R2 = 22e3
  C2 = 0.027e-6
  R3 = 470
  C3 = 0.01e-6
  R4 = 10e3
  
  return ((C3*R4*(R3*C2+alpha*(1-alpha)*R2*C2)), (C2*R3+R4*C3+alpha*(1-alpha)*R2*C2+alpha*C2*R4), 1), ((C1*R1*(R3*C2+alpha*(1-alpha)*R2*C2)), (C2*R3+R1*C1+alpha*(1-alpha)*R2*C2+(1-alpha)*C2*R1), 1)

def sd1_tone_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  from scipy.signal import bilinear
  
  x = np.arange(10000).reshape(1, -1)
  d = np.sin(x * 2 * np.pi * 1000 / 48000)
  
  out, b, a = tone_filter(d)
  b0, a0 = create_coeffs(.5)
  bref, aref = bilinear(b0, a0, sampling)

  assert_almost_equal(b[::-1], bref)
  assert_almost_equal(np.hstack(([1], -a[::-1])), aref)

if __name__ == "__main__":
  import numpy as np
  from scipy import signal
  import matplotlib.pyplot as plt
  
  b0, a0 = create_coeffs(.9)
  print(b0, a0)
  print(np.roots(b0[::-1]), np.roots(a0[::-1])) # a0 roots should have a real part negative. It seems to be related to R3 smaller than R2. The equation must be wrong somewhere.
  b0d, a0d = signal.bilinear(b0, a0, sampling)
  print(b0d, a0d)
  print(np.roots(b0d), np.roots(a0d))
  size = 1000
  
  x = np.arange(size, dtype=np.float64).reshape(1, -1)/ sampling
  d = np.sin(x * 2 * np.pi * 1000)
  out, b, a = tone_filter(d)
  outt = signal.lfilter(b0d, a0d, d)

  plt.plot(x[0], d[0], label="Raw")
  plt.plot(x[0], out[0], label="Filtered")
