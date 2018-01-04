#!/usr/bin/env python

from nose.tools import raises
from numpy import testing

def FloatInPointerFilter_new_test():
  import numpy as np
  from ATK.Core import FloatInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float32)[None,:])
  filter = FloatInPointerFilter(d, False)
  assert filter.nb_output_ports == 1

def FloatInPointerFilter_simple_new_test():
  import numpy as np
  from ATK.Core import FloatInPointerFilter
  d = np.arange(1000, dtype=np.float32)
  filter = FloatInPointerFilter(d)
  assert filter.nb_output_ports == 1

def DoubleInPointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = DoubleInPointerFilter(d, False)
  assert filter.nb_output_ports == 1

def DoubleInPointerFilter_assign_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = DoubleInPointerFilter(d, False)
  filter.set_pointer(d)
  assert filter.nb_output_ports == 1

def DoubleInPointerFilter_retrieve_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = DoubleInPointerFilter(d, False)
  filter.input_sampling_rate = 48000
  filter.process(1000)
  out = filter.get_output_array(0)
  testing.assert_array_equal(d[0], out)

@raises(ValueError)
def DoubleInPointerFilter_wrong_retrieve_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = DoubleInPointerFilter(d, False)
  filter.input_sampling_rate = 48000
  filter.process(1000)
  filter.get_output_array(1)

def DoubleIn2PointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64).reshape(2, 500))
  filter = DoubleInPointerFilter(d, False)
  assert filter.nb_output_ports == 2

@raises(TypeError)
def FloatInPointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import FloatInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = FloatInPointerFilter(d, False)

@raises(TypeError)
def DoubleInPointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.int32)[None,:])
  filter = DoubleInPointerFilter(d, False)

def FloatOutPointerFilter_new_test():
  import numpy as np
  from ATK.Core import FloatOutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float32)[None,:])
  filter = FloatOutPointerFilter(d, False)
  assert filter.nb_input_ports == 1

def DoubleOutPointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleOutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = DoubleOutPointerFilter(d, False)
  assert filter.nb_input_ports == 1

def DoubleOut2PointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleOutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64).reshape(2, 500))
  filter = DoubleOutPointerFilter(d, False)
  assert filter.nb_input_ports == 2

def DoubleOutPointerFilter_assign_test():
  import numpy as np
  from ATK.Core import DoubleOutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = DoubleOutPointerFilter(d, False)
  filter.set_pointer(d)

@raises(TypeError)
def FloatOutPointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import FloatOutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = FloatOutPointerFilter(d, False)

@raises(TypeError)
def DoubleOutPointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import DoubleOutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.int32)[None,:])
  filter = DoubleOutPointerFilter(d, False)

def DoublePointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from numpy.testing import assert_equal
  input = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  output = np.ascontiguousarray(np.zeros(1000, dtype=np.float64)[None,:])
  inputfilter = DoubleInPointerFilter(input, False)
  outputfilter = DoubleOutPointerFilter(output, False)
  outputfilter.set_input_port(0, inputfilter, 0)
  inputfilter.output_sampling_rate = 48000
  outputfilter.input_sampling_rate = 48000
  outputfilter.process(1000)
  assert_equal(input, output)


def DoublePointerFilter2_new_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from numpy.testing import assert_equal
  input = np.arange(1000, dtype=np.float64)
  output = np.zeros(1000, dtype=np.float64)
  inputfilter = DoubleInPointerFilter(input)
  outputfilter = DoubleOutPointerFilter(output)
  outputfilter.set_input_port(0, inputfilter, 0)
  inputfilter.output_sampling_rate = 48000
  outputfilter.input_sampling_rate = 48000
  outputfilter.process(1000)
  assert_equal(input, output)

