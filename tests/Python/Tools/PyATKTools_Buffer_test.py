#!/usr/bin/env python

import numpy as np

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter,\
    PipelineGlobalSinkFilter
from ATK.Tools import DoubleBufferFilter

# sample rates and sizes
sample_rate = 96000
size = 100

def process(input_l, input_r):
  # Populate the outputs
  output_l = np.zeros(size, dtype=np.float64)
  output_r = np.zeros(size, dtype=np.float64)

  # Create the inputs of the pipeline from the numpy arrays
  infilter_l = DoubleInPointerFilter(input_l, False)
  infilter_l.input_sampling_rate = sample_rate
  infilter_r = DoubleInPointerFilter(input_r, False)
  infilter_r.input_sampling_rate = sample_rate

  # Create the intermediate buffer and connect it to the inputs
  buffer = DoubleBufferFilter(2)
  buffer.input_sampling_rate = sample_rate
  buffer.set_input_port(0, infilter_l, 0)
  buffer.set_input_port(1, infilter_r, 0)

  # Create the outputs and connect them to the buffer
  outfilter_l = DoubleOutPointerFilter(output_l, False)
  outfilter_l.input_sampling_rate = sample_rate
  outfilter_l.set_input_port(0, buffer, 1)

  outfilter_r = DoubleOutPointerFilter(output_r, False)
  outfilter_r.input_sampling_rate = sample_rate
  outfilter_r.set_input_port(0, buffer, 0)

  # Create the sink of the pipeline
  sink = PipelineGlobalSinkFilter()
  sink.input_sampling_rate = sample_rate
  sink.add_filter(outfilter_l)
  sink.add_filter(outfilter_r)

  # Process the pipeline
  sink.process(size)
  return (output_l, output_r)

def buffer_test():
  from numpy.testing import assert_equal
  
  x = np.arange(size, dtype=np.float64) / sample_rate
  # Populate the inputs
  input_l = np.sin(x * 2 * np.pi * 1000)
  input_r = input_l[::-1].copy()

  (output_l, output_r) = process(input_l, input_r)

  assert_equal(output_l, input_r)
  assert_equal(output_r, input_l)


if __name__ == "__main__":
  from matplotlib import pyplot as plt
  
  # x is the time, in an array of size (1, size), as InPointerFilter
  # and OutPointerFilter require a 2D array.
  # The Python wrapper will split the numpy array into pointer,
  # number of channels and size automatically
  x = np.arange(size, dtype=np.float64) / sample_rate
  # Populate the inputs
  input_l = np.sin(x * 2 * np.pi * 1000)
  input_r = input_l[::-1].copy()

  (output_l, output_r) = process(input_l, input_r)

  #Display the results
  ax = plt.subplot(2,1,1)
  ax.plot(x[0], input_l[0], label="Left")
  ax.plot(x[0], input_r[0], label="Right")
  ax.set_title("Input")
  plt.legend()
  ax = plt.subplot(2,1,2)
  ax.plot(x[0], output_l[0], label="Left")
  ax.plot(x[0], output_r[0], label="Right")
  ax.set_title("Output")
  plt.legend()

  plt.show()
