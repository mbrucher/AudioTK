#!/usr/bin/env python

from nose.tools import raises

def Volume_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoubleVolumeFilter

  from numpy.testing import assert_almost_equal
  
  input = np.sin(np.arange(1000, dtype=np.float64)[None,:] * 1000 * 2 * np.pi / 48000)
  output = np.ascontiguousarray(np.zeros(1000, dtype=np.float64)[None,:])

  inputfilter = DoubleInPointerFilter(input, False)
  volumefilter = DoubleVolumeFilter()
  outputfilter = DoubleOutPointerFilter(output, False)

  inputfilter.set_output_sampling_rate(48000)
  volumefilter.set_input_sampling_rate(48000)
  volumefilter.set_volume(.5)
  outputfilter.set_input_sampling_rate(48000)

  volumefilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, volumefilter, 0)

  outputfilter.process(1000)

  assert_almost_equal(.5 * input, output)

