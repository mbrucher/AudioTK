#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Adaptive import DoubleRLSFilter

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
    
class Filter:
  def __init__(self):
    self.rls = DoubleRLSFilter(5)
    self.rls.set_input_sampling_rate(fs)
    self.rls.set_memory(0.999)

  def learn(self, input):
    self.rls.set_learning(True)
    
    import numpy as np
    output = np.zeros(input.shape, dtype=np.float64)

    infilter = DoubleInPointerFilter(input, False)
    infilter.set_input_sampling_rate(fs)
    self.rls.set_input_port(0, infilter, 0)
    outfilter = DoubleOutPointerFilter(output, False)
    outfilter.set_input_sampling_rate(fs)
    outfilter.set_input_port(0, self.rls, 0)
    outfilter.process(input.shape[1])
    
    return output

  def process(self, input):
    self.rls.set_learning(False)

    import numpy as np
    output = np.zeros(input.shape, dtype=np.float64)
    
    infilter = DoubleInPointerFilter(input, False)
    infilter.set_input_sampling_rate(fs)
    self.rls.set_input_port(0, infilter, 0)
    outfilter = DoubleOutPointerFilter(output, False)
    outfilter.set_input_sampling_rate(fs)
    outfilter.set_input_port(0, self.rls, 0)
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
  
  x = noise_amp*butter_bandpass_filter(np.random.randn(1, size), lowcut, highcut, fs)
  x.tofile("input_only_noise.dat")
  
  out = filter.learn(x)
  out.tofile("output_rls_noise.dat")
  
  x1 = np.arange(size).reshape(1, -1) / fs
  ref = np.sin(x1 * 2 * np.pi * base) + 1/3 * np.sin(x1 * 2 * np.pi * 3.1*base) + 1/5 * np.sin(x1 * 2 * np.pi * 4.95*base)
  d1 = ref + noise_amp*butter_bandpass_filter(np.random.randn(1, size), lowcut, highcut, fs)
  d1.tofile("input_with_noise.dat")
  ref.tofile("input_without_noise.dat")
  out1 = filter.process(d1)
  out1.tofile("output_noise_rls.dat")

  import matplotlib.pyplot as plt
  plt.plot(x1[0], x[0], label="Training noise")
  plt.plot(x1[0], out[0], label="Learnt noise")
  plt.plot(x1[0], x[0] - out[0], label="Remaining noise")
  plt.legend()
  plt.title("Noise learning stage")

  print("Original noise power: " + str(np.mean(x**2)))
  print("Learnt noise power: " + str(np.mean(out**2)))
  print("Remaining noise power: " + str(np.mean((x-out)**2)))

  plt.figure()
  plt.subplot(2,1,1)
  plt.plot(x1[0,size-window:size], d1[0,size-window:size], label="Noisy signal")
  plt.plot(x1[0,size-window:size], d1[0,size-window:size] - out1[0,size-window:size], label="Filtered signal")
  plt.plot(x1[0,size-window:size], ref[0,size-window:size], label="Original signal")
  plt.title("Comparison between original and filtered signal")
  plt.legend()
  plt.subplot(2,1,2)
  plt.plot(x1[0,size-window:size], d1[0,size-window:size] - ref[0,size-window:size], label="Original noise")
  plt.plot(x1[0,size-window:size], out1[0,size-window:size], label="Estimated noise")
  plt.plot(x1[0,size-window:size], d1[0,size-window:size] - ref[0,size-window:size] - out1[0,size-window:size], label="Remaining noise")
  plt.title("Comparison between original and remaining noise")
  plt.legend()

  print("Signal to noise ratio: " + str(np.mean(ref**2)/np.mean((ref - d1)**2)))
  print("Signal to remaining noise ratio: " + str(np.mean(ref**2)/np.mean((d1 - ref - out1)**2)))
  
  from scipy.fftpack import fft
  
  freqs = np.arange(size//2+1)
  X = np.abs(fft(x[0])[:size//2+1])
  OUT = np.abs(fft(out[0])[:size//2+1])
  REM = np.abs(fft(out[0] - x[0])[:size//2+1])
  plt.figure()
  plt.semilogy(freqs, X, label="Training noise")
  plt.semilogy(freqs, OUT, label="Learnt noise")
  plt.semilogy(freqs, REM, label="Learnt noise")
  plt.title("Power spectrum of the noise")
  plt.legend()

  D1 = np.abs(fft(d1[0])[:size//2+1])
  OUT1 = np.abs(fft(d1[0] - out1[0])[:size//2+1])
  REF = np.abs(fft(ref[0])[:size//2+1])
  plt.figure()
  plt.subplot(2,1,1)
  plt.semilogy(freqs[:601], D1[:601], label="Noisy signal")
  plt.semilogy(freqs[:601], OUT1[:601], label="Filtered signal")
#  plt.semilogy(freqs[:601], REF[:601], label="Original signal")
  plt.title("Power spectrum of the signals (0-600Hz)")
  plt.legend()
  plt.subplot(2,1,2)
  plt.semilogy(freqs[lowcut:highcut+1], D1[lowcut:highcut+1], label="Noisy signal")
  plt.semilogy(freqs[lowcut:highcut+1], OUT1[lowcut:highcut+1], label="Filtered signal")
#  plt.semilogy(freqs[lowcut:highcut+1], REF[lowcut:highcut+1], label="Original signal")
  plt.title("Power spectrum of the signals (%i-%i Hz)" % (lowcut,highcut))
  plt.legend()
  
  plt.show()
