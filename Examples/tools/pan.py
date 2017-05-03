#!/usr/bin/env python

from matplotlib import pyplot as plt
import numpy as np

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter,\
  PipelineGlobalSinkFilter
from ATK.Tools import DoublePanFilter

# sample rates and sizes
sample_rate = 96000
size = 101

pan_values = np.linspace(-1., 1., size)

def get_pan(law):
  # Here we only populate ones and we will change the panlaw
  # for each sample
  input = np.ones(size, dtype=np.float64).reshape(1, -1)
  # Populate the outputs
  output_l = np.zeros((1, size), dtype=np.float64)
  output_r = np.zeros((1, size), dtype=np.float64)

  # Create the inputs of the pipeline from the numpy arrays
  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(sample_rate)

  # Create the intermediate buffer and connect it to the inputs
  pan = DoublePanFilter()
  pan.set_input_sampling_rate(sample_rate)
  pan.set_input_port(0, infilter, 0)
  pan.set_pan_law(law)

  # Create the outputs and connect them to the pan filter
  outfilter_l = DoubleOutPointerFilter(output_l, False)
  outfilter_l.set_input_sampling_rate(sample_rate)
  outfilter_l.set_input_port(0, pan, 0)

  outfilter_r = DoubleOutPointerFilter(output_r, False)
  outfilter_r.set_input_sampling_rate(sample_rate)
  outfilter_r.set_input_port(0, pan, 1)

  # Create the sink of the pipeline
  sink = PipelineGlobalSinkFilter()
  sink.set_input_sampling_rate(sample_rate)
  sink.add_filter(outfilter_l)
  sink.add_filter(outfilter_r)

  for i in range(size):
    pan.set_pan(pan_values[i])
    # Process the pipeline
    sink.process(1)
  
  #Display the results
  plt.figure()
  plt.plot(pan_values, output_l[0], label="Left")
  plt.plot(pan_values, output_r[0], label="Right")
  plt.plot(pan_values, output_l[0]**2 + output_r[0]**2, label="Power")
  plt.legend()

get_pan(DoublePanFilter.PAN_LAWS_SINCOS_0_CENTER)
get_pan(DoublePanFilter.PAN_LAWS_SINCOS_3_CENTER)
get_pan(DoublePanFilter.PAN_LAWS_SQUARE_0_CENTER)
get_pan(DoublePanFilter.PAN_LAWS_SQUARE_3_CENTER)
get_pan(DoublePanFilter.PAN_LAWS_LINEAR_TAPER)
get_pan(DoublePanFilter.PAN_LAWS_BALANCE)

plt.show()
