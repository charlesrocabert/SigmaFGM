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
			if l[i] != "-1.0":
				means[i] += float(l[i])
				sdevs[i] += float(l[i])*float(l[i])
				count[i] += 1.0
		l = f.readline()
	f.close()
	for i in range(N):
		means[i] /= count[i]
		sdevs[i] /= count[i]
		sdevs[i] -= means[i]*means[i]
		sdevs[i]  = np.sqrt(sdevs[i])
	return header, means, sdevs

### Correct data and save it ###
def correct_data_and_save( strain, means ):
	f = open("merged/"+strain+".txt", "r")
	g = open("corrected/"+strain+".txt", "w")
	g.write(f.readline())
	l = f.readline()
	while l:
		l    = l.strip("\n").split(" ")
		newl = ""
		for i in range(len(l)):
			if float(l[i]) == -1.0:
				newl += str(means[i])+" "
			else:
				newl += l[i]+" "
		g.write(newl.strip(" ")+"\n")
		l = f.readline()
	f.close()
	g.close()


##################
#      MAIN      #
##################

strains = load_strain_names()

os.system("rm -rf corrected")
os.mkdir("corrected")

for strain in strains:
	print ">>> correct data for "+strain
	header, means, sdevs = compute_means(strain)
	correct_data_and_save(strain, means)





