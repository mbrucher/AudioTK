#!/usr/bin/env python

import numpy as np
from scipy.io import wavfile
import matplotlib.pyplot as plt

from ATK.Core import Int16InPointerFilter, FloatOutPointerFilter, PipelineGlobalSinkFilter

from ATK.Dynamic import DoubleAttackReleaseFilter, DoubleGainCompressorFilter, DoublePowerFilter
from ATK.Tools import DoubleApplyGainFilter, DoubleVolumeFilter, DoubleSumFilter

# get from http://www.telefunken-elektroakustik.com/download/brew/

filename = "Break Ca-01.wav"
sampling_rate, data = wavfile.read(filename)
processsize = len(data)

data = data.reshape(-1, 1)
infilter = Int16InPointerFilter(data, True)
infilter.set_output_sampling_rate(sampling_rate)

powerfilter = DoublePowerFilter(1)
powerfilter.set_input_sampling_rate(sampling_rate)
powerfilter.set_input_port(0, infilter, 0)
powerfilter.set_memory(np.exp(-1/(sampling_rate*1e-3)))

fastattackreleasefilter = DoubleAttackReleaseFilter(1)
fastattackreleasefilter.set_input_sampling_rate(sampling_rate)
fastattackreleasefilter.set_input_port(0, powerfilter, 0)
fastattackreleasefilter.set_attack(np.exp(-1/(sampling_rate*1e-3)))
fastattackreleasefilter.set_release(np.exp(-1/(sampling_rate*50.e-3)))

slowattackreleasefilter = DoubleAttackReleaseFilter(1)
slowattackreleasefilter.set_input_sampling_rate(sampling_rate)
slowattackreleasefilter.set_input_port(0, powerfilter, 0)
slowattackreleasefilter.set_attack(np.exp(-1/(sampling_rate*5e-3)))
slowattackreleasefilter.set_release(np.exp(-1/(sampling_rate*50.e-3)))

volumefilter = DoubleVolumeFilter(1)
volumefilter.set_input_sampling_rate(sampling_rate)
volumefilter.set_volume(-1)
volumefilter.set_input_port(0, slowattackreleasefilter, 0)

sumfilter = DoubleSumFilter()
sumfilter.set_input_sampling_rate(sampling_rate)
sumfilter.set_input_port(0, fastattackreleasefilter, 0)
sumfilter.set_input_port(1, volumefilter, 0)

gainfilter = DoubleGainCompressorFilter(1)
gainfilter.set_input_sampling_rate(sampling_rate)
gainfilter.set_input_port(0, sumfilter, 0)
gainfilter.set_threshold(.1)
gainfilter.set_ratio(.5)
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

outdata_slow = np.zeros((processsize, 1), dtype=np.float32)
outfilter_slow = FloatOutPointerFilter(outdata_slow, True)
outfilter_slow.set_input_sampling_rate(sampling_rate)
outfilter_slow.set_input_port(0, slowattackreleasefilter, 0)

outdata_fast = np.zeros((processsize, 1), dtype=np.float32)
outfilter_fast = FloatOutPointerFilter(outdata_fast, True)
outfilter_fast.set_input_sampling_rate(sampling_rate)
outfilter_fast.set_input_port(0, fastattackreleasefilter, 0)

outdata_power = np.zeros((processsize, 1), dtype=np.float32)
outfilter_power = FloatOutPointerFilter(outdata_power, True)
outfilter_power.set_input_sampling_rate(sampling_rate)
outfilter_power.set_input_port(0, sumfilter, 0)

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
pipelineend.add_filter(outfilter_slow)
pipelineend.add_filter(outfilter_fast)
pipelineend.process(processsize)

start = 0
stop = processsize

x = np.arange(stop, dtype=np.float32) / sampling_rate

plt.figure()
plt.suptitle("Transient Shaper")
plt.subplot(4, 1, 1)
plt.title("Input")
plt.plot(x[start:], indata[start:stop, 0])

plt.subplot(4, 1, 2)
plt.title("Resulting envelope")
plt.plot(x[start:], outdata_power[start:stop, 0], label="Power difference")
plt.plot(x[start:], outdata_slow[start:stop, 0], label="Slow attack power")
plt.plot(x[start:], outdata_fast[start:stop, 0], label="Fast attack power")
plt.legend()

plt.subplot(4, 1, 3)
plt.title("Gain")
plt.plot(x[start:], outdata_gain[start:stop, 0])

plt.subplot(4, 1, 4)
plt.title("Output")
plt.plot(x[start:], outdata[start:stop, 0])

plt.show()
