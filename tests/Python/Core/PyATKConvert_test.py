#!/usr/bin/env python

from nose.tools import raises

def FloatConvertFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleRealToComplexFilter
  from ATK.Core import DoubleInPointerFilter, ComplexDoubleOutPointerFilter
  
  from numpy.testing import assert_equal
  input = np.ascontiguousarray(np.arange(1000, dtype=np.float64))
  output = np.ascontiguousarray(np.zeros(1000, dtype=np.complex128))
  
  inputfilter = DoubleInPointerFilter(input)
  convertFilter = DoubleRealToComplexFilter()
  outputfilter = ComplexDoubleOutPointerFilter(output)
  
  convertFilter.set_input_port(0, inputfilter, 0)
  convertFilter.set_input_port(1, inputfilter, 0)
  outputfilter.set_input_port(0, convertFilter, 0)
  
  inputfilter.output_sampling_rate = 48000
  convertFilter.input_sampling_rate = 48000
  outputfilter.input_sampling_rate = 48000
  
  outputfilter.process(1000)
  assert_equal(input + 1j * input, output)
