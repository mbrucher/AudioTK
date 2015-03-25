#!/usr/bin/env python

import numpy as np
from scipy.io import wavfile
import matplotlib.pyplot as plt

from ATK.Core import Int16InPointerFilter, FloatOutPointerFilter, PipelineGlobalSinkFilter

from ATK.Dynamic import DoubleAttackReleaseFilter, DoubleGainCompressorFilter, DoubleRelativePowerFilter
from ATK.Tools import DoubleApplyGainFilter, DoubleDerivativeFilter

# get from http://www.telefunken-elektroakustik.com/download/brew/

filename = "Boom-Kick.wav"
sampling_rate, data = wavfile.read(filename)
processsize = len(data)

data = data.reshape(-1, 1)
infilter = Int16InPointerFilter(data, True)
infilter.set_output_sampling_rate(sampling_rate)

derivativefilter = DoubleDerivativeFilter()
derivativefilter.set_input_sampling_rate(sampling_rate)
derivativefilter.set_input_port(0, infilter, 0)

powerfilter = DoubleRelativePowerFilter(1)
powerfilter.set_input_sampling_rate(sampling_rate)
powerfilter.set_input_port(0, derivativefilter, 0)
powerfilter.set_memory(np.exp(-1/(sampling_rate*.1e-3)))

attackreleasefilter = DoubleAttackReleaseFilter(1)
attackreleasefilter.set_input_sampling_rate(sampling_rate)
attackreleasefilter.set_input_port(0, powerfilter, 0)
attackreleasefilter.set_attack(np.exp(-1/(sampling_rate*.1e-3)))
attackreleasefilter.set_release(np.exp(-1/(sampling_rate*1.e-3)))

gainfilter = DoubleGainCompressorFilter(1)
gainfilter.set_input_sampling_rate(sampling_rate)
gainfilter.set_input_port(0, attackreleasefilter, 0)
gainfilter.set_threshold(1)
gainfilter.set_ratio(.7)
gainfilter.set_softness(1)

applygainfilter = DoubleApplyGainFilter(1)
applygainfilter.set_input_sampling_rate(sampling_rate)
applygainfilter.set_input_port(0, gainfilter, 0)
applygainfilter.set_input_port(1, infilter, 0)

indata = np.zeros((processsize, 1), dtype=np.float32)
inputfilter = FloatOutPointerFilter(indata, True)
inputfilter.set_input_sampling_rate(sampling_rate)
inputfilter.set_input_port(0, infilter, 0)

outdata = np.zeros((processsize, 1), dtype=np.float32)
outfilter = FloatOutPointerFilter(outdata, True)
outfilter.set_input_sampling_rate(sampling_rate)
outfilter.set_input_port(0, applygainfilter, 0)

outdata_power = np.zeros((processsize, 1), dtype=np.float32)
outfilter_power = FloatOutPointerFilter(outdata_power, True)
outfilter_power.set_input_sampling_rate(sampling_rate)
outfilter_power.set_input_port(0, powerfilter, 0)

outdata_gain = np.zeros((processsize, 1), dtype=np.float32)
outfilter_gain = FloatOutPointerFilter(outdata_gain, True)
outfilter_gain.set_input_sampling_rate(sampling_rate)
outfilter_gain.set_input_port(0, gainfilter, 0)

pipelineend = PipelineGlobalSinkFilter()
pipelineend.set_input_sampling_rate(sampling_rate)
pipelineend.add_filter(inputfilter)
pipelineend.add_filter(outfilter)
pipelineend.add_filter(outfilter_power)
pipelineend.add_filter(outfilter_gain)
pipelineend.process(processsize)

start = 0
stop = 1000

x = np.arange(stop, dtype=np.float32) / sampling_rate

plt.figure()
plt.suptitle("Transient Shaper (derivative-based)")
plt.subplot(4, 1, 1)
plt.title("Input")
plt.plot(x[start:], indata[start:stop, 0])

plt.subplot(4, 1, 2)
plt.title("Relative Power")
plt.plot(x[start:], outdata_power[start:stop, 0])

plt.subplot(4, 1, 3)
plt.title("Gain")
plt.plot(x[start:], outdata_gain[start:stop, 0])

plt.subplot(4, 1, 4)
plt.title("Output")
plt.plot(x[start:], outdata[start:stop, 0])

plt.show()
