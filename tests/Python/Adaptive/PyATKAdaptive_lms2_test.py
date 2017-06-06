#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Adaptive import DoubleLMSFilter

from scipy.signal import butter, lfilter

fs = 48000

def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return b, a

def butter_bandpass_filter(data, lowcut, highcut, fs, order=5):
    b, a = butter_bandpass(lowcut, highcut, fs, order=order)
    y = lfilter(b, a, data)
    return y

def filter(input, reference):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = 48000
  reffilter = DoubleInPointerFilter(reference, False)
  reffilter.input_sampling_rate = 48000
  rls = DoubleLMSFilter(12)
  rls.input_sampling_rate = 48000
  rls.memory = 0.9
  rls.mu = 0.05
  rls.set_input_port(0, infilter, 0)
  rls.set_input_port(1, reffilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = 48000
  outfilter.set_input_port(0, rls, 0)
  outfilter.process(input.shape[1])

  return output

def LMS2_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  d = np.fromfile(dirname + os.sep + "input_lms2.dat", dtype=np.float64).reshape(1, -1)
  noise = np.fromfile(dirname + os.sep + "noise_lms2.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_lms2.dat", dtype=np.float64).reshape(1, -1)
  out = filter(d, noise)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  size = fs
  window = size//20

  lowcut = fs//10
  highcut = fs//5
  
  noise = np.random.randn(1, size)/10
  noise = butter_bandpass_filter(noise, lowcut, highcut, fs)

  noise.tofile("noise_lms2.dat")
  x = np.arange(size, dtype=np.float64).reshape(1, -1) / fs
  d = np.sin(x * 2 * np.pi * 100) + noise
  d.tofile("input_lms2.dat")
  out = filter(d, noise)
  out.tofile("output_lms2.dat")
  noise = noise[:,1:]
  x = x[:,1:]
  d = d[:,1:]
  out = out[:,:-1]

  import matplotlib.pyplot as plt
  print(x)
  plt.plot(x[0,size-window:size], d[0,size-window:size], label="Noisy signal")
  plt.plot(x[0,size-window:size], noise[0,size-window:size], label="Original noise")
  plt.plot(x[0,size-window:size], (d[0,size-window:size] - out[0,size-window:size]), label="Estimated signal")
  plt.plot(x[0,size-window:size], out[0,size-window:size], label="Estimated noise")
  plt.legend()

  from scipy.fftpack import fft
  freqs = np.arange(size//2+1)

  D1 = np.abs(fft(d[0])[:size//2+1])
  OUT1 = np.abs(fft(d[0] - out[0])[:size//2+1])
  REF = np.abs(fft(d[0] - noise[0])[:size//2+1])
  plt.figure()
  plt.subplot(2,1,1)
  plt.semilogy(freqs[:601], D1[:601], label="Noisy signal")
  plt.semilogy(freqs[:601], OUT1[:601], label="Filtered signal")
  plt.semilogy(freqs[:601], REF[:601], label="Original signal")
  plt.title("Power spectrum of the signals (0-600Hz)")
  plt.legend()
  plt.subplot(2,1,2)
  plt.semilogy(freqs[lowcut:highcut+1], D1[lowcut:highcut+1], label="Noisy signal")
  plt.semilogy(freqs[lowcut:highcut+1], OUT1[lowcut:highcut+1], label="Filtered signal")
  plt.semilogy(freqs[lowcut:highcut+1], REF[lowcut:highcut+1], label="Original signal")
  plt.title("Power spectrum of the signals (%i-%i Hz)" % (lowcut,highcut))
  plt.legend()
  
  plt.show()
