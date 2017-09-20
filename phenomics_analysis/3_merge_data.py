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

### Merge data from several files for each strain and repetition ###
def merge_data( strain, reps ):
	#-----------------#
	# 1) Collect data #
	#-----------------#
	useless = ["image_number", "Cgroup", "Agroup", "Dgroup", "D115", "D111"]
	expes   = ["actin_biological", "conA_biological", "dapi_biological"]
	data    = {}
	for rep in reps:
		for expe in expes:
			filename = strain+"_"+str(rep)+"_"+expe+".csv"
			f = open("csv/"+filename, "r")
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
					if var not in data[cell_id] and var != "cell_id":# and var != "Dgroup":
						data[cell_id][var] = float(l[header[var]])
					#elif var not in data[cell_id] and var != "cell_id" and var == "Dgroup":
					#	data[cell_id][var] = l[header[var]]
				l = f.readline()
			f.close()
	#-------------------#
	# 2) Write new data #
	#-------------------#
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
			line += str(data[cell_id][var])+" "
		line = line.strip(" ")+"\n"
		f.write(line)
	f.close()
	

##################
#      MAIN      #
##################

strains = load_strain_names()
reps    = [1,2,3,4,5]

os.system("rm -rf merged")
os.mkdir("merged")

for strain in strains:
	print ">>> merging "+strain
	merge_data(strain, reps)




