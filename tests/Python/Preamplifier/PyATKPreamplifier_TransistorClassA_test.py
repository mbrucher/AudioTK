#!/usr/bin/env python

from nose.tools import raises
from nose.plugins.attrib import attr

sampling_rate = 48000 * 4

@attr('Eigen')
def DoubleTransistorClassAFilter_zero_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Preamplifier import DoubleTransistorClassAFilter

  from numpy.testing import assert_almost_equal
  
  input = np.zeros(1000, dtype=np.float64).reshape(1, -1)
  output = np.zeros(1000, dtype=np.float64).reshape(1, -1)

  inputfilter = DoubleInPointerFilter(input, False)
  triodefilter = DoubleTransistorClassAFilter.build_standard_filter()
  outputfilter = DoubleOutPointerFilter(output, False)

  inputfilter.output_sampling_rate = sampling_rate
  triodefilter.input_sampling_rate = sampling_rate
  outputfilter.input_sampling_rate = sampling_rate

  triodefilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, triodefilter, 0)

  outputfilter.process(1000)

  assert_almost_equal(0, output[0])

