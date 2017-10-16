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
# Generate replicates #
#######################
def generate_replicates( strain, reps ):
	#-------------------------------------------------#
	# 1) Define data to collect                       #
	#-------------------------------------------------#
	useless = ["image_number", "Cgroup", "Agroup", "Dgroup", "D115", "D111"]
	expes   = ["actin_biological", "conA_biological", "dapi_biological"]
	#-------------------------------------------------#
	# 2) Collect and rewrite data for each repetition #
	#-------------------------------------------------#
	for rep in reps:
		### 2.1) Collect data ###
		data = {}
		for expe in expes:
			filename = strain+"_"+str(rep)+"_"+expe+".csv"
			f = open("csv-test/"+filename, "r")
			l = f.readline().strip("\t\n").split("\t")
			header = {}
			count = 0
			for var in l:
				if var not in useless:
					header[var] = count
				count += 1
			l = f.readline()
			while l:
				l = l.strip("\t\n").split("\t")
				cell_id = l[header['cell_id']]+"_"+str(rep)
				if cell_id not in data:
					data[cell_id] = {}
				for var in header:
					if var not in data[cell_id] and var != "cell_id":
						if str(float(l[header[var]])) == "inf":
							data[cell_id][var] = -1.0
						else:
							data[cell_id][var] = float(l[header[var]])
				l = f.readline()
			f.close()
		### 2.2) Write data ###
		f = open("replicates/"+strain+"_"+str(rep)+".txt", "w")
		id_0 = data.keys()[0]
		header = {}
		count = 0
		line = ""
		for var in data[id_0]:
			line += var+" "
			header[var] = count
			count += 1
		line = line.strip(" ")+"\n"
		f.write(line)
		for cell_id in data:
			line = ""
			for var in header:
				val = data[cell_id][var]
				if val == -1.0:
					line += "NA "
				else:
					line += str(data[cell_id][var])+" "
			line = line.strip(" ")+"\n"
			f.write(line)
		f.close()

###########################
# Merge strain replicates #
###########################
def merge_replicates( strain, reps ):
	#-------------------------------------------------#
	# 1) Define data to collect                       #
	#-------------------------------------------------#
	useless = ["image_number", "Cgroup", "Agroup", "Dgroup", "D115", "D111"]
	expes   = ["actin_biological", "conA_biological", "dapi_biological"]
	#-------------------------------------------------#
	# 2) Collect and rewrite data for each repetition #
	#-------------------------------------------------#
	data = {}
	### 2.1) Collect data ###
	for rep in reps:
		for expe in expes:
			filename = strain+"_"+str(rep)+"_"+expe+".csv"
			f = open("csv-test/"+filename, "r")
			l = f.readline().strip("\t\n").split("\t")
			header = {}
			count = 0
			for var in l:
				if var not in useless:
					header[var] = count
				count += 1
			l = f.readline()
			while l:
				l = l.strip("\t\n").split("\t")
				cell_id = l[header['cell_id']]+"_"+str(rep)
				if cell_id not in data:
					data[cell_id] = {}
				for var in header:
					if var not in data[cell_id] and var != "cell_id":
						if str(float(l[header[var]])) == "inf":
							data[cell_id][var] = -1.0
						else:
							data[cell_id][var] = float(l[header[var]])
				l = f.readline()
			f.close()
	### 2.2) Write data ###
	f = open("merged/"+strain+".txt", "w")
	id_0 = data.keys()[0]
	header = {}
	count = 0
	line = ""
	for var in data[id_0]:
		line += var+" "
		header[var] = count
		count += 1
	line = line.strip(" ")+"\n"
	f.write(line)
	for cell_id in data:
		line = ""
		for var in header:
			val = data[cell_id][var]
			if val == -1.0:
				line += "NA "
			else:
				line += str(data[cell_id][var])+" "
		line = line.strip(" ")+"\n"
		f.write(line)
	f.close()

