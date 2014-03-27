#!/usr/bin/env python

from nose.tools import raises

def Oversampling_2_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoubleOversampling6points5order_2Filter

  from numpy.testing import assert_almost_equal
  
  ref = np.sin(np.arange(2000, dtype=np.float64)[None,:] * 1000 * 2 * np.pi / 96000)
  input = np.ascontiguousarray(ref[:, ::2])
  output = np.ascontiguousarray(np.zeros(2000, dtype=np.float64)[None,:])

  inputfilter = DoubleInPointerFilter(input, False)
  oversamplingfilter = DoubleOversampling6points5order_2Filter()
  outputfilter = DoubleOutPointerFilter(output, False)

  inputfilter.set_output_sampling_rate(48000)
  oversamplingfilter.set_input_sampling_rate(48000)
  oversamplingfilter.set_output_sampling_rate(96000)
  outputfilter.set_input_sampling_rate(96000)

  oversamplingfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, oversamplingfilter, 0)

  outputfilter.process(2000)

  assert_almost_equal(ref[:,1495:-5], output[:,1500:], decimal=1)

