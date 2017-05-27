#!/usr/bin/env python

from nose.tools import raises

def FloatInPointerFilter_new_test():
  import numpy as np
  from ATK.Core import FloatInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float32)[None,:])
  filter = FloatInPointerFilter(d, False)
  assert filter.nb_output_ports == 1

def DoubleInPointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = DoubleInPointerFilter(d, False)
  assert filter.nb_output_ports == 1

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

