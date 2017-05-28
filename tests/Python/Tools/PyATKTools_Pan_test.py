#!/usr/bin/env python

from nose.tools import raises

def Pan_linear_left_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoublePanFilter

  from numpy.testing import assert_almost_equal
  
  t = np.arange(1000, dtype=np.float64)[None, :]
  input = np.sin(t * 1000 * 2 * np.pi / 48000)
  output = np.ascontiguousarray(np.zeros(2000, dtype=np.float64).reshape(2, -1))

  inputfilter = DoubleInPointerFilter(input, False)
  panfilter = DoublePanFilter()
  outputfilter = DoubleOutPointerFilter(output, False)

  inputfilter.output_sampling_rate = 48000
  panfilter.input_sampling_rate = 48000
  panfilter.pan_law = DoublePanFilter.LINEAR_TAPER
  panfilter.pan = -1
  outputfilter.input_sampling_rate = 48000

  panfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, panfilter, 0)
  outputfilter.set_input_port(1, panfilter, 1)

  outputfilter.process(1000)

  assert_almost_equal(input[0], output[0])
  assert_almost_equal(0, output[1])

def Pan_linear_right_test():
  import numpy as np
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
  from ATK.Tools import DoublePanFilter
  
  from numpy.testing import assert_almost_equal
  
  t = np.arange(1000, dtype=np.float64)[None, :]
  input = np.sin(t * 1000 * 2 * np.pi / 48000)
  output = np.ascontiguousarray(np.zeros(2000, dtype=np.float64).reshape(2, -1))
  
  inputfilter = DoubleInPointerFilter(input, False)
  panfilter = DoublePanFilter()
  outputfilter = DoubleOutPointerFilter(output, False)
  
  inputfilter.output_sampling_rate = 48000
  panfilter.input_sampling_rate = 48000
  panfilter.pan_law = DoublePanFilter.LINEAR_TAPER
  panfilter.pan = 1
  outputfilter.input_sampling_rate = 48000

  
  panfilter.set_input_port(0, inputfilter, 0)
  outputfilter.set_input_port(0, panfilter, 0)
  outputfilter.set_input_port(1, panfilter, 1)
  
  outputfilter.process(1000)
  
  assert_almost_equal(input[0], output[1])
  assert_almost_equal(0, output[0])

# sample rates and sizes
sample_rate = 96000
size = 101

def process(pan_values, law):
  import numpy as np
  
  from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter, PipelineGlobalSinkFilter
  from ATK.Tools import DoublePanFilter
  
  # Here we only populate ones and we will change the panlaw
  # for each sample
  input = np.ones(size, dtype=np.float64)
  # Populate the outputs
  output_l = np.zeros(size, dtype=np.float64)
  output_r = np.zeros(size, dtype=np.float64)
  
  # Create the inputs of the pipeline from the numpy arrays
  infilter = DoubleInPointerFilter(input, False)
  infilter.input_sampling_rate = sample_rate
  
  # Create the intermediate buffer and connect it to the inputs
  pan = DoublePanFilter()
  pan.input_sampling_rate = sample_rate
  pan.pan_law = law
  pan.set_input_port(0, infilter, 0)
  
  # Create the outputs and connect them to the pan filter
  outfilter_l = DoubleOutPointerFilter(output_l, False)
  outfilter_l.input_sampling_rate = sample_rate
  outfilter_l.set_input_port(0, pan, 0)
  
  outfilter_r = DoubleOutPointerFilter(output_r, False)
  outfilter_r.input_sampling_rate = sample_rate
  outfilter_r.set_input_port(0, pan, 1)
  
  # Create the sink of the pipeline
  sink = PipelineGlobalSinkFilter()
  sink.input_sampling_rate = sample_rate
  sink.add_filter(outfilter_l)
  sink.add_filter(outfilter_r)
  
  for i in range(size):
    pan.pan = pan_values[i]
    # Process the pipeline
    sink.process(1)
  
  return (output_l, output_r)

def PanFilter_display_test():
  import numpy as np
  from ATK.Tools import DoublePanFilter

  pan_values = np.linspace(-1., 1., size)
  
  process(pan_values, DoublePanFilter.SINCOS_0_CENTER)
  process(pan_values, DoublePanFilter.SINCOS_3_CENTER)
  process(pan_values, DoublePanFilter.SQUARE_0_CENTER)
  process(pan_values, DoublePanFilter.SQUARE_3_CENTER)
  process(pan_values, DoublePanFilter.LINEAR_TAPER)
  process(pan_values, DoublePanFilter.BALANCE)

def get_pan(pan_values, law):
  from matplotlib import pyplot as plt
  
  (output_l, output_r) = process(pan_values, law)
  
  #Display the results
  plt.figure()
  plt.plot(pan_values, output_l[0], label="Left")
  plt.plot(pan_values, output_r[0], label="Right")
  plt.plot(pan_values, output_l[0]**2 + output_r[0]**2, label="Power")
  plt.legend()

if __name__ == "__main__":
  import numpy as np
  from ATK.Tools import DoublePanFilter

  pan_values = np.linspace(-1., 1., size)

  get_pan(pan_values, DoublePanFilter.SINCOS_0_CENTER)
  get_pan(pan_values, DoublePanFilter.SINCOS_3_CENTER)
  get_pan(pan_values, DoublePanFilter.SQUARE_0_CENTER)
  get_pan(pan_values, DoublePanFilter.SQUARE_3_CENTER)
  get_pan(pan_values, DoublePanFilter.LINEAR_TAPER)
  get_pan(pan_values, DoublePanFilter.BALANCE)

  plt.show()
