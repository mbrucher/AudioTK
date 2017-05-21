# -*- coding: utf-8 -*-

import numpy as np
from scipy.signal import freqz, bilinear
from matplotlib import pyplot as plt

from ATK.EQ import FloatRIAAFilter

sampling_rate = 96000

t1 = 75e-6
t2 = 318e-6
t3 = 3180e-6
t4 = 7950e-6

sa1 = [0, 1]
sb1 = [-t1, 1]

sa2 = [-t2, 1]
sb2 = [0, t2/t1]

sa3 = [0, 1]
sb3 = [t3, 1]

sa4 = [t4, 0]
sb4 = [t4, 1]

sa = np.polymul(np.polymul(sa1, sa2), sa3)
sb = np.polymul(np.polymul(sb1, sb2), sb3)

b, a = bilinear(sb, sa, sampling_rate)


riaafilter = FloatRIAAFilter()
riaafilter.input_sampling_rate = sampling_rate

wb, hb = freqz(riaafilter.coefficients_in[::-1], np.hstack(([1], -riaafilter.coefficients_out[::-1])))
wh, hh = freqz(b, a)

fig = plt.figure()
plt.title('Digital filter frequency response')
ax1 = fig.add_subplot(111)

#plt.semilogx(wb, 20 * np.log10(np.abs(hb)), 'b', label="ATK")
plt.semilogx(wh, 20 * np.log10(np.abs(hh)), 'r', label="reference")
plt.ylabel('Amplitude [dB]', color='b')
plt.xlabel('Frequency [rad/sample]')

ax2 = ax1.twinx()
anglesb = np.unwrap(np.angle(hb))
anglesh = np.unwrap(np.angle(hh))
angles = np.unwrap(np.angle(hb-hh))
#plt.semilogx(wb, anglesb, 'g', label="ATK")
plt.semilogx(wh, anglesh, 'k', label="Reference")
plt.ylabel('Angle (radians)', color='g')
ax1.grid()
plt.axis('tight')
plt.show()
