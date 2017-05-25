#!/usr/bin/env python

from nose.tools import raises

def PipelineGlobalSinkFilter_new_test():
  from ATK.Core import PipelineGlobalSinkFilter
  sink = PipelineGlobalSinkFilter()
  sink.set_input_sampling_rate(48000)
  sink.process(100)

def PipelineGlobalSinkFilter_usage_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter, PipelineGlobalSinkFilter
  from numpy.testing import assert_equal
  input = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  output = np.ascontiguousarray(np.zeros(1000, dtype=np.float64)[None,:])
  inputfilter = DoubleInPointerFilter(input, False)
  outputfilter = DoubleOutPointerFilter(output, False)
  outputfilter.set_input_port(0, inputfilter, 0)
  inputfilter.output_sampling_rate = 48000
  outputfilter.input_sampling_rate = 48000
  sink = PipelineGlobalSinkFilter()
  sink.add_filter(outputfilter)
  sink.input_sampling_rate = 48000
  sink.process(1000)
  assert_equal(input, output)

