#!/usr/bin/env python

from nose.tools import raises

def Int32PointerFilter_new_test():
  import numpy as np
  from ATK.Core import Int32InPointerFilter
  d = np.arange(1000, dtype=np.int32)
  filter = Int32InPointerFilter(np.atleast_2d(d), False)
  assert filter.get_nb_output_ports() == 1

def Int64PointerFilter_new_test():
  import numpy as np
  from ATK.Core import Int64InPointerFilter
  d = np.arange(1000, dtype=np.int64)
  filter = Int64InPointerFilter(np.atleast_2d(d), False)
  assert filter.get_nb_output_ports() == 1

def FloatInPointerFilter_new_test():
  import numpy as np
  from ATK.Core import FloatInPointerFilter
  d = np.arange(1000, dtype=np.float32)
  filter = FloatInPointerFilter(np.atleast_2d(d), False)
  assert filter.get_nb_output_ports() == 1

def DoubleInPointerFilter_new_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.arange(1000, dtype=np.float64)
  filter = DoubleInPointerFilter(np.atleast_2d(d), False)
  assert filter.get_nb_output_ports() == 1

@raises(TypeError)
def Int32PointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import Int32InPointerFilter
  d = np.arange(1000, dtype=np.int64)
  filter = Int32InPointerFilter(np.atleast_2d(d), False)
  assert filter.get_nb_output_ports() == 1

@raises(TypeError)
def Int64PointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import Int64InPointerFilter
  d = np.arange(1000, dtype=np.float32)
  filter = Int64InPointerFilter(np.atleast_2d(d), False)
  assert filter.get_nb_output_ports() == 1

@raises(TypeError)
def FloatInPointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import FloatInPointerFilter
  d = np.arange(1000, dtype=np.float64)
  filter = FloatInPointerFilter(np.atleast_2d(d), False)
  assert filter.get_nb_output_ports() == 1

@raises(TypeError)
def DoubleInPointerFilter_new_fail_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter
  d = np.arange(1000, dtype=np.int32)
  filter = DoubleInPointerFilter(np.atleast_2d(d), False)
  assert filter.get_nb_output_ports() == 1
