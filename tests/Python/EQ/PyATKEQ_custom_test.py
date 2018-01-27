#!/usr/bin/env python

from ATK.EQ import DoubleCustomFIRFilter, DoubleCustomIIRFilter

import numpy as np
from nose.tools import raises

sampling = 48000

@raises(ValueError)
def customFIR_bad_dim_test():
  import numpy as np

  filter = DoubleCustomFIRFilter()
  filter.coefficients_in = np.ones(())

@raises(ValueError)
def customFIR_bad_size_test():
  import numpy as np

  filter = DoubleCustomFIRFilter()
  filter.coefficients_in = np.ones((0))

def customFIR_check_coeffs_test():
  import numpy as np
  from numpy.testing import assert_almost_equal

  filter = DoubleCustomFIRFilter()
  filter.coefficients_in = np.ones((10))
  assert_almost_equal(filter.coefficients_in, np.ones((10)))

@raises(ValueError)
def customIIR_bad_dim_test():
  import numpy as np

  filter = DoubleCustomIIRFilter()
  filter.coefficients_in = np.ones(())

@raises(ValueError)
def customIIR_bad_size_test():
  import numpy as np

  filter = DoubleCustomIIRFilter()
  filter.coefficients_in = np.ones((0))

def customIIR_check_coeffs_test():
  import numpy as np
  from numpy.testing import assert_almost_equal

  filter = DoubleCustomIIRFilter()
  filter.coefficients_in = np.ones((10))
  assert_almost_equal(filter.coefficients_in, np.ones((10)))

@raises(ValueError)
def customIIR_bad_dim2_test():
  import numpy as np

  filter = DoubleCustomIIRFilter()
  filter.coefficients_out = np.ones(())

@raises(ValueError)
def customIIR_bad_size2_test():
  import numpy as np

  filter = DoubleCustomIIRFilter()
  filter.coefficients_out = np.ones((0))

def customIIR_check_coeffs2_test():
  import numpy as np
  from numpy.testing import assert_almost_equal

  filter = DoubleCustomIIRFilter()
  filter.coefficients_out = np.ones((10))
  assert_almost_equal(filter.coefficients_out, np.ones((10)))
