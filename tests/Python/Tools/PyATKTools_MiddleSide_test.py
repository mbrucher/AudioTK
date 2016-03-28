#!/usr/bin/env python

from nose.tools import raises

def MiddleSide_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoubleMiddleSideFilter

  from numpy.testing import assert_almost_equal
  
  t = np.arange(1000, dtype=np.float64)
  input = np.sin(np.array((t, t)) * 1000 * 2 * np.pi / 48000)
  output = np.ascontiguousarray(np.zeros(2000, dtype=np.float64).reshape(2, -1))

  inputfilter = DoubleInPointerFilter(input, False)
  msfilter = DoubleMiddleSideFilter()
  outputfilter = DoubleOutPointerFilter(output, False)

  inputfilter.set_output_sampling_rate(48000)
  msfilter.set_input_sampling_rate(48000)
  outputfilter.set_input_sampling_rate(48000)

  msfilter.set_input_port(0, inputfilter, 0)
  msfilter.set_input_port(1, inputfilter, 1)
  outputfilter.set_input_port(0, msfilter, 0)
  outputfilter.set_input_port(1, msfilter, 1)

  outputfilter.process(1000)

  assert_almost_equal(input[0]*2, output[0])
  assert_almost_equal(0, output[1])

