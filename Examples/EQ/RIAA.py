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

wb, hb = freqs(sb*t1/t2, sa, worN=sampling_rate/2*np.logspace(-3,0,1000))
wh, hh = freqs(sa*t2/t1, sb, worN=sampling_rate/2*np.logspace(-3,0,1000))
fig = plt.figure()
plt.title('Analog filter frequency response')
ax1 = fig.add_subplot(111)

#ax1.semilogx(wb, 20 * np.log10(np.abs(hb)), 'b', label="Inverse")
ax1.semilogx(wh, 20 * np.log10(np.abs(hh)), 'r', label="reference")
ax1.set_ylim([-30,30])
ax1.set_ylabel('Amplitude [dB]', color='b')
plt.xlabel('Frequency [Hz]')

ax2 = ax1.twinx()
anglesb = np.unwrap(np.angle(hb))
anglesh = np.unwrap(np.angle(hh))
#ax2.semilogx(wb, anglesb, 'g', label="Inverse")
ax2.semilogx(wh, anglesh, 'k', label="Reference")
ax2.set_ylabel('Angle (radians)', color='g')
ax2.set_ylim([-1.5,0])
ax1.grid()
plt.axis('tight')

"""warping first"""
k = t2/t1
print(t1, t2, t3, t4)
t1 = np.pi/(sampling_rate*np.tan(np.pi / (t1 * sampling_rate)))
t2 = np.pi/(sampling_rate*np.tan(np.pi / (t2 * sampling_rate)))
t3 = np.pi/(sampling_rate*np.tan(np.pi / (t3 * sampling_rate)))
t4 = np.pi/(sampling_rate*np.tan(np.pi / (t4 * sampling_rate)))
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

wb, hb = freqz(riaafilter.coefficients_in[::-1], np.hstack(([1], -riaafilter.coefficients_out[::-1])), worN=np.pi*np.logspace(-3,0,1000))
wh, hh = freqz(b, a, worN=np.pi*np.logspace(-3,0,1000))

fig = plt.figure()
plt.title('Digital filter frequency response')
ax1 = fig.add_subplot(111)

ax1.semilogx(wb, 20 * np.log10(np.abs(hb)), 'b', label="ATK")
ax1.semilogx(wh, 20 * np.log10(np.abs(hh)), 'r', label="reference")
ax1.set_ylabel('Amplitude [dB]', color='b')
ax1.set_ylim([-30,30])
plt.xlabel('Frequency [rad/sample]')

ax2 = ax1.twinx()
anglesb = np.unwrap(np.angle(hb))
anglesh = np.unwrap(np.angle(hh))
ax2.semilogx(wb, anglesb, 'g', label="ATK")
ax2.semilogx(wh, anglesh, 'k', label="Reference")
ax2.set_ylabel('Angle (radians)', color='g')
ax2.set_ylim([-1.5,0])
ax1.grid()
plt.axis('tight')

plt.show()
