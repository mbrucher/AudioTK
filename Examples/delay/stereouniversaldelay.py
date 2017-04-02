#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter, PipelineGlobalSinkFilter
from ATK.Delay import DoubleStereoUniversalFixedDelayLineFilter

sample_rate = 96000

def filter(inputl, inputr, blend_ch1=0, blend_ch2=0,
    feedback_ch1_ch1=0, feedback_ch1_ch2=0, feedback_ch2_ch1=0, feedback_ch2_ch2=0,
    feedforward_ch1_ch1=1, feedforward_ch1_ch2=0, feedforward_ch2_ch1=0, feedforward_ch2_ch2=1):
  import numpy as np
  outputl = np.zeros(inputl.shape, dtype=np.float64)
  outputr = np.zeros(inputl.shape, dtype=np.float64)

  infilterL = DoubleInPointerFilter(inputl, False)
  infilterL.set_input_sampling_rate(sample_rate)
  infilterR = DoubleInPointerFilter(inputr, False)
  infilterR.set_input_sampling_rate(sample_rate)

  delayfilter = DoubleStereoUniversalFixedDelayLineFilter(100000)
  delayfilter.set_input_sampling_rate(sample_rate)
  delayfilter.set_input_port(0, infilterL, 0)
  delayfilter.set_input_port(1, infilterR, 0)
  delayfilter.set_delay(0, 4800) #50ms
  delayfilter.set_delay(1, 3600) #37.5ms
  delayfilter.set_blend(0, blend_ch1)
  delayfilter.set_blend(1, blend_ch2)
  delayfilter.set_feedback(0, 0, feedback_ch1_ch1)
  delayfilter.set_feedback(0, 1, feedback_ch1_ch2)
  delayfilter.set_feedback(1, 0, feedback_ch2_ch1)
  delayfilter.set_feedback(1, 1, feedback_ch2_ch2)
  delayfilter.set_feedforward(0, 0, feedforward_ch1_ch1)
  delayfilter.set_feedforward(0, 1, feedforward_ch1_ch2)
  delayfilter.set_feedforward(1, 0, feedforward_ch2_ch1)
  delayfilter.set_feedforward(1, 1, feedforward_ch2_ch2)
  
  outfilterl = DoubleOutPointerFilter(outputl, False)
  outfilterl.set_input_sampling_rate(sample_rate)
  outfilterl.set_input_port(0, delayfilter, 0)

  outfilterr = DoubleOutPointerFilter(outputr, False)
  outfilterr.set_input_sampling_rate(sample_rate)
  outfilterr.set_input_port(0, delayfilter, 1)
  
  pipelineend = PipelineGlobalSinkFilter()
  pipelineend.set_input_sampling_rate(sample_rate)
  pipelineend.add_filter(outfilterl)
  pipelineend.add_filter(outfilterr)
  pipelineend.process(inputl.shape[1])

  return outputl, outputr

if __name__ == "__main__":
  import numpy as np
  size = 960000
  
  x = np.arange(size, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(x * 2 * np.pi * 1000)
  dr = d[:,::-1].copy()
  
  np.savetxt("input.txt", d)
  outl, outr = filter(d, dr, blend_ch1=1, blend_ch2=1,
    feedforward_ch1_ch1=-1, feedforward_ch2_ch2=-1, feedforward_ch1_ch2=.1, feedforward_ch2_ch1=.7,
    feedback_ch1_ch1=-.5, feedback_ch1_ch2=.1, feedback_ch2_ch1=.3, feedback_ch2_ch2=-.1, )
  np.savetxt("outputl.txt", outl)
  np.savetxt("outputr.txt", outr)
