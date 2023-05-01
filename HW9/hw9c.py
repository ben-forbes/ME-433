import matplotlib.pyplot as plt # for plotting
from scipy.signal import lfilter, firwin
import numpy as np # for sine function
import csv

# Import the csv
t = [] # column 0
data1 = [] # column 1

with open('sigC.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column

## Implement FFT

Fs = len(t)/t[-1] # sample rate = total number of samples / total time of samples
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = data1 # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)/n # fft computing and normalization
Y = Y[range(int(n/2))]

fig1,(ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,y,'b')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()

# Implement moving average low-pass filter
# Program to calculate moving average
arr = data1
window_size = 50
  
i = 0
# Initialize an empty list to store moving averages
moving_averages = []
  
# Loop through the array to consider
# every window of size 3
while i < len(arr) - window_size + 1:
    if i < window_size-1:
        moving_averages.append(0)
    # Store elements from i to i+window_size
    # in list to get the current window
    window = arr[i : i + window_size]
  
    # Calculate the average of current window
    window_average = round(sum(window) / window_size, 2)
      
    # Store the average of current
    # window in moving average list
    moving_averages.append(window_average)
      
    # Shift window to right by one position
    i += 1
moving_averages = list(moving_averages)

Y1 = np.fft.fft(moving_averages)/n # fft computing and normalization
Y1 = Y1[range(int(n/2))]
  
fig2, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,y,'k',t,moving_averages,'r')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'k',frq,abs(Y1),'r') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.title('Moving Average Filter with X = 50')
plt.show()

# IIR Filter

f = []
A = 0.9
B = 0.1

for dp in data1:
    if len(f) == 0:
        f.append(0)
    else:
        f.append(f[-1]*A + dp*B)

Y2 = np.fft.fft(f)/n # fft computing and normalization
Y2 = Y2[range(int(n/2))]

fig3, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,y,'k',t,f,'r')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'k',frq,abs(Y2),'r') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.title('IIR Filter with Values A = 0.9 and B = 0.1')
plt.show()

# Implement FIR Filter
# The Nyquist rate of the signal.
nyq_rate = Fs / 2.

# The cutoff frequency of the filter
cutoff_hz = 60

# Length of the filter (number of coefficients, i.e. the filter order + 1)
numtaps = 49

# Use firwin to create a lowpass FIR filter
fir_coeff = firwin(numtaps, cutoff_hz/nyq_rate)

# Use lfilter to filter the signal with the FIR filter
filtered_signal = lfilter(fir_coeff, 1.0, data1)

Y3 = np.fft.fft(filtered_signal)/n # fft computing and normalization
Y3 = Y3[range(int(n/2))]

fig4, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,y,'k',t,filtered_signal,'r')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'k',frq,abs(Y3),'r') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.title('FIR Filter')
plt.show()
