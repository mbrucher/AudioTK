#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Dynamic import DoubleApplyGainFilter, DoubleAttackReleaseFilter, DoubleGainCompressorFilter, DoublePowerFilter

import matplotlib.pyplot as plt

sample_rate = 96000

def plot_me(signal, MySampleRate, NFFT = 8192, noverlap = 1024):
  a = plt.subplot(2, 1, 1)
  plt.title("Original signal")
  plt.xlabel("s")
  plt.ylabel("Hz")
  plt.specgram(signal[0], NFFT = NFFT, Fs = MySampleRate, noverlap = noverlap )
  a = plt.subplot(2, 1, 2)
  plt.title("Processed signal")
  plt.xlabel("s")
  plt.ylabel("Hz")
  plt.specgram(signal[1], NFFT = NFFT, Fs = MySampleRate, noverlap = noverlap )

def filter(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)

  powerfilter = DoublePowerFilter(1)
  powerfilter.set_input_sampling_rate(sample_rate)
  powerfilter.set_input_port(0, infilter, 0)
  powerfilter.set_memory(np.exp(-1/(sample_rate*1e-3)))

  attackreleasefilter = DoubleAttackReleaseFilter(1)
  attackreleasefilter.set_input_sampling_rate(sample_rate)
  attackreleasefilter.set_input_port(0, powerfilter, 0)
  attackreleasefilter.set_attack(np.exp(-1/(sample_rate*1e-3)))
  attackreleasefilter.set_release(np.exp(-1/(sample_rate*100e-3)))

  gainfilter = DoubleGainCompressorFilter(1)
  gainfilter.set_input_sampling_rate(sample_rate)
  gainfilter.set_input_port(0, attackreleasefilter, 0)
  gainfilter.set_threshold(0.5)
  gainfilter.set_slope(4)
  gainfilter.set_softness(1)

  applygainfilter = DoubleApplyGainFilter(1)
  applygainfilter.set_input_sampling_rate(sample_rate)
  applygainfilter.set_input_port(0, gainfilter, 0)
  applygainfilter.set_input_port(1, infilter, 0)

  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, applygainfilter, 0)
  outfilter.process(input.shape[1])

  return output

if __name__ == "__main__":
  import numpy as np
  size = 2400

  x = np.arange(size, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(x * 2 * np.pi * 1000)

  np.savetxt("input.txt", d)
  out = filter(d)
  plt.figure()
  plt.plot(x[0], d[0], label="input")
  plt.plot(x[0], out[0], label="output")
  plt.title("Compressor")
  plt.legend()
  plt.show()
