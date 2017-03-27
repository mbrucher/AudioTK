#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter, PipelineGlobalSinkFilter
from ATK.Dynamic import DoubleAttackReleaseFilter, DoubleGainCompressorFilter, DoublePowerFilter
from ATK.Tools import DoubleApplyGainFilter, DoubleVolumeFilter, DoubleMiddleSideFilter

import matplotlib.pyplot as plt

sample_rate = 96000
ratios = 2
thresholds = 1

import sys, os
sys.path.append(os.path.dirname(os.path.realpath(__file__))+"/..")
from display.compare_spec import plot_me

def filter(inputl, inputr):
  import numpy as np
  outputl = np.zeros(inputl.shape, dtype=np.float64)
  outputr = np.zeros(inputl.shape, dtype=np.float64)

  infilterL = DoubleInPointerFilter(inputl, False)
  infilterL.set_input_sampling_rate(sample_rate)
  infilterR = DoubleInPointerFilter(inputr, False)
  infilterR.set_input_sampling_rate(sample_rate)

  mssplitfilter = DoubleMiddleSideFilter()
  mssplitfilter.set_input_sampling_rate(sample_rate)
  mssplitfilter.set_input_port(0, infilterL, 0)
  mssplitfilter.set_input_port(1, infilterR, 0)

  adaptgainfilter = DoubleVolumeFilter(2)
  adaptgainfilter.set_input_sampling_rate(sample_rate)
  adaptgainfilter.set_input_port(0, mssplitfilter, 0)
  adaptgainfilter.set_input_port(1, mssplitfilter, 1)
  adaptgainfilter.set_volume(.5)

  powerfilter1 = DoublePowerFilter()
  powerfilter1.set_input_sampling_rate(sample_rate)
  powerfilter1.set_input_port(0, adaptgainfilter, 0)
  powerfilter1.set_memory(np.exp(-1/(sample_rate*.1e-3)))

  attackreleasefilter1 = DoubleAttackReleaseFilter()
  attackreleasefilter1.set_input_sampling_rate(sample_rate)
  attackreleasefilter1.set_input_port(0, powerfilter1, 0)
  attackreleasefilter1.set_attack(np.exp(-1/(sample_rate*1e-3)))
  attackreleasefilter1.set_release(np.exp(-1/(sample_rate*100e-3)))

  gainfilter1 = DoubleGainCompressorFilter()
  gainfilter1.set_input_sampling_rate(sample_rate)
  gainfilter1.set_input_port(0, attackreleasefilter1, 0)
  gainfilter1.set_threshold(thresholds)
  gainfilter1.set_ratio(ratios)
  gainfilter1.set_softness(1)

  applygainfilter = DoubleApplyGainFilter(2)
  applygainfilter.set_input_sampling_rate(sample_rate)
  applygainfilter.set_input_port(0, gainfilter1, 0)
  applygainfilter.set_input_port(1, mssplitfilter, 0)

  powerfilter2 = DoublePowerFilter(1)
  powerfilter2.set_input_sampling_rate(sample_rate)
  powerfilter2.set_input_port(0, adaptgainfilter, 1)
  powerfilter2.set_memory(np.exp(-1/(sample_rate*.1e-3)))

  attackreleasefilter2 = DoubleAttackReleaseFilter()
  attackreleasefilter2.set_input_sampling_rate(sample_rate)
  attackreleasefilter2.set_input_port(0, powerfilter1, 0)
  attackreleasefilter2.set_attack(np.exp(-1/(sample_rate*1e-3)))
  attackreleasefilter2.set_release(np.exp(-1/(sample_rate*100e-3)))

  gainfilter2 = DoubleGainCompressorFilter()
  gainfilter2.set_input_sampling_rate(sample_rate)
  gainfilter2.set_input_port(0, attackreleasefilter2, 0)
  gainfilter2.set_threshold(thresholds)
  gainfilter2.set_ratio(ratios)
  gainfilter2.set_softness(1)

  applygainfilter.set_input_port(2, gainfilter2, 0)
  applygainfilter.set_input_port(3, mssplitfilter, 1)

  msmergefilter = DoubleMiddleSideFilter()
  msmergefilter.set_input_sampling_rate(sample_rate)
  msmergefilter.set_input_port(0, applygainfilter, 0)
  msmergefilter.set_input_port(1, applygainfilter, 1)

  volumefilter = DoubleVolumeFilter(2)
  volumefilter.set_input_sampling_rate(sample_rate)
  volumefilter.set_volume(.5)
  volumefilter.set_input_port(0, msmergefilter, 0)
  volumefilter.set_input_port(1, msmergefilter, 1)
  
  outfilterl = DoubleOutPointerFilter(outputl, False)
  outfilterl.set_input_sampling_rate(sample_rate)
  outfilterl.set_input_port(0, volumefilter, 0)

  outfilterr = DoubleOutPointerFilter(outputr, False)
  outfilterr.set_input_sampling_rate(sample_rate)
  outfilterr.set_input_port(0, volumefilter, 1)
  
  pipelineend = PipelineGlobalSinkFilter()
  pipelineend.set_input_sampling_rate(sample_rate)
  pipelineend.add_filter(outfilterl)
  pipelineend.add_filter(outfilterr)
  pipelineend.process(inputl.shape[1])

  return outputl, outputr

if __name__ == "__main__":
  import numpy as np
  samples = 2000000
  freq_max = 20000

  t = np.arange(samples, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(np.pi * (sample_rate * freq_max / samples * (t + .1)) * t)
  dr = d[:,::-1].copy()

  np.savetxt("input.txt", d)
  outl, outr = filter(d, dr)
  np.savetxt("outputl.txt", outl)
  np.savetxt("outputl.txt", outr)
  plt.figure()
  plot_me((d[0], outl[0]), sample_rate)
  plt.gcf().suptitle("Compressor channel L")
  plt.figure()
  plot_me((dr[0], outr[0]), sample_rate)
  plt.gcf().suptitle("Compressor channel R")
  plt.figure()
  plt.plot(t[0,0:1000], d[0,0:1000])
  plt.plot(t[0,0:1000], outl[0,0:1000])
  plt.figure()
  plt.plot(t[0,0:1000], dr[0,0:1000])
  plt.plot(t[0,0:1000], outr[0,0:1000])
  plt.show()
