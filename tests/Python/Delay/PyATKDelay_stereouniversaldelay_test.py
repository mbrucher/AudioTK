#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter, PipelineGlobalSinkFilter
from ATK.Delay import DoubleDualMultipleUniversalFixedDelayLineFilter

sample_rate = 96000

def filter(inputl, inputr, blend_ch1=0, blend_ch2=0,
    feedback_ch1_ch1=0, feedback_ch1_ch2=0, feedback_ch2_ch1=0, feedback_ch2_ch2=0,
    feedforward_ch1_ch1=1, feedforward_ch1_ch2=0, feedforward_ch2_ch1=0, feedforward_ch2_ch2=1):
  import numpy as np
  outputl = np.zeros(inputl.shape, dtype=np.float64)
  outputr = np.zeros(inputl.shape, dtype=np.float64)

  infilterL = DoubleInPointerFilter(inputl, False)
  infilterL.input_sampling_rate = sample_rate
  infilterR = DoubleInPointerFilter(inputr, False)
  infilterR.input_sampling_rate = sample_rate

  delayfilter = DoubleDualMultipleUniversalFixedDelayLineFilter(5000)
  delayfilter.input_sampling_rate = sample_rate
  delayfilter.set_input_port(0, infilterL, 0)
  delayfilter.set_input_port(1, infilterR, 0)
  delayfilter.set_delay(0,4800) #50ms
  delayfilter.set_delay(1,3600) #37.5ms
  delayfilter.set_blend(0,blend_ch1)
  delayfilter.set_blend(1,blend_ch2)
  delayfilter.set_feedback(0,0,feedback_ch1_ch1)
  delayfilter.set_feedback(0,1,feedback_ch1_ch2)
  delayfilter.set_feedback(1,0,feedback_ch2_ch1)
  delayfilter.set_feedback(1,1,feedback_ch2_ch2)
  delayfilter.set_feedforward(0,0,feedforward_ch1_ch1)
  delayfilter.set_feedforward(0,1,feedforward_ch1_ch2)
  delayfilter.set_feedforward(1,0,feedforward_ch2_ch1)
  delayfilter.set_feedforward(1,1,feedforward_ch2_ch2)
  
  outfilterl = DoubleOutPointerFilter(outputl, False)
  outfilterl.input_sampling_rate = sample_rate
  outfilterl.set_input_port(0, delayfilter, 0)

  outfilterr = DoubleOutPointerFilter(outputr, False)
  outfilterr.input_sampling_rate = sample_rate
  outfilterr.set_input_port(0, delayfilter, 1)
  
  pipelineend = PipelineGlobalSinkFilter()
  pipelineend.input_sampling_rate = sample_rate
  pipelineend.add_filter(outfilterl)
  pipelineend.add_filter(outfilterr)
  pipelineend.process(inputl.shape[1])

  return outputl, outputr

def dualmultipleuniversaldelay_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  d = np.fromfile(dirname + os.sep + "input_SUDl.dat", dtype=np.float64).reshape(1, -1)
  dr = np.fromfile(dirname + os.sep + "input_SUDr.dat", dtype=np.float64).reshape(1, -1)
  refl = np.fromfile(dirname + os.sep + "output_SUDl.dat", dtype=np.float64).reshape(1, -1)
  refr = np.fromfile(dirname + os.sep + "output_SUDr.dat", dtype=np.float64).reshape(1, -1)
  outl, outr = filter(d, dr, blend_ch1=1, blend_ch2=1,
                      feedforward_ch1_ch1=-1, feedforward_ch2_ch2=-1, feedforward_ch1_ch2=.1, feedforward_ch2_ch1=.7,
                      feedback_ch1_ch1=-.5, feedback_ch1_ch2=.1, feedback_ch2_ch1=.3, feedback_ch2_ch2=-.1, )
  assert_almost_equal(outl, refl)
  assert_almost_equal(outr, refr)

if __name__ == "__main__":
  import numpy as np
  samples = 2000000
  freq_max = 20000

  import matplotlib.pyplot as plt

  import sys, os
  sys.path.append(os.path.dirname(os.path.realpath(__file__))+"/..")
  from display.compare_spec import plot_me

  t = np.arange(samples, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(np.pi * (sample_rate * freq_max / samples * (t + .1)) * t)
  dr = d[:,::-1].copy()

  d[:,:1000].tofile("input_SUDl.dat")
  dr[:,:1000].tofile("input_SUDr.dat")
  outl, outr = filter(d, dr, blend_ch1=1, blend_ch2=1,
    feedforward_ch1_ch1=-1, feedforward_ch2_ch2=-1, feedforward_ch1_ch2=.1, feedforward_ch2_ch1=.7,
    feedback_ch1_ch1=-.5, feedback_ch1_ch2=.1, feedback_ch2_ch1=.3, feedback_ch2_ch2=-.1, )
  outl[:,:1000].tofile("output_SUDl.dat")
  outr[:,:1000].tofile("output_SUDr.dat")

  plt.figure()
  plot_me((d[0], outl[0]), sample_rate)
  plt.gcf().suptitle("Delay Channel R")
  plt.figure()
  plot_me((dr[0], outr[0]), sample_rate)
  plt.gcf().suptitle("Delay Channel L")
  plt.show()
