from ulab import numpy as np # to get access to ulab numpy functions
import time

# Define the sampling rate and duration of the signal
fs = 1024  # Sampling rate
duration = 1  # Duration of the signal in seconds
n = fs * duration  # Number of samples

# Create the time array
t = np.linspace(0, duration, n, endpoint=False)

# Define the three sine waves with different frequencies
f1 = 50  # Frequency of the first sine wave
f2 = 100  # Frequency of the second sine wave
f3 = 200  # Frequency of the third sine wave
x = np.sin(2 * np.pi * f1 * t) + np.sin(2 * np.pi * f2 * t) + np.sin(2 * np.pi * f3 * t)

# Take the FFT of the signal
a, b = np.fft.fft(x)
print('real part:\t', a)
print('\nimaginary part:\t', b)

while (1):
    for i in range(len(a)):
        print("("+str(a[i])+",)") # print with plotting format
        time.sleep(.01) # delay in seconds









