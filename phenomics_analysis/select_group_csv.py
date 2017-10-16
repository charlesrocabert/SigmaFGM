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

def get_Dgroup( header, line ):
	linesplit = line.strip("\r\n").split("\t")
	for i in range(len(header)):
		if header[i] == "Dgroup":
			return linesplit[i]
	print "Error when parsing line for Dgroup. Exit."
	sys.exit()

def get_cell_id( header, line ):
	linesplit = line.strip("\r\n").split("\t")
	for i in range(len(header)):
		if header[i] == "cell_id":
			return int(linesplit[i])
	print "Error when parsing line for cell_id. Exit."
	sys.exit()

def get_cell_ids( strain, reps, Dgroups ):
	cell_ids = {}
	for rep in reps:
		cell_ids[rep] = []
		filename = strain+"_"+str(rep)+"_dapi_biological.csv"
		f = open("csv-test/"+filename, "r")
		l = f.readline()
		header = l.strip("\r\n").split("\t")
		l = f.readline()
		while l:
			Dgroup = get_Dgroup(header, l)
			if Dgroup in Dgroups:
				cell_ids[rep].append(get_cell_id(header, l))
			l = f.readline()
		f.close()
	return cell_ids

def rewrite_files( strain, reps, cell_ids ):
	expes = ["actin_biological", "conA_biological", "dapi_biological"]
	for expe in expes:
		for rep in reps:
			newfile = ""
			filename = strain+"_"+str(rep)+"_"+expe+".csv"
			f = open("csv-test/"+filename, "r")
			l = f.readline()
			header = l.strip("\r\n").split("\t")
			newfile += l
			l = f.readline()
			while l:
				if get_cell_id(header, l) in cell_ids[rep]:
					newfile += l
				l = f.readline()
			f.close()
			f = open("csv-test/"+filename, "w")
			f.write(newfile)
			f.close()

##################
#      MAIN      #
##################

strains = load_strain_names()
reps    = [1,2,3,4,5]
Dgroups = ["A1", "B"]

for strain in strains:
	cell_ids = get_cell_ids(strain, reps, Dgroups)
	rewrite_files(strain, reps, cell_ids)
