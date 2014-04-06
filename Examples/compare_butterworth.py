#!/usr/bin/env python

from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

b, a = signal.butter(5, (200./24000, 1000./24000), btype="bandstop")
print b, a

myb = (0.844056445676857, -8.426092680617854, 37.86686509663166, -100.88215891093614, 176.44292152260732, -211.69118294672327, 176.44292152260726, -100.88215891093608, 37.86686509663164, -8.426092680617845, 0.8440564456768559)
mya = (-0.7124312834885348, 7.353080760168991, -34.168986128890744, 94.14003557518912, -170.29762595791465, 211.35279625401296, -182.24941708736654, 107.81717331448749, -41.87922567217062, 9.644600225972116, -1 )[::-1]

origbutter = signal.freqz(b, a)
mybutter = signal.freqz(myb, mya)

fig = plt.figure()
plt.title('Digital filter frequency response')
ax1 = fig.add_subplot(111)

plt.loglog(origbutter[0] / np.pi * 24000, np.abs(origbutter[1]), 'b')
plt.loglog(mybutter[0] / np.pi * 24000, np.abs(mybutter[1]), 'g')
plt.show()
