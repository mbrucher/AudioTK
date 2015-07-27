#!/usr/bin/env python

from ATK.EQ import DoubleBesselLowPassFilter, DoubleButterworthLowPassFilter
from ATK.EQ import DoubleChebyshev1LowPassFilter, DoubleChebyshev2LowPassFilter
from ATK.EQ import DoubleLinkwitzRileyLowPassFilter, DoubleLowPassFilter, DoubleRobertBristowJohnsonLowPassFilter

def get_low_pass(filter, order=-1, ripple=0, samplingrate=48000):
  from scipy import signal

  lowpassfilter = filter()
  lowpassfilter.set_input_sampling_rate(samplingrate)
  lowpassfilter.set_cut_frequency(samplingrate/20)
  if(order > 0):
    lowpassfilter.set_order(order)
  if(ripple > 0):
    lowpassfilter.set_ripple(ripple)

  b = list(np.array(lowpassfilter.get_coefficients_in()))
  a1 = list(-np.array(lowpassfilter.get_coefficients_out())[::-1])
  a = [1]
  a.extend(a1)

  return signal.freqz(b, a[::-1], worN=1000)

import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
ax1 = fig.add_subplot(211)

plt.title('Digital filter frequency response')

bessel = get_low_pass(DoubleBesselLowPassFilter, order=2)
butter = get_low_pass(DoubleButterworthLowPassFilter, order=2)
cheby1 = get_low_pass(DoubleChebyshev1LowPassFilter, order=2, ripple=1)
cheby2 = get_low_pass(DoubleChebyshev2LowPassFilter, order=2, ripple=20)
second = get_low_pass(DoubleLowPassFilter)
lr = get_low_pass(DoubleLinkwitzRileyLowPassFilter)
rbj = get_low_pass(DoubleRobertBristowJohnsonLowPassFilter)

plt.loglog(bessel[0] / np.pi * 24000, np.abs(bessel[1]), label="Bessel")
plt.loglog(butter[0] / np.pi * 24000, np.abs(butter[1]), label="Butterworth", marker="x")
plt.loglog(cheby1[0] / np.pi * 24000, np.abs(cheby1[1]), label="Chebyshev type 1")
plt.loglog(cheby2[0] / np.pi * 24000, np.abs(cheby2[1]), label="Chebyshev type 2")
plt.loglog(second[0] / np.pi * 24000, np.abs(second[1]), label="Second order")
plt.loglog(lr[0] / np.pi * 24000, np.abs(lr[1]), label="Linkwitz-Riley")
plt.loglog(rbj[0] / np.pi * 24000, np.abs(rbj[1]), label="RBJ")
plt.xlim((20, 24000))
plt.ylim((1e-3, 2))
plt.legend(loc=3)

ax1 = fig.add_subplot(212)
plt.semilogx(bessel[0] / np.pi * 24000, np.angle(bessel[1]), label="Bessel")
plt.semilogx(butter[0] / np.pi * 24000, np.angle(butter[1]), label="Butterworth", marker="x")
plt.semilogx(cheby1[0] / np.pi * 24000, np.angle(cheby1[1]), label="Chebyshev type 1")
plt.semilogx(cheby2[0] / np.pi * 24000, np.angle(cheby2[1]), label="Chebyshev type 2")
plt.semilogx(second[0] / np.pi * 24000, np.angle(second[1]), label="Second order")
plt.semilogx(lr[0] / np.pi * 24000, np.angle(lr[1]), label="Linkwitz-Riley")
plt.semilogx(rbj[0] / np.pi * 24000, np.angle(rbj[1]), label="RBJ")
plt.xlim((20, 24000))

plt.show()
