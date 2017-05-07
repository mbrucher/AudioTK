#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleOversampling6points5order_32Filter, DoubleOversampling6points5order_16Filter, DoubleOversampling6points5order_8Filter, DoubleOversampling6points5order_4Filter, DoubleDecimationFilter
from ATK.EQ import DoubleButterworthLowPassFilter
from ATK.Preamplifier import DoubleKorenTriodeFilter

def filter_4(input, Rp, Rg, Ro, Rk, VBias, Co, Ck):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  overfilter = DoubleOversampling6points5order_4Filter()
  overfilter.set_input_sampling_rate(48000)
  overfilter.set_output_sampling_rate(48000 * 4)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleKorenTriodeFilter.build_standard_filter(Rp, Rg, Ro, Rk, VBias, Co, Ck)
  overdrivefilter.set_input_sampling_rate(48000 * 4)
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(48000 * 4)
  lowpassfilter.set_cut_frequency(48000)
  lowpassfilter.set_order(5)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(48000 * 4)
  decimationfilter.set_output_sampling_rate(48000)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

import matplotlib.pyplot as plt
def compute_and_plot(d, txt):
  d.tofile("input_preamps_" + txt + ".dat")
  out_default = filter_4(d, Rp=200e3, Rg=220e3, Ro=220e3, Rk=1e3, VBias=300, Co=22e-9, Ck=1e-6)
  out_default.tofile("output4_default_" + txt + ".dat")
  out_guitar = filter_4(d, Rp=100e3, Rg=220e3, Ro=22e3, Rk=2.7e3, VBias=300, Co=20e-9, Ck=10e-6)
  out_guitar.tofile("output4_guitar_" + txt + ".dat")
  out_bass = filter_4(d, Rp=100e3, Rg=1e6, Ro=1e6, Rk=820, VBias=300, Co=22e-9, Ck=250e-6)
  out_bass.tofile("output4_bass_" + txt + ".dat")
  
  plt.figure()
  plt.plot(x[0], d[0], label="input")
  plt.plot(x[0], out_default[0], label="Default circuit")
  plt.plot(x[0], out_guitar[0], label="Guitar preamp")
  plt.plot(x[0], out_bass[0], label="Bass preamp")
  plt.title(txt + "Hz input signal")
  plt.legend()

if __name__ == "__main__":
  import numpy as np
  size = 1200
  
  x = np.arange(size).reshape(1, -1) / 48000.
  d = np.sin(x * 2 * np.pi * 200) * 5
  compute_and_plot(d, "200")
  d = np.sin(x * 2 * np.pi * 40) * 5
  compute_and_plot(d, "40")
  d = np.sin(x * 2 * np.pi * 1000) * 5
  compute_and_plot(d, "1k")

  plt.show()

"""
  Build a custom filter with a given tube function contructor
  The defaults are Rp=200e3, Rg=220e3, Ro=220e3, Rk=1e3, VBias=300, Co=22e-9, Ck=1e-6
  Guitar preamp: Rp=100e3, Rg=220e3, Ro=22e3, Rk=2.7e3, VBias=300, Co=20e-9, Ck=10e-6
  Bass preamp: Rp=100e3, Rg=1e6, Ro=1e6, Rk=820, VBias=300, Co=22e-9, Ck=250e-6
"""
