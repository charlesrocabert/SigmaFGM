#!/usr/bin/env python
# coding: utf-8

#***********************************************************************
# Copyright (C) 2016-2018
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
	popsize, initmu, initsigma, inittheta,
	mmu, msigma, mtheta, smu, ssigma, stheta, noise,
	oneDshift ):
	cmdline = "../build/bin/SigmaFGM_run"
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
	cmdline += " -initmu "+str(initmu)
	cmdline += " -initsigma "+str(initsigma)
	cmdline += " -inittheta "+str(inittheta)
	cmdline += " -mmu "+str(mmu)
	cmdline += " -msigma "+str(msigma)
	cmdline += " -mtheta "+str(mtheta)
	cmdline += " -smu "+str(smu)
	cmdline += " -ssigma "+str(ssigma)
	cmdline += " -stheta "+str(stheta)
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
	STABILIZING_TIME = 1000
	SIMULATION_TIME  = 100000
	SHUTOFF_DISTANCE = 0
	SHUTOFF_TIME     = 0
	NB_DIMENSIONS    = 2
	ALPHA            = 0.5
	BETA             = 0.0
	Q                = 2.0
	POPULATION_SIZE  = 1000
	INITIAL_MU       = 4.0/math.sqrt(float(NB_DIMENSIONS))
	INITIAL_SIGMA    = 1e-15
	INITIAL_THETA    = 0.0
	M_MU             = 1e-3
	M_SIGMA          = 1e-3
	M_THETA          = 1e-3
	S_MU             = 0.1/math.sqrt(float(NB_DIMENSIONS))
	S_SIGMA          = 0.1
	S_THETA          = 0.1
	NOISE            = "FULL"
	ONED_SHIFT       = False

	run_simulation(SEED, STABILIZING_TIME, SIMULATION_TIME, SHUTOFF_DISTANCE, SHUTOFF_TIME, NB_DIMENSIONS,
		ALPHA, BETA, Q,
		POPULATION_SIZE, INITIAL_MU, INITIAL_SIGMA, INITIAL_THETA,
		M_MU, M_SIGMA, M_THETA, S_MU, S_SIGMA, S_THETA, NOISE,
		ONED_SHIFT )

