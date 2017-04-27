#!/usr/bin/python
from matplotlib import pyplot
import numpy

x = numpy.arange(-10, 10.1, 0.1);
y = numpy.sin(x)/x;

pyplot.plot(x,y);
pyplot.title('ECE 331 HW 12 Problem 5');
pyplot.xlabel('Angle (radians)');
pyplot.ylabel('Amplitude');

pyplot.show();

