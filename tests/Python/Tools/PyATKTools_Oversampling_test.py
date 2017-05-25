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
  
  inputfilter.output_sampling_rate = 48000
  oversamplingfilter.input_sampling_rate = 48000
  oversamplingfilter.output_sampling_rate = 96000
  outputfilter.input_sampling_rate = 96000
  
  oversamplingfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, oversamplingfilter, 0)
  
  outputfilter.process(2000)

  assert_almost_equal(ref[:,994:-6], output[:,1000:], decimal=1)

def Oversampling_4_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoubleOversampling6points5order_4Filter
  
  from numpy.testing import assert_almost_equal
  
  ref = np.sin(np.arange(4000, dtype=np.float64)[None,:] * 1000 * 2 * np.pi / 192000)
  input = np.ascontiguousarray(ref[:, ::4])
  output = np.ascontiguousarray(np.zeros(4000, dtype=np.float64)[None,:])
  
  inputfilter = DoubleInPointerFilter(input, False)
  oversamplingfilter = DoubleOversampling6points5order_4Filter()
  outputfilter = DoubleOutPointerFilter(output, False)
  
  inputfilter.output_sampling_rate = 48000
  oversamplingfilter.input_sampling_rate = 48000
  oversamplingfilter.output_sampling_rate = 192000
  outputfilter.input_sampling_rate = 192000
  
  oversamplingfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, oversamplingfilter, 0)
  
  outputfilter.process(4000)

  assert_almost_equal(ref[:,988:-12], output[:,1000:], decimal=1)

def Oversampling_8_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoubleOversampling6points5order_8Filter
  
  from numpy.testing import assert_almost_equal
  
  ref = np.sin(np.arange(8000, dtype=np.float64)[None,:] * 1000 * 2 * np.pi / 384000)
  input = np.ascontiguousarray(ref[:, ::8])
  output = np.ascontiguousarray(np.zeros(8000, dtype=np.float64)[None,:])
  
  inputfilter = DoubleInPointerFilter(input, False)
  oversamplingfilter = DoubleOversampling6points5order_8Filter()
  outputfilter = DoubleOutPointerFilter(output, False)
  
  inputfilter.output_sampling_rate = 48000
  oversamplingfilter.input_sampling_rate = 48000
  oversamplingfilter.output_sampling_rate = 384000
  outputfilter.input_sampling_rate = 384000
  
  oversamplingfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, oversamplingfilter, 0)
  
  outputfilter.process(8000)
  
  assert_almost_equal(ref[:,976:-24], output[:,1000:], decimal=1)

def Oversampling_16_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoubleOversampling6points5order_16Filter
  
  from numpy.testing import assert_almost_equal
  
  ref = np.sin(np.arange(16000, dtype=np.float64)[None,:] * 1000 * 2 * np.pi / 768000)
  input = np.ascontiguousarray(ref[:, ::16])
  output = np.ascontiguousarray(np.zeros(16000, dtype=np.float64)[None,:])
  
  inputfilter = DoubleInPointerFilter(input, False)
  oversamplingfilter = DoubleOversampling6points5order_16Filter()
  outputfilter = DoubleOutPointerFilter(output, False)
  
  inputfilter.output_sampling_rate = 48000
  oversamplingfilter.input_sampling_rate = 48000
  oversamplingfilter.output_sampling_rate = 768000
  outputfilter.input_sampling_rate = 768000

  
  oversamplingfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, oversamplingfilter, 0)
  
  outputfilter.process(16000)

  assert_almost_equal(ref[:,952:-48], output[:,1000:], decimal=1)


def Oversampling_32_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoubleOversampling6points5order_32Filter
  
  from numpy.testing import assert_almost_equal
  
  ref = np.sin(np.arange(32000, dtype=np.float64)[None,:] * 1000 * 2 * np.pi / (2*768000))
  input = np.ascontiguousarray(ref[:, ::32])
  output = np.ascontiguousarray(np.zeros(32000, dtype=np.float64)[None,:])
  
  inputfilter = DoubleInPointerFilter(input, False)
  oversamplingfilter = DoubleOversampling6points5order_32Filter()
  outputfilter = DoubleOutPointerFilter(output, False)
  
  inputfilter.output_sampling_rate = 48000
  oversamplingfilter.input_sampling_rate = 48000
  oversamplingfilter.output_sampling_rate = 32*48000
  outputfilter.input_sampling_rate = 32*48000

  
  oversamplingfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, oversamplingfilter, 0)
  
  outputfilter.process(32000)
  
  assert_almost_equal(ref[:,904:-96], output[:,1000:], decimal=1)

