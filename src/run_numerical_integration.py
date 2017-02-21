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
def integration_step_basic( path, dim, mu, sigma, rep, points, seed ):
	cmdline  = path
	cmdline += " -dim "+str(dim)
	cmdline += " -mu "+str(mu)
	cmdline += " -sigma "+str(sigma)
	#cmdline += " -rep "+str(rep)
	#cmdline += " -points "+str(points)
	#cmdline += " -seed "+str(seed)
	process  = subprocess.Popen([cmdline], stdout=subprocess.PIPE, shell=True)
	output   = process.stdout.read().strip("\n").split(" ")
	meanW    = float(output[0])
	sdW      = float(output[1])
	return meanW, sdW

### Parallel integration step execution ###
def integration_step_parallel( path, dim, mu, sigma, rep, points, seed ):
	cmdline  = path
	cmdline += " -dim "+str(dim)
	cmdline += " -mu "+str(mu)
	cmdline += " -sigma "+str(sigma)
	cmdline += " -rep "+str(rep)
	cmdline += " -points "+str(points)
	cmdline += " -seed "+str(seed)
	os.system(cmdline+" > /dev/null &")

### OAR integration step execution ###
def integration_step_OAR( path, dim, mu, sigma, rep, points, seed ):
	cmdline  = PATH
	cmdline += " -dim "+str(dim)
	cmdline += " -mu "+str(mu)
	cmdline += " -sigma "+str(sigma)
	cmdline += " -rep "+str(rep)
	cmdline += " -points "+str(points)
	cmdline += " -seed "+str(seed)
	f = open("run.sh", "w")
	f.write(cmdline+"\n")
	f.close()
	os.system("chmod 775 run.sh")
	execline = "oarsub -l /core=2,walltime=200:00:00 ./run.sh -p \"cluster=\'beagle\'\""
	os.system(execline)


##################
#      MAIN      #
##################
#os.system("rm -rf output_data")
#os.mkdir("output_data")

PATH     = "/Users/charlesrocabert/svn/noisyfgm/branches/development/beta/build/bin/integration_step_QAGI"
METHOD   = "basic"
NB_CORES = 2

NB_REPS   = 100
NB_POINTS = 1000000

NB_DIM = 50

MIN_MU  = 0.0
MAX_MU  = 10.0
STEP_MU = 0.01

MIN_SIGMA  = 0.0
MAX_SIGMA  = 10.0
STEP_SIGMA = 0.01

###########################################
# A) If the integration method is "basic" #
###########################################
if METHOD == "basic":
	f = open("basic_method_output.txt", "w")
	f.write("dim mu sigma meanW sdW\n")
	#dim = 1
	dim = 30
	while dim <= NB_DIM:
		mu = MIN_MU
		while mu <= MAX_MU:
			sigma = MIN_SIGMA
			while sigma <= MAX_SIGMA:
				print "> Dimension="+str(dim)+", Mu="+str(mu)+", Sigma="+str(sigma)+" ..."
				meanW, sdW = integration_step_basic(PATH, dim, mu, sigma, NB_REPS, NB_POINTS, random.randint(1,1e+6))
				f.write(str(dim)+" "+str(mu)+" "+str(sigma)+" "+str(meanW)+" "+str(sdW)+"\n")
				f.flush()
				#strmu = str(mu)
				#if strmu.endswith(".0"):
				#	strmu = strmu.split(".")[0]
				#strsigma = str(sigma)
				#if strsigma.endswith(".0"):
				#	strsigma = strsigma.split(".")[0]
				#filename = str(dim)+"_"+strmu+"_"+strsigma+".txt"
				#os.system("mv "+filename+" output_data/.")
				sigma += STEP_SIGMA
			mu += STEP_MU
		dim += 1

##############################################
# B) If the integration method is "parallel" #
##############################################
if METHOD == "parallel":
	count   = 1
	threads = {}
	dim = 1
	while dim <= NB_DIM:
		mu = MIN_MU
		while mu <= MAX_MU:
			sigma = MIN_SIGMA
			while sigma <= MAX_SIGMA:
				threads[count] = [0, dim, mu, sigma]
				count += 1
				sigma += STEP_SIGMA
			mu += STEP_MU
		dim += 1
	end     = False
	counter = 0
	while not end:
		time.sleep(1)
		end = True
		counter  = 0.0
		finished = 0.0
		running  = 0.0
		waiting  = 0.0
		for key in threads:
			counter += 1.0
			### If the thread is not run ###
			if threads[key][0] == 0:
				end = False
				if counter < NB_CORES:
					counter += 1
					threads[key][0] = 1
					integration_step_parallel(PATH, threads[key][1], threads[key][2], threads[key][3], NB_REPS, NB_POINTS, random.randint(1,1e+6))
					running += 1.0
				else:
					waiting += 1.0
			### If the thread is running ###
			elif threads[key][0] == 1:
				strmu = str(threads[key][2])
				if strmu.endswith(".0"):
					strmu = strmu.split(".")[0]
				strsigma = str(threads[key][3])
				if strsigma.endswith(".0"):
					strsigma = strsigma.split(".")[0]
				filename = str(threads[key][1])+"_"+strmu+"_"+strsigma+".txt"
				if os.path.exists(filename):
					counter -= 1
					threads[key][0] = 2
					os.system("mv "+filename+" output_data/.")
					finished += 1.0
				else:
					waiting += 1.0
					end = False
			### If the thread is finished ###
			elif threads[key][0] == 2:
				finished += 1.0
		print "Thread(s) running : "+str(counter)
		print "> Finished:"+str(finished/counter)+"%, Running:"+str(running/counter)+"%; Waiting:"+str(waiting/counter)+"%"

#########################################
# C) If the integration method is "OAR" #
#########################################
if METHOD == "OAR":
	dim = 1
	while dim <= NB_DIM:
		mu = MIN_MU
		while mu <= MAX_MU:
			sigma = MIN_SIGMA
			while sigma <= MAX_SIGMA:
				print "> Dimension="+str(dim)+", Mu="+str(mu)+", Sigma="+str(sigma)+" ..."
				integration_step_OAR(PATH, dim, mu, sigma, NB_REPS, NB_POINTS, random.randint(1,1e+6))
				sigma += STEP_SIGMA
			mu += STEP_MU
		dim += 1



