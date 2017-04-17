#!/usr/bin/python
from csv import reader
from matplotlib import pyplot

# Parse time/altitude data
with open('data.txt', 'rb') as csvfile:
        data = list(reader(csvfile, delimiter=' '))

# Extract time & altitude
time = [i[0] for i in data[1::]]
alti = [i[1] for i in data[1::]]

# Plot using pyplot from matplotlib
pyplot.plot(time, alti)
pyplot.title('Altitude vs. Time');
pyplot.xlabel('Time');
pyplot.ylabel('Altitude');
pyplot.show()
