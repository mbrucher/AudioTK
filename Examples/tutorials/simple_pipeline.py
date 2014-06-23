#!/usr/bin/env python

import numpy as np
from scipy.io import wavfile

from ATK.Core import Int16InPointerFilter, Int16OutPointerFilter
from ATK.Tools import FloatMiddleSideFilter, FloatVolumeFilter

sampling_rate, data = wavfile.read("stereofile.wav")

infilter = Int16InPointerFilter(data, True)
infilter.set_output_sampling_rate(sampling_rate)

print infilter.get_nb_output_ports()
assert infilter.get_nb_output_ports() == 2

msfilter = FloatMiddleSideFilter()
msfilter.set_input_sampling_rate(sampling_rate)
msfilter.set_input_port(0, infilter, 0)
msfilter.set_input_port(1, infilter, 1)

volumefilter = FloatVolumeFilter(1)
volumefilter.set_input_sampling_rate(sampling_rate)
volumefilter.set_input_port(0, msfilter, 1)
volumefilter.set_volume(.5)

msmergefilter = FloatMiddleSideFilter()
msmergefilter.set_input_sampling_rate(sampling_rate)
msmergefilter.set_input_port(0, msfilter, 0)
msmergefilter.set_input_port(1, volumefilter, 0)
  
volumefilter2 = FloatVolumeFilter(2)
volumefilter2.set_input_sampling_rate(sampling_rate)
volumefilter2.set_input_port(0, msmergefilter, 0)
volumefilter2.set_input_port(1, msmergefilter, 1)
volumefilter2.set_volume(2)

outdata = np.zeros(data.shape, dtype=np.int16)
outfilter = Int16OutPointerFilter(outdata, True)
outfilter.set_input_sampling_rate(sampling_rate)
outfilter.set_input_port(0, volumefilter2, 0)
outfilter.set_input_port(1, volumefilter2, 1)

outfilter.process(len(data))
wavfile.write("stereofile3.wav", sampling_rate, outdata)
