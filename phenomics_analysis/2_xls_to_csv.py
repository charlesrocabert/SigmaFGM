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


##################
#      MAIN      #
##################

strains = load_strain_names()
reps    = 5
expes   = ["actin_biological", "conA_biological", "dapi_biological"]

os.system("rm -rf csv")
os.mkdir("csv")

for strain in strains:
	for rep in range(1,reps+1):
		for exp in expes:
			filename = "raw_data/ex37SingleCell130219/"+strain+"_"+str(rep)+"/"+strain+"_"+str(rep)+"_"+exp+".xls"
			print filename
			os.system("/Applications/LibreOffice.app/Contents/MacOS/soffice --headless --convert-to csv --outdir csv/ "+filename) 
			time.sleep(0.1)