##############################
# Compute inter-strain means #
##############################
def compute_interstrain_means( strains ):
	data           = {}
	data["header"] = {}
	data["mean"]   = {}
	#------------------#
	# 1) Collect means #
	#------------------#
	for strain in strains:
		f         = open("merged/"+strain+".txt", "r")
		header    = f.readline()
		variables = header.strip("\n").split(" ")
		N         = len(variables)
		l         = f.readline()
		means     = [0.0]*N
		count     = [0.0]*N
		while l:
			l = l.strip("\n").split(" ")
			for i in range(N):
				if l[i] != "NA":
					means[i] += float(l[i])
					count[i] += 1.0
			l = f.readline()
		f.close()
		for i in range(N):
			if count[i] > 0.0:
				means[i] /= count[i]
			if str(means[i]) == "inf":
				print ">>> Infinite value in merged data ("+str(strain)+" - pos"+str(i)+") !!! Exit."
				sys.exit()
		data["header"][strain] = header
		data["mean"][strain]   = means
	#------------------#
	# 2) Write means   #
	#------------------#
	f = open("interstrain/mean.txt", "w")
	s0 = data["header"].keys()[0]
	f.write("name "+data["header"][s0])
	for strain in strains:
		mean = data["mean"][strain]
		l    = strain
		for i in range(len(mean)):
			l += " "+str(mean[i])
		f.write(l+"\n")
	f.close()

################################################################
# Center and scale interstrain data, and get means and stddevs #
################################################################
def center_scale_interstrain_data():
	#-----------------------------#
	# 1) Compute mean and sdev    #
	#-----------------------------#
	f = open("interstrain/mean.txt", "r")
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
	f = open("interstrain/mean.txt", "r")
	g = open("interstrain/centered_scaled_mean.txt", "w")
	g.write(f.readline())
	l = f.readline()
	while l:
		l = l.strip("\n").split(" ")
		line = l[0]
		for i in range(1,len(l)):
			val = 0.0
			if sdevs[i-1] > 0.0:
				val = (float(l[i])-means[i-1])/sdevs[i-1]
			line += " "+str(val)
		g.write(line+"\n")
		l = f.readline()
	f.close()
	g.close()
	#-----------------------------#
	# 3) Return means and stddevs #
	#-----------------------------#
	return means, sdevs

###############################################################################
# Center and scale intrastrain data, according to interstrain means and sdevs #
###############################################################################
def center_scale_intrastrain_data( strain, reps, means, sdevs ):
	for rep in reps:
		#---------------------------------#
		# 1) Center and scale replicates  #
		#---------------------------------#
		f = open("replicates/"+strain+"_"+str(rep)+".txt", "r")
		g = open("replicates/centered_scaled_"+strain+"_"+str(rep)+".txt", "w")
		g.write(f.readline())
		l = f.readline()
		while l:
			l = l.strip("\n").split(" ")
			line = ""
			for i in range(len(l)):
				if l[i] == "NA":
					line += "NA "
				else:
					val = 0.0
					if sdevs[i] > 0.0:
						val = (float(l[i])-means[i])/sdevs[i]
					line += str(val)+" "
			g.write(line.strip(" ")+"\n")
			l = f.readline()
		f.close()
		g.close()
		#---------------------------------#
		# 2) Center and scale merged data #
		#---------------------------------#
		f = open("merged/"+strain+".txt", "r")
		g = open("merged/centered_scaled_"+strain+".txt", "w")
		g.write(f.readline())
		l = f.readline()
		while l:
			l = l.strip("\n").split(" ")
			line = ""
			for i in range(len(l)):
				if l[i] == "NA":
					line += "NA "
				else:
					val = 0.0
					if sdevs[i] > 0.0:
						val = (float(l[i])-means[i])/sdevs[i]
					line += str(val)+" "
			g.write(line.strip(" ")+"\n")
			l = f.readline()
		f.close()
		g.close()


##################
#      MAIN      #
##################

strains = load_strain_names()
reps    = [1,2,3,4,5]

print "> 1) Create folders"
os.system("rm -rf replicates")
os.mkdir("replicates")
os.system("rm -rf merged")
os.mkdir("merged")
#os.system("rm -rf interstrain")
#os.mkdir("interstrain")

print "> 2) Load raw data"
for strain in strains:
	print "  strain "+strain+" ..."
	generate_replicates(strain, reps)
	merge_replicates(strain, reps)

#print "> 3) Compute interstrain means"
#compute_interstrain_means(strains)

print "> 4) Center and scale data"
print "  mean data ..."
means, sdevs = center_scale_interstrain_data()
for strain in strains:
	print "  strain "+strain+" ..."
	center_scale_intrastrain_data(strain, reps, means, sdevs)

