#!/usr/bin/env python
# coding: utf-8

#**********************************************************************
# Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#**********************************************************************

import os
import sys
import math
import time
import numpy as np
import subprocess

### Load the list of strain names ###
def load_strain_names():
	strains = []
	f = open("strain_names.txt", "r")
	l = f.readline()
	while l:
		l = l.strip("\n")
		strains.append(l)
		l = f.readline()
	f.close()
	return strains

### Compute the mean and the variance of strain variables ###
def compute_means( strain ):
	f         = open("merged/"+strain+".txt", "r")
	header    = f.readline()
	variables = header.strip("\n").split(" ")
	N         = len(variables)
	l         = f.readline()
	means     = [0.0]*N
	sdevs     = [0.0]*N
	count     = [0.0]*N
	while l:
		l = l.strip("\n").split(" ")
		for i in range(N):
			if l[i] != "-1.0" and l[i] != "inf":
				means[i] += float(l[i])
				sdevs[i] += float(l[i])*float(l[i])
				count[i] += 1.0
				if means[i] == float("Inf"):
					print "F*** "+l[i]+" "+str(means[i])+" "+str(i)+" "+variables[i]
		l = f.readline()
	f.close()
	for i in range(N):
		means[i] /= count[i]
		sdevs[i] /= count[i]
		sdevs[i] -= means[i]*means[i]
		sdevs[i]  = np.sqrt(sdevs[i])
	return header, means, sdevs


##################
#      MAIN      #
##################

strains        = load_strain_names()
data           = {}
data["header"] = {}
data["mean"]   = {}
data["sdev"]   = {}

os.system("rm -rf interstrain_means")
os.mkdir("interstrain_means")

for strain in strains:
	print ">>> computing mean and stddev for "+strain
	header, means, sdevs   = compute_means(strain)
	data["header"][strain] = header
	data["mean"][strain]   = means
	data["sdev"][strain]   = sdevs

f1 = open("interstrain_means/mean.txt", "w")
f2 = open("interstrain_means/sdev.txt", "w")
s0 = data["header"].keys()[0]
f1.write("name "+data["header"][s0])
f2.write("name "+data["header"][s0])
for strain in strains:
	print ">>> Writing data for "+strain
	mean = data["mean"][strain]
	sdev = data["sdev"][strain]
	l1   = strain
	l2   = strain
	for i in range(len(mean)):
		l1 += " "+str(mean[i])
		l2 += " "+str(sdev[i])
	f1.write(l1+"\n")
	f2.write(l2+"\n")
f1.close()
f2.close()





