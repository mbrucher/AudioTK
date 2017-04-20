#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Delay import DoubleHadamardFeedbackDelayNetworkFilter

sample_rate = 96000

def filter(input, ingain_ch1=0, ingain_ch2=0, ingain_ch3=0, ingain_ch4=0,
    outgain_ch1=0, outgain_ch2=0, outgain_ch3=0, outgain_ch4=0,
    feedback_ch1=0, feedback_ch2=0, feedback_ch3=0, feedback_ch4=0):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)

  delayfilter = DoubleHadamardFeedbackDelayNetworkFilter(10000)
  delayfilter.set_input_sampling_rate(sample_rate)
  delayfilter.set_input_port(0, infilter, 0)
  delayfilter.set_delay(0, 4800) #50ms
  delayfilter.set_delay(1, 3600) #37.5ms
  delayfilter.set_delay(2, 2400) #25
  delayfilter.set_delay(3, 1200) #12.5ms
  delayfilter.set_ingain(0, ingain_ch1)
  delayfilter.set_ingain(1, ingain_ch2)
  delayfilter.set_ingain(2, ingain_ch3)
  delayfilter.set_ingain(3, ingain_ch4)
  delayfilter.set_outgain(0, outgain_ch1)
  delayfilter.set_outgain(1, outgain_ch2)
  delayfilter.set_outgain(2, outgain_ch3)
  delayfilter.set_outgain(3, outgain_ch4)
  delayfilter.set_feedback(0, feedback_ch1)
  delayfilter.set_feedback(1, feedback_ch2)
  delayfilter.set_feedback(2, feedback_ch3)
  delayfilter.set_feedback(3, feedback_ch4)
  
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(sample_rate)
  outfilter.set_input_port(0, delayfilter, 0)
  outfilter.process(input.shape[1])

  return output

if __name__ == "__main__":
  import numpy as np
  size = 9600
  
  x = np.arange(size, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(x * 2 * np.pi * 100)

  d[0].tofile("input_hadamard.dat")
  out = filter(d, ingain_ch1=1, ingain_ch2=.2, ingain_ch3=1, ingain_ch4=1,
    outgain_ch1=1, outgain_ch2=1, outgain_ch3=1, outgain_ch4=.5,
    feedback_ch1=0.1, feedback_ch2=0.4, feedback_ch3=0.2, feedback_ch4=.1
    )
  out[0].tofile("output_hadamard.dat")
  
  import matplotlib.pyplot as plt

  plt.plot(x[0][:9600], d[0][:9600], label="input")
  plt.plot(x[0][:9600], out[0][:9600], label="output")
  plt.legend()
  plt.show()