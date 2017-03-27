#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleOversampling6points5order_32Filter, DoubleOversampling6points5order_16Filter, DoubleOversampling6points5order_8Filter, DoubleOversampling6points5order_4Filter, DoubleDecimationFilter
from ATK.EQ import DoubleButterworthLowPassFilter, DoubleSD1ToneFilter, DoubleChamberlinFilter
from ATK.Distortion import DoubleSD1OverdriveFilter, DoubleTS9OverdriveFilter

sample_rate = 48000

def filter_sd1(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  inputfilter = DoubleInPointerFilter(input, False)
  inputfilter.set_input_sampling_rate(sample_rate)
  infilter = DoubleChamberlinFilter()
  infilter.set_input_sampling_rate(sample_rate)
  infilter.set_input_port(0, inputfilter, 0)
  infilter.select(0)
  infilter.set_attenuation(1)
  infilter.set_cut_frequency(1000)
  overfilter = DoubleOversampling6points5order_4Filter()
  overfilter.set_input_sampling_rate(sample_rate)
  overfilter.set_output_sampling_rate(sample_rate * 4)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleSD1OverdriveFilter()
  overdrivefilter.set_input_sampling_rate(sample_rate * 4)
  overdrivefilter.set_input_port(0, overfilter, 0)
  overdrivefilter.set_drive(0.9)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(sample_rate * 4)
  lowpassfilter.set_cut_frequency(sample_rate)
  lowpassfilter.set_order(5)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(sample_rate * 4)
  decimationfilter.set_output_sampling_rate(sample_rate)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_ts9(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  inputfilter = DoubleInPointerFilter(input, False)
  inputfilter.set_input_sampling_rate(sample_rate)
  infilter = DoubleChamberlinFilter()
  infilter.set_input_sampling_rate(sample_rate)
  infilter.set_input_port(0, inputfilter, 0)
  infilter.select(0)
  infilter.set_attenuation(1)
  infilter.set_cut_frequency(1000)
  overfilter = DoubleOversampling6points5order_4Filter()
  overfilter.set_input_sampling_rate(sample_rate)
  overfilter.set_output_sampling_rate(sample_rate * 4)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleTS9OverdriveFilter()
  overdrivefilter.set_input_sampling_rate(sample_rate * 4)
  overdrivefilter.set_input_port(0, overfilter, 0)
  overdrivefilter.set_drive(0.9)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(sample_rate * 4)
  lowpassfilter.set_cut_frequency(sample_rate)
  lowpassfilter.set_order(5)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(sample_rate * 4)
  decimationfilter.set_output_sampling_rate(sample_rate)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

if __name__ == "__main__":
  import numpy as np
  size = 1200
  
  x = np.arange(size).reshape(1, -1) / 48000.
  d = np.sin(x * 2 * np.pi * 100)
  np.savetxt("input.txt", d)
  outsd1 = filter_sd1(d)
  np.savetxt("output_sd1.txt", outsd1)
  outts9 = filter_ts9(d)
  np.savetxt("output_ts9.txt", outts9)

  import matplotlib.pyplot as plt
  plt.plot(x[0], d[0], label="input")
  plt.plot(x[0], outsd1[0], label="SD1")
  plt.plot(x[0], outts9[0], label="TS9")
  plt.legend()
  plt.show()
