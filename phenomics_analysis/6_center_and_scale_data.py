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

### Center and scale mean data, and get mean and stddev ###
def center_scale_mean_data():
	#-----------------------------#
	# 1) Compute mean and sdev    #
	#-----------------------------#
	f = open("interstrain_means/mean.txt", "r")
	l = f.readline()
	l = l.strip("\n").split(" ")
	N = len(l)
	means = [0.0]*(N-1)
	sdevs = [0.0]*(N-1)
	count = 0.0
	l = f.readline()
	while l:
		l = l.strip("\n").split(" ")
		for i in range(N-1):
			means[i] += float(l[i+1])
			sdevs[i] += float(l[i+1])*float(l[i+1])
		count += 1.0
		l = f.readline()
	f.close()
	for i in range(N-1):
		means[i] /= count
		sdevs[i] /= count
		sdevs[i] -= means[i]*means[i]
		sdevs[i]  = np.sqrt(sdevs[i])
	#-----------------------------#
	# 2) Center and scale data    #
	#-----------------------------#
	f = open("interstrain_means/mean.txt", "r")
	g = open("interstrain_means/centered_scaled_mean.txt", "w")
	g.write(f.readline())
	l = f.readline()
	while l:
		l = l.strip("\n").split(" ")
		line = l[0]
		for i in range(1,len(l)):
			val   = (float(l[i])-means[i-1])/sdevs[i-1]
			line += " "+str(val)
		g.write(line+"\n")
		l = f.readline()
	f.close()
	g.close()
	#-----------------------------#
	# 3) Return means and stddevs #
	#-----------------------------#
	return means, sdevs

### Center and scale strain data ###
def center_scale_strain( strain, means, sdevs ):
	f = open("corrected/"+strain+".txt", "r")
	g = open("corrected/centered_scaled_"+strain+".txt", "w")
	g.write(f.readline())
	l = f.readline()
	while l:
		l = l.strip("\n").split(" ")
		line = ""
		for i in range(len(l)):
			val   = (float(l[i])-means[i])/sdevs[i]
			line += str(val)+" "
		g.write(line.strip(" ")+"\n")
		l = f.readline()
	f.close()
	g.close()


##################
#      MAIN      #
##################

strains      = load_strain_names()
means, sdevs = center_scale_mean_data()

for strain in strains:
	print ">>> Centering and scaling "+strain
	center_scale_strain(strain, means, sdevs)








