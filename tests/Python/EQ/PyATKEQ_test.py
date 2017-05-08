#!/usr/bin/env python

from nose.tools import raises

def import_test():
  from ATK import EQ

def DoubleBandPassCoefficientsIIRFilter_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.EQ import DoubleSecondOrderBandPassFilter

  from numpy.testing import assert_almost_equal
  
  input = np.sin(np.arange(1000, dtype=np.float64)[None,:] * 1000 * 2 * np.pi / 48000)
  output = np.ascontiguousarray(np.zeros(1000, dtype=np.float64)[None,:])

  inputfilter = DoubleInPointerFilter(input, False)
  EQfilter = DoubleSecondOrderBandPassFilter()
  outputfilter = DoubleOutPointerFilter(output, False)

  inputfilter.set_output_sampling_rate(48000)
  EQfilter.set_input_sampling_rate(48000)
  EQfilter.set_Q(1)
  EQfilter.set_cut_frequency(1000)
  outputfilter.set_input_sampling_rate(48000)

  EQfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, EQfilter, 0)

  outputfilter.process(1000)

  assert_almost_equal(input[0,500:], input[0,500] / output[0,500] * output[0,500:])

