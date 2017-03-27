import matplotlib.pyplot as plt
import numpy as np
size = 1200
x = np.arange(size) / 48000.
d = np.sin(x * 2 * np.pi * 100)

simple = np.fromfile("simple/trapezoidal/simple_NR_id_output4.txt", dtype=np.float64, sep=" ")
clipper = np.fromfile("clipper/trapezoidal/clipper_NR_id_output4.txt", dtype=np.float64, sep=" ")

plt.plot(x, d[:size], label="Input")
plt.plot(x, simple[:size], label="Diode Clipper (serial)")
plt.plot(x, clipper[:size], label="Diode Clipper (parallel)")

plt.title("Diode clipper")
plt.xlabel("Time")
plt.ylabel("Amplitude")
plt.legend(loc=4)

plt.show()
