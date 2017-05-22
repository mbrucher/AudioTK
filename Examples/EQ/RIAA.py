# -*- coding: utf-8 -*-

import numpy as np
from scipy.signal import freqs, freqz, bilinear
from matplotlib import pyplot as plt

from ATK.EQ import FloatRIAAFilter

sampling_rate = 96000

t1 = 75e-6
t2 = 318e-6
t3 = 3180e-6
t4 = 7950e-6

sa1 = [0, 1]
sb1 = [t1, 1]

sa2 = [t2, 1]
sb2 = [0, 1]

sa3 = [0, 1]
sb3 = [t3, 1]

sa4 = [t4, 0]
sb4 = [t4, 1]

sa = np.polymul(np.polymul(sa1, sa2), sa3)
sb = np.polymul(np.polymul(sb1, sb2), sb3)

wb, hb = freqs(sa*t2/t1, sb, worN=sampling_rate/2*np.logspace(-3,0,1000))

fig = plt.figure()
plt.title('Filter frequency response comparison')
ax1 = fig.add_subplot(111)

ax1.semilogx(wb, 20 * np.log10(np.abs(hb)), 'r', label="Reference (amplitude)")
ax1.set_ylabel('Amplitude [dB]', color='b')

ax2 = ax1.twinx()
anglesb = np.unwrap(np.angle(hb))
ax2.semilogx(wb, anglesb, 'k', label="Reference (angle)")

"""warping first"""
k = t2/t1
print(t1, t2, t3, t4)
t1 = 1/(sampling_rate*np.tan(np.pi / (t1 * sampling_rate)))
t2 = 1/(sampling_rate*np.tan(np.pi / (t2 * sampling_rate)))
t3 = 1/(sampling_rate*np.tan(np.pi / (t3 * sampling_rate)))
t4 = 1/(sampling_rate*np.tan(np.pi / (t4 * sampling_rate)))
print(t1, t2, t3, t4)

sa1 = [0, 1]
sb1 = [t1, 1]

sa2 = [t2, 1]
sb2 = [0, 1]

sa3 = [0, 1]
sb3 = [t3, 1]

sa4 = [t4, 0]
sb4 = [t4, 1]

sa = np.polymul(np.polymul(sa1, sa2), sa3)
sb = np.polymul(np.polymul(sb1, sb2), sb3)

b, a = bilinear(sa*k, sb, sampling_rate)

riaafilter = FloatRIAAFilter()
riaafilter.input_sampling_rate = sampling_rate

print(riaafilter.coefficients_in[::-1])
print(np.hstack(([1], -riaafilter.coefficients_out[::-1])))
print(b)
print(a)

wh, hh = freqz(riaafilter.coefficients_in[::-1], np.hstack(([1], -riaafilter.coefficients_out[::-1])), worN=np.pi*np.logspace(-3.5,-.2,1500))

ax1.semilogx(wh/np.pi*sampling_rate, 20 * np.log10(np.abs(hh)), 'b', label="ATK (amplitude)")
ax1.set_ylabel('Amplitude [dB]', color='b')
ax1.set_xlabel('Frequency [Hz]')

anglesh = np.unwrap(np.angle(hh))
ax2.semilogx(wh/np.pi*sampling_rate, anglesh, 'g', label="ATK (angle)")
ax2.set_ylabel('Angle (radians)', color='g')
ax1.grid()
plt.axis('tight')
ax1.legend(loc=0)
ax2.legend(loc=3)
plt.show()
