#!/usr/bin/env python

from nose.tools import raises

def Decimation_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoubleDecimationFilter

  from numpy.testing import assert_almost_equal
  
  input = np.sin(np.arange(2000, dtype=np.float64)[None,:] * 1000 * 2 * np.pi / 96000)
  output = np.ascontiguousarray(np.zeros(1000, dtype=np.float64)[None,:])

  inputfilter = DoubleInPointerFilter(input, False)
  decimationfilter = DoubleDecimationFilter(1)
  outputfilter = DoubleOutPointerFilter(output, False)

  inputfilter.set_output_sampling_rate(96000)
  decimationfilter.set_input_sampling_rate(96000)
  decimationfilter.set_output_sampling_rate(48000)
  outputfilter.set_input_sampling_rate(48000)

  decimationfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, decimationfilter, 0)

  outputfilter.process(1000)

  assert_almost_equal(input[:,::2], output)

