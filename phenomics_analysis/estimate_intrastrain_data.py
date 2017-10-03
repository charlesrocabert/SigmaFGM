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
import subprocess
import numpy as np

#################################
# Load the list of strain names #
#################################
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

#######################
# Load replicate data #
#######################
def load_replicate( strain, rep ):
	data       = {}
	cell_count = 0
	f = open("replicates/centered_scaled_"+strain+"_"+str(rep)+".txt", "r")
	data["header"] = f.readline().strip("\n").split(" ")
	l = f.readline()
	while l:
		l = l.strip("\n").split(" ")
		data[cell_count] = []
		for val in l:
			if val == "NA":
				data[cell_count].append("NA")
			else:
				data[cell_count].append(float(val))
		cell_count += 1
		l = f.readline()
	f.close()
	return data

##############################
# Compute correlation matrix #
##############################
def compute_correlation_matrix( replicate ):
	M = len(replicate["header"])
	N = len(replicate.keys())-1
	mat = {}
	for i in range(N):
		mat[i] = {}
		for j in range(N):
			#----------------------------#
			# 1) Compute means and sdevs #
			#----------------------------#
			mA     = 0.0
			mB     = 0.0
			sA     = 0.0
			sB     = 0.0
			countA = 0.0
			countB = 0.0
			for k in range(M):
				if replicate[i][k] != "NA":
					mA     += replicate[i][k]
					sA     += replicate[i][k]*replicate[i][k]
					countA += 1.0
				if replicate[j][k] != "NA":
					mB     += replicate[j][k]
					sB     += replicate[j][k]*replicate[j][k]
					countB += 1.0
			if countA > 0.0:
				mA /= countA
				sA /= countA
				sA -= mA*mA
				sA  = np.sqrt(sA)
			if countB > 0.0:
				mB /= countB
				sB /= countB
				sB -= mB*mB
				sB  = np.sqrt(sB)
			#----------------------------#
			# 2) Compute correlation     #
			#----------------------------#
			cor   = 0.0
			count = 0.0
			for k in range(M):
				if replicate[i][k] != "NA" and replicate[j][k] != "NA":
					cor   += (replicate[i][k]-mA)*(replicate[j][k]-mB)
					count += 1.0
				if count > 0.0:
					cor /= count*sA*sB
			#----------------------------#
			# 3) Save correlation        #
			#----------------------------#
			mat[i][j] = cor
	return mat

######################################
# Interpolate missing replicate data #
######################################
def interpolate( strain, rep, replicate, cormat ):
	M = len(replicate["header"])
	N = len(replicate.keys())-1
	#--------------------------------#
	# 1) Compute mean traits         #
	#--------------------------------#
	means = []
	for i in range(N):
		meantrait = 0.0
		count     = 0.0
		for k in range(M):
			if not str(replicate[i][k]).startswith("NA"):
				meantrait += replicate[i][k]
				count     += 1.0
		if count > 0.0:
			meantrait /= count
		means.append(meantrait)
	#--------------------------------#
	# 2) Compute interpolated values #
	#--------------------------------#
	for i in range(N):
		for k in range(M):
			if str(replicate[i][k]).startswith("NA"):
				interpolation = 0.0
				corsum        = 0.0
				for j in range(N):
					if not str(replicate[j][k]).startswith("NA"):
						interpolation += (replicate[j][k]-means[j])*cormat[i][j]
						corsum        += abs(cormat[i][j])
				if corsum > 0.0:
					interpolation /= corsum
				interpolation += means[i]
				replicate[i][k] = "NA "+str(interpolation)
	#--------------------------------#
	# 3) Write data file             #
	#--------------------------------#
	f = open("interpolated/"+strain+"_"+str(rep)+".txt", "w")
	header = ""
	for var in replicate["header"]:
		header += var+" "
	f.write(header.strip(" ")+"\n")
	for i in range(N):
		line = ""
		for val in replicate[i]:
			if str(val).startswith("NA"):
				line += val.split(" ")[1]+" "
			else:
				line += str(val)+" "
		f.write(line.strip(" ")+"\n")
	f.close()


##################
#      MAIN      #
##################

strains = load_strain_names()
reps    = [1,2,3,4,5]

os.system("rm -rf interpolated")
os.mkdir("interpolated")

for strain in strains:
	for rep in reps:
		print "> Estimate missing data for replicate "+strain+"-"+str(rep)
		replicate = load_replicate(strain, rep)
		cormat    = compute_correlation_matrix(replicate)
		interpolate(strain, rep, replicate, cormat)

