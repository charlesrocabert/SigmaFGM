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

####################
# Merge replicates #
####################
def merge_replicates( strains, reps ):
	f = open("interpolated/BY4743_1.txt", "r")
	header = f.readline()
	f.close()
	for strain in strains:
		f = open("interpolated/"+strain+"_merged.txt", "w")
		f.write(header)
		for rep in reps:
			g = open("interpolated/"+strain+"_"+str(rep)+".txt", "r")
			l = g.readline()
			l = g.readline()
			while l:
				f.write(l)
				l = g.readline()
			g.close()
		f.close()


##################
#      MAIN      #
##################

strains = load_strain_names()
reps    = [1,2,3,4,5]

print "> Merge interpolated replicates"
merge_replicates(strains, reps)

