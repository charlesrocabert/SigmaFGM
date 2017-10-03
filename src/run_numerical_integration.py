
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
import time
import random
import subprocess

### Basic integration step execution ###
def integration_step_local( path, dim, mu, sigma ):
	cmdline  = path
	cmdline += " -dim "+str(dim)
	cmdline += " -mu "+str(mu)
	cmdline += " -sigma "+str(sigma)
	process  = subprocess.Popen([cmdline], stdout=subprocess.PIPE, shell=True)
	output   = process.stdout.read().strip("\n").split(" ")
	value    = float(output[0])
	error    = float(output[1])
	return value, error


##################
#      MAIN      #
##################

PATH       = "/Users/charlesrocabert/git/SigmaFGM/build/bin/integration_step_QAGI"

NB_DIM     = 1

MIN_MU     = 0.0
MAX_MU     = 10.0
STEP_MU    = 0.05

MIN_SIGMA  = 0.0
MAX_SIGMA  = 10.0
STEP_SIGMA = 0.05


f = open("integration_output.txt", "w")
f.write("dim mu sigma value error\n")
count = 0
dim   = 1
while dim <= NB_DIM:
	mu = MIN_MU
	while mu <= MAX_MU:
		sigma = MIN_SIGMA
		while sigma <= MAX_SIGMA:
			count += 1
			if count%1000 == 0:
				print "> Dimension="+str(dim)+", Mu="+str(mu)+", Sigma="+str(sigma)+" ..."
			value, error = integration_step_local(PATH, dim, mu, sigma)
			f.write(str(dim)+" "+str(mu)+" "+str(sigma)+" "+str(value)+" "+str(error)+"\n")
			f.flush()
			sigma += STEP_SIGMA
		mu += STEP_MU
	dim += 1

