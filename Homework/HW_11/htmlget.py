#!/usr/bin/python
import urllib2
response = urllib2.urlopen('http://courses.eece.maine.edu/ece331/')
html = response.read()
print html
