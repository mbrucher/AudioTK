#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Dynamic import DoubleAttackReleaseFilter, DoubleGainCompressorFilter, DoublePowerFilter
from ATK.Tools import DoubleApplyGainFilter

sample_rate = 96000

def filter(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate

  powerfilter = DoublePowerFilter(1)
  powerfilter.input_sampling_rate = sample_rate
  powerfilter.set_input_port(0, infilter, 0)
  powerfilter.memory = np.exp(-1/(sample_rate*1e-3))

  attackreleasefilter = DoubleAttackReleaseFilter(1)
  attackreleasefilter.input_sampling_rate = sample_rate
  attackreleasefilter.set_input_port(0, powerfilter, 0)
  attackreleasefilter.attack = np.exp(-1/(sample_rate*1e-3))
  attackreleasefilter.release = np.exp(-1/(sample_rate*100e-3))

  gainfilter = DoubleGainCompressorFilter(1)
  gainfilter.input_sampling_rate = sample_rate
  gainfilter.set_input_port(0, attackreleasefilter, 0)
  gainfilter.threshold = 0.5
  gainfilter.ratio = 4
  gainfilter.softness = 1

  applygainfilter = DoubleApplyGainFilter(1)
  applygainfilter.input_sampling_rate = sample_rate
  applygainfilter.set_input_port(0, gainfilter, 0)
  applygainfilter.set_input_port(1, infilter, 0)

  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.input_sampling_rate = sample_rate
  outfilter.set_input_port(0, applygainfilter, 0)
  outfilter.process(input.shape[1])

  return output

def compressor_test():
  import numpy as np
  from numpy.testing import assert_almost_equal
  
  import os
  dirname = os.path.dirname(__file__)
  
  x = np.fromfile(dirname + os.sep + "input_comp.dat", dtype=np.float64).reshape(1, -1)
  ref = np.fromfile(dirname + os.sep + "output_comp.dat", dtype=np.float64).reshape(1, -1)
  out = filter(x)
  assert_almost_equal(out, ref)

if __name__ == "__main__":
  import numpy as np
  import matplotlib.pyplot as plt
  
  size = 5000

  x = np.arange(size, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(x * 2 * np.pi * 100)

  d.tofile("input_comp.dat")
  out = filter(d)
  out.tofile("output_comp.dat")
  
  import matplotlib.pyplot as plt
  plt.plot(x[0], d[0], label="input")
  plt.plot(x[0], out[0], label="output")
  plt.legend()
  plt.show()
