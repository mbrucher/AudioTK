# -*- coding: utf-8 -*-
"""
Remez example
"""

import matplotlib.pyplot as plt
import numpy as np
import numpy.linalg as linalg
#from scipy.signal import freqz
from numpy.fft import fft

def firamp(h, L, w):
  H=fft(h, 2*L)
  H = H[0:L]
  return np.real(np.exp(1j * M * w) * H)

def locmax(x):
  temp1 = np.hstack((x[0]-1, x[:-1]))
  temp2 = np.hstack((x[1:], x[-1]-1))
  return np.where(np.logical_and(x > temp1, x > temp2))
  
N = 13
Kp = 1
Ks = 2
wp = 0.4*np.pi
ws = 0.5*np.pi
wo = (wp+ws)/2
L = 1000
w = np.arange(L)*np.pi/L
W = Kp*(w<=wp) + Ks*(w>=ws)
D = w <= wo

M = (N-1)//2
R = M+2

k = np.array([51, 101, 341, 361, 531, 671, 701, 851])-1
print(w[k]/np.pi)

m = np.arange(M+1)
s = (-1)**(np.arange(1, R+1))
temp = np.vstack((np.cos(w[k]*m.reshape(-1,1)), s/W[k])).T
x = linalg.solve(temp, D[k])

a = x[:-1]
delta = x[-1]
print(delta)

h = np.hstack((a[:0:-1], 2*a[0], a[1:]))/2

A = firamp(h, L, w)
err = (A-D)*W
print(w[k]/np.pi)
print(err[k])
            
plt.plot(w, err)
newk = np.sort(np.hstack((locmax(err), locmax(-err))))
errk = (A[newk]-D[newk])*W[newk]
print(w[newk]/np.pi)
print(errk)
