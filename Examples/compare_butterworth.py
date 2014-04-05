#!/usr/bin/env python

from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

b, a = signal.butter(5, 1000./24000, btype="high")

myb = (-0.8089749484507495, 4.044874742253747, -8.089749484507495, 8.089749484507495, -4.044874742253747, 0.8089749484507495)
mya = (-0.6544404672199353, 3.54936607194117, -7.712655577891663, 8.394248760033474, -4.576487473337743, 1 )[::-1]

origbutter = signal.freqz(b, a)
mybutter = signal.freqz(myb, mya)

fig = plt.figure()
plt.title('Digital filter frequency response')
ax1 = fig.add_subplot(111)

plt.loglog(origbutter[0] / np.pi * 24000, np.abs(origbutter[1]), 'b')
plt.loglog(mybutter[0] / np.pi * 24000, np.abs(mybutter[1]), 'g')
plt.show()
