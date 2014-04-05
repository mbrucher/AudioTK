#!/usr/bin/env python

from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

b, a = signal.butter(5, 23000./24000)

myb = (0.5853375951189914, 2.926687975594957, 5.853375951189914, 5.853375951189914, 2.926687975594957, 0.5853375951189914)
mya = (-0.3426200947914363, -2.077572699966394, -5.085377425474877, -6.289011983598065, -3.9362208399769525, -1)[::-1]

origbutter = signal.freqz(b, a)
mybutter = signal.freqz(myb, mya)

fig = plt.figure()
plt.title('Digital filter frequency response')
ax1 = fig.add_subplot(111)

plt.loglog(origbutter[0] / np.pi * 24000, np.abs(origbutter[1]), 'b')
plt.loglog(mybutter[0] / np.pi * 24000, np.abs(mybutter[1]), 'g')
plt.show()
