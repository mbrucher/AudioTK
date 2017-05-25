#!/usr/bin/env python

from nose.tools import raises

def Sum_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoubleSumFilter

  from numpy.testing import assert_almost_equal
  
  t = np.arange(1000, dtype=np.float64)
  input = np.sin(np.array((t, t)) * 1000 * 2 * np.pi / 48000)
  output = np.ascontiguousarray(np.zeros(1000, dtype=np.float64)[None,:])

  inputfilter = DoubleInPointerFilter(input, False)
  sumfilter = DoubleSumFilter()
  outputfilter = DoubleOutPointerFilter(output, False)

  inputfilter.output_sampling_rate = 48000
  sumfilter.input_sampling_rate = 48000
  outputfilter.input_sampling_rate = 48000

  sumfilter.set_input_port(0, inputfilter, 0)
  sumfilter.set_input_port(1, inputfilter, 1)
  outputfilter.set_input_port(0, sumfilter, 0)

  outputfilter.process(1000)

  assert_almost_equal(2*input[0], output[0])

