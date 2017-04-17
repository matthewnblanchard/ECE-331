#!/usr/bin/python
import csv
with open('predict60.raw', 'rb') as csvfile:
        data = csv.reader(csvfile, delimiter=' ')
        for row in data:
                print "%s %s" %(row[0], row[1])
