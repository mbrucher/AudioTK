#!/usr/bin/env python

from dempwolf_tube_filter import filter_4 as filter_4_d
from enhanced_tube_filter import filter_4 as filter_4_ek
from leach_tube_filter import filter_4 as filter_4_l
from munro_piazza_tube_filter import filter_4 as filter_4_mp
from tube_filter import filter_4 as filter_4_k

if __name__ == "__main__":
  import numpy as np
  size = 1200
  
  x = np.arange(size).reshape(1, -1) / 48000.
  d = np.sin(x * 2 * np.pi * 200) * 10
  d.tofile("input.dat")

  import matplotlib.pyplot as plt
  plt.plot(x[0], d[0], label="input")

  out = filter_4_ek(d)
  out.tofile("output4_ek.dat")
  plt.plot(x[0], out[0], label="Enhanced Koren")
  out = filter_4_k(d)
  out.tofile("output4_k.dat")
  plt.plot(x[0], out[0], label="Koren")
  out = filter_4_l(d)
  out.tofile("output4_l.dat")
  plt.plot(x[0], out[0], label="Leach")
  out = filter_4_mp(d)
  out.tofile("output4_mp.dat")
  plt.plot(x[0], out[0], label="Munro-Piazza")
  out = filter_4_d(d)
  out.tofile("output4_d.dat")
  plt.plot(x[0], out[0], label="Dempwolf")

  plt.legend()
  plt.show()

