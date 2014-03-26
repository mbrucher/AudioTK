#!/usr/bin/env python

from nose.tools import raises

def Int32OutPointerFilter_new_test():
  import numpy as np
  from ATK.Core import Int32InPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.int32)[None,:])
  filter = Int32InPointerFilter(d, False)
  assert filter.get_nb_output_ports() == 1

def Int64InPointerFilter_new_test():
  import numpy as np
  from ATK.Core import Int64InPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.int64)[None,:])
  filter = Int64InPointerFilter(d, False)
  assert filter.get_nb_output_ports() == 1

def FloatInPointerFilter_new_test():
  import numpy as np
  from ATK.Core import FloatInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float32)[None,:])
  filter = FloatInPointerFilter(d, False)
  assert filter.get_nb_output_ports() == 1

def DoubleInPointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = DoubleInPointerFilter(d, False)
  assert filter.get_nb_output_ports() == 1

def DoubleIn2PointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64).reshape(2, 500))
  filter = DoubleInPointerFilter(d, False)
  assert filter.get_nb_output_ports() == 2

@raises(TypeError)
def Int32InPointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import Int32InPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.int64)[None,:])
  filter = Int32InPointerFilter(d, False)

@raises(TypeError)
def Int64InPointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import Int64InPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float32)[None,:])
  filter = Int64InPointerFilter(d, False)

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

def Int32OutPointerFilter_new_test():
  import numpy as np
  from ATK.Core import Int32OutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.int32)[None,:])
  filter = Int32OutPointerFilter(d, False)
  assert filter.get_nb_input_ports() == 1

def Int64OutPointerFilter_new_test():
  import numpy as np
  from ATK.Core import Int64OutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.int64)[None,:])
  filter = Int64OutPointerFilter(d, False)
  assert filter.get_nb_input_ports() == 1

def FloatOutPointerFilter_new_test():
  import numpy as np
  from ATK.Core import FloatOutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float32)[None,:])
  filter = FloatOutPointerFilter(d, False)
  assert filter.get_nb_input_ports() == 1

def DoubleOutPointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleOutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64)[None,:])
  filter = DoubleOutPointerFilter(d, False)
  assert filter.get_nb_input_ports() == 1

def DoubleOut2PointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleOutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float64).reshape(2, 500))
  filter = DoubleOutPointerFilter(d, False)
  assert filter.get_nb_input_ports() == 2

@raises(TypeError)
def Int32OutPointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import Int32OutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.int64)[None,:])
  filter = Int32OutPointerFilter(d, False)

@raises(TypeError)
def Int64OutPointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import Int64OutPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.float32)[None,:])
  filter = Int64OutPointerFilter(d, False)

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
  inputfilter.set_output_sampling_rate(48000)
  outputfilter.set_input_sampling_rate(48000)
  outputfilter.process(1000)
  assert_equal(input, output)

