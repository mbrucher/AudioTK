#!/usr/bin/env python

import matplotlib.pyplot as plt

def plot_me(signal, MySampleRate, NFFT = 8192, noverlap = 1024):
  a = plt.subplot(2, 1, 1)
  plt.title("Original signal")
  plt.xlabel("s")
  plt.ylabel("Hz")
  plt.specgram(signal[0], NFFT = NFFT, Fs = MySampleRate, noverlap = noverlap )
  plt.colorbar()
  a = plt.subplot(2, 1, 2)
  plt.title("Processed signal")
  plt.xlabel("s")
  plt.ylabel("Hz")
  plt.specgram(signal[1], NFFT = NFFT, Fs = MySampleRate, noverlap = noverlap )
  plt.colorbar()
