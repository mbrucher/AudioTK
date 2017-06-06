#!/usr/bin/env python

from nose.tools import raises

def DoubleConvertFilter_new_test():
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

def DoubleConvertFilter2_new_test():
  import numpy as np
  from ATK.Core import DoubleComplexToRealFilter, PipelineGlobalSinkFilter
  from ATK.Core import ComplexDoubleInPointerFilter, DoubleOutPointerFilter
  
  from numpy.testing import assert_equal
  input = np.ascontiguousarray(np.arange(1000, dtype=np.complex128))
  output = np.ascontiguousarray(np.zeros(1000, dtype=np.float64))
  output2 = np.ascontiguousarray(np.zeros(1000, dtype=np.float64))
  
  inputfilter = ComplexDoubleInPointerFilter(input)
  convertFilter = DoubleComplexToRealFilter()
  outputfilter = DoubleOutPointerFilter(output)
  output2filter = DoubleOutPointerFilter(output2)
  
  convertFilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, convertFilter, 0)
  output2filter.set_input_port(0, convertFilter, 1)
  
  inputfilter.output_sampling_rate = 48000
  convertFilter.input_sampling_rate = 48000
  outputfilter.input_sampling_rate = 48000
  output2filter.input_sampling_rate = 48000
  
  sink = PipelineGlobalSinkFilter()
  sink.add_filter(outputfilter)
  sink.add_filter(output2filter)
  sink.input_sampling_rate = 48000
  sink.process(1000)

  assert_equal(input, output)
  assert_equal(0, output2)
