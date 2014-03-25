#!/usr/bin/env python

from nose.tools import raises

def Int32PointerFilter_new_test():
  import numpy as np
  from ATK.Core import Int32InPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.int32)[None,:])
  print d.shape
  filter = Int32InPointerFilter(d, False)
  assert filter.get_nb_output_ports() == 1

def Int64PointerFilter_new_test():
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

@raises(TypeError)
def Int32PointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import Int32InPointerFilter
  d = np.ascontiguousarray(np.arange(1000, dtype=np.int64)[None,:])
  filter = Int32InPointerFilter(d, False)

@raises(TypeError)
def Int64PointerFilter_new_fail_test():
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
