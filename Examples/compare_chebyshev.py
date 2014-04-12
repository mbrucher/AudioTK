#!/usr/bin/env python

from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

b, a = signal.cheby1(5, 3, (200./24000, 1000./24000), btype="bandstop")
print b, a

myb = (0.7306357663871558, -7.293830542832419, 32.778478432648164, -87.32604776399218, 152.73327968828013, -183.2450311609813, 152.7332796882801, -87.32604776399215, 32.77847843264815, -7.2938305428324135, 0.7306357663871552)
mya = (-0.4965394956628667, 5.398384243072551, -26.28716557837329, 75.56356199300757, -142.09613335284078, 182.75510675096402, -162.87973777474093, 99.36761663230192, -39.72521157301267, 9.400118155284124, -1 )[::-1]

origbutter = signal.freqz(b, a)
mybutter = signal.freqz(myb, mya)

fig = plt.figure()
plt.title('Digital filter frequency response')
ax1 = fig.add_subplot(111)

plt.loglog(origbutter[0] / np.pi * 24000, np.abs(origbutter[1]), 'b')
plt.loglog(mybutter[0] / np.pi * 24000, np.abs(mybutter[1]), 'g')
plt.show()
