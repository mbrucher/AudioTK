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
    print(b, a)
    y = lfilter(b, a, data)
    return y
    
class Filter:
  def __init__(self):
    self.lms = DoubleLMSFilter(40)
    self.lms.set_input_sampling_rate(fs)
    self.lms.set_memory(0.999)
    self.lms.set_mu(0.015)

  def learn(self, input, ref):
    import numpy as np
    output = np.zeros(input.shape, dtype=np.float64)

    infilter = DoubleInPointerFilter(input, False)
    infilter.set_input_sampling_rate(fs)
    reffilter = DoubleInPointerFilter(ref, False)
    reffilter.set_input_sampling_rate(fs)
    self.lms.set_input_port(0, infilter, 0)
    self.lms.set_input_port(1, reffilter, 0)
    outfilter = DoubleOutPointerFilter(output, False)
    outfilter.set_input_sampling_rate(fs)
    outfilter.set_input_port(0, self.lms, 0)
    outfilter.process(input.shape[1])

    return output

if __name__ == "__main__":
  import numpy as np
  size = 48000
  window = size//10
  
  filter = Filter()
  
  lowcut = fs//10
  highcut = fs//5

  base = 100
  noise_amp = 0.5
  
  noise = np.random.randn(1, size)
  x = butter_bandpass_filter(np.random.randn(1, size), lowcut, highcut, fs)
  noise.tofile("input_only_noise.dat")
  
  out = filter.learn(noise, x)
  out.tofile("output_lms_noise.dat")
  
  import matplotlib.pyplot as plt
  from scipy import signal

  print(filter.lms.get_coefficients_in())
  
  b, a = butter_bandpass(lowcut, highcut, fs)
  w, h = signal.freqz(filter.lms.get_coefficients_in())
  w1, h1 = signal.freqz(b, a)
  plt.figure()
  plt.plot(w, np.abs(h), label="LMS filter")
  plt.plot(w, np.abs(h1), label="Reference")
  plt.legend()
  plt.grid(True)
  plt.title("Frequency response")
  
  from scipy.fftpack import fft
  
  freqs = np.arange(size//2+1) * np.pi / fs
  X = np.abs(fft(x[0])[:size//2+1])
  OUT = np.abs(fft(out[0])[:size//2+1])
  plt.figure()
  plt.semilogy(freqs, X, label="Training noise")
  plt.semilogy(freqs, OUT, label="Learnt noise")
  plt.title("Power spectrum of the noise")
  plt.legend()
  plt.show()
  