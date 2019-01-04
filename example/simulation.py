#!/usr/bin/env python
# coding: utf-8

#***********************************************************************
# Copyright (C) 2016-2019
# Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
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
#***********************************************************************

import os
import sys
import math

### Run a simulation from the parameters set ###
def run_simulation( seed, stabt, simt, shutoffdistance, shutofftime, nbdim,
	alpha, beta, Q,
	popsize, initX, initVe, initTheta,
	mX, mVe, mTheta, sX, sVe, sTheta, noise,
	oneDshift ):
	cmdline = "../build/bin/SigmaFGM_simulation"
	cmdline += " -seed "+str(seed)
	cmdline += " -stabt "+str(stabt)
	cmdline += " -simt "+str(simt)
	cmdline += " -shutoffdistance "+str(shutoffdistance)
	cmdline += " -shutofftime "+str(shutofftime)
	cmdline += " -nbdim "+str(nbdim)
	cmdline += " -alpha "+str(alpha)
	cmdline += " -beta "+str(beta)
	cmdline += " -Q "+str(Q)
	cmdline += " -popsize "+str(popsize)
	cmdline += " -initx "+str(initX)
	cmdline += " -initve "+str(initVe)
	cmdline += " -inittheta "+str(initTheta)
	cmdline += " -mx "+str(mX)
	cmdline += " -mve "+str(mVe)
	cmdline += " -mtheta "+str(mTheta)
	cmdline += " -sx "+str(sX)
	cmdline += " -sve "+str(sVe)
	cmdline += " -stheta "+str(sTheta)
	cmdline += " -noise "+str(noise)
	if oneDshift:
		cmdline += " -oneDshift"
	os.system(cmdline)
	#os.system("Rscript plot_data.R /Users/charlesrocabert/git/SigmaFGM/example/output.png")


############
#   MAIN   #
############

if __name__ == '__main__':
	SEED             = 0
	STABILIZING_TIME = 0
	SIMULATION_TIME  = 200
	SHUTOFF_DISTANCE = 0
	SHUTOFF_TIME     = 0
	NB_DIMENSIONS    = 1
	ALPHA            = 0.5
	BETA             = 0.0
	Q                = 2.0
	POPULATION_SIZE  = 1000
	INITIAL_X        = 2.0/math.sqrt(float(NB_DIMENSIONS))
	INITIAL_VE       = 1e-15
	INITIAL_THETA    = 0.0
	M_X              = 1e-0
	M_VE             = 1e-0
	M_THETA          = 1e-0
	S_X              = 0.1/math.sqrt(float(NB_DIMENSIONS))
	S_VE             = 0.1
	S_THETA          = 0.1
	NOISE            = "FULL"
	ONED_SHIFT       = False

	run_simulation(SEED, STABILIZING_TIME, SIMULATION_TIME, SHUTOFF_DISTANCE, SHUTOFF_TIME, NB_DIMENSIONS,
		ALPHA, BETA, Q,
		POPULATION_SIZE, INITIAL_X, INITIAL_VE, INITIAL_THETA,
		M_X, M_VE, M_THETA, S_X, S_VE, S_THETA, NOISE,
		ONED_SHIFT )
