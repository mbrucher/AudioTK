
import numpy as np
import scipy.signal as signal
import matplotlib.pyplot as plt


def create_bassman(low, middle, high):
  R1 = 250e3
  R2 = 1e6
  R3 = 25e3
  R4 = 45e3
  C1 = 250e-12
  C2 = 20e-9
  C3 = 20e-9

  b = (0, (high*C1*R1 + middle*C3*R3 + low*(C1*R2 + C2*R2) + (C1*R3 + C2*R3)), (high*(C1*C2*R1*R4 + C1*C3*R1*R4) - middle*middle*(C1*C3*R3*R3 + C2*C3*R3*R3) + middle*(C1*C3*R1*R3 + C1*C3*R3*R3 + C2*C3*R3*R3)
      + low*(C1*C2*R1*R2 + C1*C2*R2*R4 + C1*C3*R2*R4) + low*middle*(C1*C3*R2*R3 + C2*C3*R2*R3)
      + (C1*C2*R1*R3 + C1*C2*R3*R4 + C1*C3*R3*R4)), (low*middle*(C1*C2*C3*R1*R2*R3 + C1*C2*C3*R2*R3*R4) - middle*middle*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4)
      + middle*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4) + high*C1*C2*C3*R1*R3*R4 - high*middle*C1*C2*C3*R1*R3*R4
      + high*low*C1*C2*C3*R1*R2*R4))[::-1]

  a = (1, ((C1*R1 + C1*R3 + C2*R3 + C2*R4 + C3*R4) + middle*C3*R3 + low*(C1*R2 + C2*R2)), (middle*(C1*C3*R1*R3 - C2*C3*R3*R4 + C1*C3*R3*R3 + C2*C3*R3*R3)
      + low*middle*(C1*C3*R2*R3 + C2*C3*R2*R3) - middle*middle*(C1*C3*R3*R3 + C2*C3*R3*R3) + low*(C1*C2*R2*R4 + C1*C2*R1*R2 + C1*C3*R2*R4 + C2*C3*R2*R4)
      + (C1*C2*R1*R4 + C1*C3*R1*R4 + C1*C2*R3*R4 + C1*C2*R1*R3 + C1*C3*R3*R4 + C2*C3*R3*R4)), (low*middle*(C1*C2*C3*R1*R2*R3 + C1*C2*C3*R2*R3*R4) - middle*middle*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4)
      + middle*(C1*C2*C3*R3*R3*R4 + C1*C2*C3*R1*R3*R3 - C1*C2*C3*R1*R3*R4)
      + low*C1*C2*C3*R1*R2*R4 + C1*C2*C3*R1*R3*R4))[::-1]
  return b, a

b, a = create_bassman(0.5, 0.5, 0.5)
w, h = signal.freqs(b, a, worN=np.logspace(1, 5, 1000))
plt.semilogx(w, 20 * np.log10(abs(h)), label="low=middle=high=0.5")

b, a = create_bassman(0, 0.5, 0.5)
w, h = signal.freqs(b, a, worN=np.logspace(1, 5, 1000))
plt.semilogx(w, 20 * np.log10(abs(h)), label="low=0,middle=high=0.5")

b, a = create_bassman(1, 0.5, 0.5)
w, h = signal.freqs(b, a, worN=np.logspace(1, 5, 1000))
plt.semilogx(w, 20 * np.log10(abs(h)), label="low=1,middle=high=0.5")

b, a = create_bassman(0.5, 0, 0.5)
w, h = signal.freqs(b, a, worN=np.logspace(1, 5, 1000))
plt.semilogx(w, 20 * np.log10(abs(h)), label="middle=0,low=high=0.5")

b, a = create_bassman(0.5, 1, 0.5)
w, h = signal.freqs(b, a, worN=np.logspace(1, 5, 1000))
plt.semilogx(w, 20 * np.log10(abs(h)), label="middle=1,low=high=0.5")

b, a = create_bassman(0.5, 0.5, 0)
w, h = signal.freqs(b, a, worN=np.logspace(1, 5, 1000))
plt.semilogx(w, 20 * np.log10(abs(h)), label="low=middle=0.5, high=0")

b, a = create_bassman(0.5, 0.5, 1)
w, h = signal.freqs(b, a, worN=np.logspace(1, 5, 1000))
plt.semilogx(w, 20 * np.log10(abs(h)), label="low=middle=0.5, high=1")


plt.xlabel('Frequency')
plt.ylabel('Amplitude response [dB]')
plt.legend(loc=4)
plt.grid()
plt.show()
