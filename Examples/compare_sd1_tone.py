#!/usr/bin/env python

from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

def create_coeffs(alpha):
  R1 = 10e3
  C1 = 0.018e-6
  R2 = 22e3
  C2 = 0.027e-6
  R3 = 470
  C3 = 0.01e-6
  R4 = 10e3
  
  return (C3*R4*(R3*C2+alpha*(1-alpha)*R2*C2), C2*R3+R4*C3+alpha*(1-alpha)*R2*C2+alpha*C2*R4, 1), (C1*R1*(R3*C2+alpha*(1-alpha)*R2*C2), C2*R3+R1*C1+alpha*(1-alpha)*R2*C2+(1-alpha)*C2*R1, 1)

b0, a0 = create_coeffs(0)
b1, a1 = create_coeffs(1)
b, a = create_coeffs(0.5)

sd10 = signal.freqs(b0, a0, worN=np.logspace(1, 4.5, 1000))
sd11 = signal.freqs(b1, a1, worN=np.logspace(1, 4.5, 1000))
sd1 = signal.freqs(b, a, worN=np.logspace(1, 4.5, 1000))

fig = plt.figure()
plt.title('Analog filter frequency response (SD1 tone circuit)')
ax1 = fig.add_subplot(111)

plt.loglog(sd10[0], np.abs(sd10[1]), 'b', label="alpha=0")
plt.loglog(sd11[0], np.abs(sd11[1]), 'g', label="alpha=1")
plt.loglog(sd1[0], np.abs(sd1[1]), 'r', label="alpha=0.5")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Amplitude (dB)")
plt.legend()

b0d, a0d = signal.bilinear(b0, a0, 44100)
b1d, a1d = signal.bilinear(b1, a1, 44100)
bd, ad = signal.bilinear(b, a, 44100)

sd10d = signal.freqz(b0d, a0d)
sd11d = signal.freqz(b1d, a1d)
sd1d = signal.freqz(bd, ad)

fig = plt.figure()
plt.title('Digital filter frequency response (SD1 tone circuit) 44.1kHz')
ax1 = fig.add_subplot(111)

plt.loglog(sd10d[0], np.abs(sd10d[1]), 'b', label="alpha=0")
plt.loglog(sd11d[0], np.abs(sd11d[1]), 'g', label="alpha=1")
plt.loglog(sd1d[0], np.abs(sd1d[1]), 'r', label="alpha=0.5")
plt.xlabel("Frequency (rad/sample)")
plt.ylabel("Amplitude (dB)")
plt.legend()

b0d, a0d = signal.bilinear(b0, a0, 44100*2)
b1d, a1d = signal.bilinear(b1, a1, 44100*2)
bd, ad = signal.bilinear(b, a, 44100*2)

sd10d = signal.freqz(b0d, a0d)
sd11d = signal.freqz(b1d, a1d)
sd1d = signal.freqz(bd, ad)

fig = plt.figure()
plt.title('Digital filter frequency response (SD1 tone circuit) 88.2kHz')
ax1 = fig.add_subplot(111)

plt.loglog(sd10d[0], np.abs(sd10d[1]), 'b', label="alpha=0")
plt.loglog(sd11d[0], np.abs(sd11d[1]), 'g', label="alpha=1")
plt.loglog(sd1d[0], np.abs(sd1d[1]), 'r', label="alpha=0.5")
plt.xlabel("Frequency (rad/sample)")
plt.ylabel("Amplitude (dB)")
plt.legend()

plt.show()
