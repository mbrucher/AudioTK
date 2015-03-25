#!/usr/bin/env python

import numpy as np
from scipy.io import wavfile
import matplotlib.pyplot as plt

from ATK.Core import Int32InPointerFilter, FloatOutPointerFilter, PipelineGlobalSinkFilter
from ATK.Tools import FloatMiddleSideFilter, FloatVolumeFilter

from ATK.Dynamic import DoubleAttackReleaseFilter, DoubleGainCompressorFilter, DoublePowerFilter
from ATK.Tools import DoubleApplyGainFilter

# get from http://www.telefunken-elektroakustik.com/download/brew/

sampling_ratel, datal = wavfile.read("KEYS LEFT - DI - LaChappel 992.wav")
sampling_rater, datar = wavfile.read("KEYS RIGHT - DI - LaChappel 992.wav")

assert sampling_ratel == sampling_rater

sampling_rate = sampling_ratel

datal = datal.reshape(-1, 1)
datar = datar.reshape(-1, 1)
infilterl = Int32InPointerFilter(datal, True)
infilterl.set_output_sampling_rate(sampling_rate)
infilterr = Int32InPointerFilter(datar, True)
infilterr.set_output_sampling_rate(sampling_rate)

msfilter = FloatMiddleSideFilter()
msfilter.set_input_sampling_rate(sampling_rate)
msfilter.set_input_port(0, infilterl, 0)
msfilter.set_input_port(1, infilterr, 0)

powerfilter = DoublePowerFilter(2)
powerfilter.set_input_sampling_rate(sampling_rate)
powerfilter.set_input_port(0, msfilter, 0)
powerfilter.set_input_port(1, msfilter, 1)
powerfilter.set_memory(np.exp(-1/(sampling_rate*.1e-3)))

attackreleasefilterm = DoubleAttackReleaseFilter(1)
attackreleasefilterm.set_input_sampling_rate(sampling_rate)
attackreleasefilterm.set_input_port(0, powerfilter, 0)
attackreleasefilterm.set_attack(np.exp(-1/(sampling_rate*1e-3)))
attackreleasefilterm.set_release(np.exp(-1/(sampling_rate*100e-3)))

attackreleasefilters = DoubleAttackReleaseFilter(1)
attackreleasefilters.set_input_sampling_rate(sampling_rate)
attackreleasefilters.set_input_port(0, powerfilter, 1)
attackreleasefilters.set_attack(np.exp(-1/(sampling_rate*10e-3)))
attackreleasefilters.set_release(np.exp(-1/(sampling_rate*1000e-3)))

gainfilter = DoubleGainCompressorFilter(2)
gainfilter.set_input_sampling_rate(sampling_rate)
gainfilter.set_input_port(0, attackreleasefilterm, 0)
gainfilter.set_input_port(1, attackreleasefilters, 0)
gainfilter.set_threshold(0.1)
gainfilter.set_ratio(10)
gainfilter.set_softness(1)

applygainfilter = DoubleApplyGainFilter(2)
applygainfilter.set_input_sampling_rate(sampling_rate)
applygainfilter.set_input_port(0, gainfilter, 0)
applygainfilter.set_input_port(1, msfilter, 0)
applygainfilter.set_input_port(2, gainfilter, 1)
applygainfilter.set_input_port(3, msfilter, 1)

msmergefilter = FloatMiddleSideFilter()
msmergefilter.set_input_sampling_rate(sampling_rate)
msmergefilter.set_input_port(0, applygainfilter, 0)
msmergefilter.set_input_port(1, applygainfilter, 1)
  
volumefilter2 = FloatVolumeFilter(2)
volumefilter2.set_input_sampling_rate(sampling_rate)
volumefilter2.set_input_port(0, msmergefilter, 0)
volumefilter2.set_input_port(1, msmergefilter, 1)
volumefilter2.set_volume(.5) # Account for MS gain


indata = np.zeros((len(datal), 2), dtype=np.float32)
infilter = FloatOutPointerFilter(indata, True)
infilter.set_input_sampling_rate(sampling_rate)
infilter.set_input_port(0, infilterl, 0)
infilter.set_input_port(1, infilterr, 0)

outdata = np.zeros((len(datal), 2), dtype=np.float32)
outfilter = FloatOutPointerFilter(outdata, True)
outfilter.set_input_sampling_rate(sampling_rate)
outfilter.set_input_port(0, volumefilter2, 0)
outfilter.set_input_port(1, volumefilter2, 1)

outdata_power = np.zeros((len(datal), 2), dtype=np.float32)
outfilter_power = FloatOutPointerFilter(outdata_power, True)
outfilter_power.set_input_sampling_rate(sampling_rate)
outfilter_power.set_input_port(0, powerfilter, 0)
outfilter_power.set_input_port(1, powerfilter, 1)

outdata_gain = np.zeros((len(datal), 2), dtype=np.float32)
outfilter_gain = FloatOutPointerFilter(outdata_gain, True)
outfilter_gain.set_input_sampling_rate(sampling_rate)
outfilter_gain.set_input_port(0, gainfilter, 0)
outfilter_gain.set_input_port(1, gainfilter, 1)

pipelineend = PipelineGlobalSinkFilter()
pipelineend.set_input_sampling_rate(sampling_rate)
pipelineend.add_filter(infilter)
pipelineend.add_filter(outfilter)
pipelineend.add_filter(outfilter_power)
pipelineend.add_filter(outfilter_gain)
pipelineend.process(len(datal))

length = 10000

x = np.arange(length, dtype=np.float32) / sampling_rate

plt.figure()
plt.suptitle("Input")
plt.subplot(2, 1, 1)
plt.title("Left channel")
plt.plot(x, indata[:length, 0])
plt.subplot(2, 1, 2)
plt.title("Right channel")
plt.plot(x, indata[:length, 1])

plt.figure()
plt.suptitle("Output")
plt.subplot(2, 1, 1)
plt.title("Left channel")
plt.plot(x, outdata[:length, 0])
plt.subplot(2, 1, 2)
plt.title("Right channel")
plt.plot(x, outdata[:length, 1])

plt.figure()
plt.suptitle("Power")
plt.subplot(2, 1, 1)
plt.title("Middle channel")
plt.plot(x, outdata_power[:length, 0])
plt.subplot(2, 1, 2)
plt.title("Side channel")
plt.plot(x, outdata_power[:length, 1])

plt.figure()
plt.suptitle("Gain")
plt.subplot(2, 1, 1)
plt.title("Middle channel")
plt.plot(x, outdata_gain[:length, 0])
plt.subplot(2, 1, 2)
plt.title("Side channel")
plt.plot(x, outdata_gain[:length, 1])

plt.show()
