#!/usr/bin/env python

from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

b, a = signal.cheby2(5, 3, (200./24000, 1000./24000), btype="bandstop")
print b, a

myb = (0.970480608569324, -9.674889407346342, 43.43258097823774, -115.6217271672294, 202.12989516929048, -242.47268036304317, 202.12989516929048, -115.62172716722938, 43.43258097823773, -9.674889407346342, 0.9704806085693239)
mya = (-0.9418326116090838, 9.445529769182228, -42.657169682139696, 114.23899007770811, -200.91212825428292, 242.46055315510847, -203.33552044319293, 117.01137758064448, -44.21926252097025, 9.909462929551104, -1 )[::-1]

origbutter = signal.freqz(b, a)
mybutter = signal.freqz(myb, mya)

fig = plt.figure()
plt.title('Digital filter frequency response')
ax1 = fig.add_subplot(111)

plt.loglog(origbutter[0] / np.pi * 24000, np.abs(origbutter[1]), 'b')
plt.loglog(mybutter[0] / np.pi * 24000, np.abs(mybutter[1]), 'g')
plt.show()
