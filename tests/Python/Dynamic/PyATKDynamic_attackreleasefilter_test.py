#!/usr/bin/env python

import numpy as np

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter, PipelineGlobalSinkFilter
from ATK.Dynamic import DoubleAttackReleaseFilter, DoubleAttackReleaseHysteresisFilter

processsize = 3000
sampling_rate = 44100

def filter(input):
  infilter = DoubleInPointerFilter(input)
  infilter.output_sampling_rate = sampling_rate
  
  attackreleasefilter = DoubleAttackReleaseFilter(1)
  attackreleasefilter.input_sampling_rate = sampling_rate
  attackreleasefilter.set_input_port(0, infilter, 0)
  attackreleasefilter.attack = np.exp(-1/(sampling_rate*1e-3))
  attackreleasefilter.release = np.exp(-1/(sampling_rate*10e-3))
  
  outdata = np.zeros(processsize, dtype=np.float64)
  outfilter = DoubleOutPointerFilter(outdata)
  outfilter.input_sampling_rate = sampling_rate
  outfilter.set_input_port(0, attackreleasefilter, 0)
  
  attackreleasefilter2 = DoubleAttackReleaseHysteresisFilter(1)
  attackreleasefilter2.input_sampling_rate = sampling_rate
  attackreleasefilter2.set_input_port(0, infilter, 0)
  attackreleasefilter2.attack = np.exp(-1/(sampling_rate*1e-3))
  attackreleasefilter2.release = np.exp(-1/(sampling_rate*10e-3))
  attackreleasefilter2.release_hysteresis = .5
  attackreleasefilter2.attack_hysteresis = .9
  
  outdata2 = np.zeros(processsize, dtype=np.float64)
  outfilter_hyst = DoubleOutPointerFilter(outdata2)
  outfilter_hyst.input_sampling_rate = sampling_rate
  outfilter_hyst.set_input_port(0, attackreleasefilter2, 0)
  
  pipelineend = PipelineGlobalSinkFilter()
  pipelineend.input_sampling_rate = sampling_rate
  pipelineend.add_filter(outfilter)
  pipelineend.add_filter(outfilter_hyst)
  pipelineend.process(processsize)
  
  return outdata, outdata2

def ar_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_ar.dat", dtype=np.float64)
  ref = np.fromfile(dirname + os.sep + "output_ar.dat", dtype=np.float64)
  ref2 = np.fromfile(dirname + os.sep + "output2_ar.dat", dtype=np.float64)
  outdata, outdata2 = filter(x)
  assert_almost_equal(outdata, ref)
  assert_almost_equal(outdata2, ref2)

if __name__ == "__main__":
  import matplotlib.pyplot as plt

  x = np.arange(processsize, dtype=np.float64) / sampling_rate
  
  data = np.sin(x * np.pi * 40)
  data = data ** 2
  data.tofile("input_ar.dat")

  outdata, outdata2 = filter(data)
  outdata.tofile("output_ar.dat")
  outdata2.tofile("output2_ar.dat")

  plt.figure()
  plt.suptitle("Attack Release filters")
  plt.plot(x, data, label="Original")
  plt.plot(x, outdata, label="AR filter")
  plt.plot(x, outdata2, label="AR filter with hysteresis (0.9, 0.5)")
  
  plt.legend(loc=4)
  plt.show()
