#!/usr/bin/env python

from nose.tools import raises

def Pan_linear_left_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoublePanFilter

  from numpy.testing import assert_almost_equal
  
  t = np.arange(1000, dtype=np.float64)[None, :]
  input = np.sin(t * 1000 * 2 * np.pi / 48000)
  output = np.ascontiguousarray(np.zeros(2000, dtype=np.float64).reshape(2, -1))

  inputfilter = DoubleInPointerFilter(input, False)
  panfilter = DoublePanFilter()
  outputfilter = DoubleOutPointerFilter(output, False)

  inputfilter.output_sampling_rate = 48000
  panfilter.input_sampling_rate = 48000
  panfilter.pan_law = DoublePanFilter.LINEAR_TAPER
  panfilter.pan = -1
  outputfilter.input_sampling_rate = 48000

  panfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, panfilter, 0)
  outputfilter.set_input_port(1, panfilter, 1)

  outputfilter.process(1000)

  assert_almost_equal(input[0], output[0])
  assert_almost_equal(0, output[1])

def Pan_linear_right_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoublePanFilter
  
  from numpy.testing import assert_almost_equal
  
  t = np.arange(1000, dtype=np.float64)[None, :]
  input = np.sin(t * 1000 * 2 * np.pi / 48000)
  output = np.ascontiguousarray(np.zeros(2000, dtype=np.float64).reshape(2, -1))
  
  inputfilter = DoubleInPointerFilter(input, False)
  panfilter = DoublePanFilter()
  outputfilter = DoubleOutPointerFilter(output, False)
  
  inputfilter.output_sampling_rate = 48000
  panfilter.input_sampling_rate = 48000
  panfilter.pan_law = DoublePanFilter.LINEAR_TAPER
  panfilter.pan = 1
  outputfilter.input_sampling_rate = 48000

  
  panfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, panfilter, 0)
  outputfilter.set_input_port(1, panfilter, 1)
  
  outputfilter.process(1000)
  
  assert_almost_equal(input[0], output[1])
  assert_almost_equal(0, output[0])

