#!/usr/bin/env python

from matplotlib import pyplot as plt
import numpy as np

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleVolumeFilter

# sample rates and sizes
sample_rate = 96000
size = 100

# x is the time, in an array of size (1, size), as InPointerFilter
# and OutPointerFilter require a 2D array.
# The Python wrapper will split the numpy array into pointer, 
# number of channels and size automatically
x = np.arange(size, dtype=np.float64).reshape(1, -1) / sample_rate
# Populate the inputs
input = np.sin(x * 2 * np.pi * 1000)
# Populate the outputs
output = np.zeros((1, size), dtype=np.float64)

# Create the inputs of the pipeline from the numpy arrays
infilter = DoubleInPointerFilter(input, False)
infilter.set_input_sampling_rate(sample_rate)

# Create the intermediate buffer and connect it to the inputs
volume = DoubleVolumeFilter(1)
volume.set_input_sampling_rate(sample_rate)
volume.set_input_port(0, infilter, 0)
volume.set_volume(10)

# Create the outputs and connect them to the buffer
outfilter = DoubleOutPointerFilter(output, False)
outfilter.set_input_sampling_rate(sample_rate)
outfilter.set_input_port(0, volume, 0)

# Process the pipeline
outfilter.process(size)

#Display the results
plt.plot(x[0], input[0], label="input")
plt.plot(x[0], output[0], label="output")
plt.legend()
plt.show()
