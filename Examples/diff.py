#!/usr/bin/env python

import numpy as np
from matplotlib import pyplot as plt

input = np.fromfile("input.txt", sep=" ", dtype = np.float64)

output_32 = np.fromfile("output32.txt", sep=" ", dtype = np.float64)
output_16 = np.fromfile("output16.txt", sep=" ", dtype = np.float64)
output_8 = np.fromfile("output8.txt", sep=" ", dtype = np.float64)
output_4 = np.fromfile("output4.txt", sep=" ", dtype = np.float64)

plt.figure()
plt.plot(input[:1000])
plt.plot(output_32[:1000])
plt.title("Oversampling 32 result")
plt.xlabel("time")
plt.ylabel("output amplitude difference")

plt.figure()
plt.plot(input[:1000], (output_32 - output_16)[:1000])
plt.title("Oversampling 32 - oversampling 16")
plt.xlabel("input amplitude")
plt.ylabel("output amplitude difference")
plt.figure()
plt.plot(input[:1000], (output_32 - output_8)[:1000])
plt.title("Oversampling 32 - oversampling 8")
plt.xlabel("input amplitude")
plt.ylabel("output amplitude difference")
plt.figure()
plt.plot(input[:1000], (output_32 - output_4)[:1000])
plt.title("Oversampling 32 - oversampling 4")
plt.xlabel("input amplitude")
plt.ylabel("output amplitude difference")

plt.show()
