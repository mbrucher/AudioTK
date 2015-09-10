#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter, PipelineGlobalSinkFilter

from ATK.Dynamic import DoubleAttackReleaseFilter, DoubleAttackReleaseHysteresisFilter

processsize = 3000
sampling_rate = 44100

data = np.sin(np.arange(processsize) * np.pi * 40 / sampling_rate).reshape(-1, 1)
data = data ** 2
infilter = DoubleInPointerFilter(data, True)
infilter.set_output_sampling_rate(sampling_rate)

attackreleasefilter = DoubleAttackReleaseFilter(1)
attackreleasefilter.set_input_sampling_rate(sampling_rate)
attackreleasefilter.set_input_port(0, infilter, 0)
attackreleasefilter.set_attack(np.exp(-1/(sampling_rate*1e-3)))
attackreleasefilter.set_release(np.exp(-1/(sampling_rate*10e-3)))

outdata = np.zeros((processsize, 1), dtype=np.float64)
outfilter = DoubleOutPointerFilter(outdata, True)
outfilter.set_input_sampling_rate(sampling_rate)
outfilter.set_input_port(0, attackreleasefilter, 0)

attackreleasefilter2 = DoubleAttackReleaseHysteresisFilter(1)
attackreleasefilter2.set_input_sampling_rate(sampling_rate)
attackreleasefilter2.set_input_port(0, infilter, 0)
attackreleasefilter2.set_attack(np.exp(-1/(sampling_rate*1e-3)))
attackreleasefilter2.set_release(np.exp(-1/(sampling_rate*10e-3)))
attackreleasefilter2.set_hysteresis(.5)

outdata2 = np.zeros((processsize, 1), dtype=np.float64)
outfilter_hyst = DoubleOutPointerFilter(outdata2, True)
outfilter_hyst.set_input_sampling_rate(sampling_rate)
outfilter_hyst.set_input_port(0, attackreleasefilter2, 0)

pipelineend = PipelineGlobalSinkFilter()
pipelineend.set_input_sampling_rate(sampling_rate)
pipelineend.add_filter(outfilter)
pipelineend.add_filter(outfilter_hyst)
pipelineend.process(processsize)

start = 0
stop = processsize

x = np.arange(stop, dtype=np.float32) / sampling_rate

plt.figure()
plt.suptitle("Attack Release filters")
plt.plot(x[start:], data[start:stop, 0], label="Original")
plt.plot(x[start:], outdata[start:stop, 0], label="AR filter")
plt.plot(x[start:], outdata2[start:stop, 0], label="AR filter with hysteresis")

plt.legend(loc=4)
plt.show()
