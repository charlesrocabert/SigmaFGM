
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

def run_solver( stabt, t, shutofffitness, shutofftime, seed, nbdim, nbpart,
	initmu, initsigma, inittheta, dmu, dsigma, dtheta,
	stats, stats2D,
	oneaxis, weight,
	nonoise, isotropic, norotation, qagi ):
	cmdline = "../build/bin/run_solver"
	cmdline += " -stabt "+str(stabt)
	cmdline += " -t "+str(t)
	cmdline += " -shutofffitness "+str(shutofffitness)
	cmdline += " -shutofftime "+str(shutofftime)
	cmdline += " -seed "+str(seed)
	cmdline += " -nbdim "+str(nbdim)
	cmdline += " -nbparticles "+str(nbpart)
	cmdline += " -initmu "+str(initmu)
	cmdline += " -initsigma "+str(initsigma)
	cmdline += " -inittheta "+str(inittheta)
	cmdline += " -dmu "+str(dmu)
	cmdline += " -dsigma "+str(dsigma)
	cmdline += " -dtheta "+str(dtheta)
	if stats:
		cmdline += " -statistics"
	if stats2D:
		cmdline += " -2Dstatistics"
	if oneaxis:
		cmdline += " -oneaxis"
	if weight:
		cmdline += " -weightfitness"
	if nonoise:
		cmdline += " -nonoise"
	if isotropic:
		cmdline += " -isotropicnoise"
	if norotation:
		cmdline += " -norotation"
	if qagi:
		cmdline += " -qagi"
	print cmdline
	os.system(cmdline)
	os.system("Rscript plot_data.R /Users/charlesrocabert/git/NoisyFGM/example/output.png")


############
#   MAIN   #
############
if __name__ == '__main__':
	STABILIZING_TIME = 0
	SIMULATION_TIME  = 1
	SHUTOFF_FITNESS  = 0.9
	SHUTOFF_TIME     = 20000
	SEED             = 0
	NB_DIMENSIONS    = 2
	NB_PARTICLES     = 1000
	INITIAL_MU       = 3.0
	INITIAL_SIGMA    = 1e-15
	INITIAL_THETA    = 0.0
	D_MU             = 0.01
	D_SIGMA          = 0.01
	D_THETA          = 0.01
	STATISTICS       = True
	STATISTICS_2D    = True
	ONE_AXIS         = True
	WEIGHT_FITNESS   = False
	NO_NOISE         = False
	ISOTROPIC_NOISE  = True
	NO_ROTATION      = True
	QAGI             = False

	run_solver(STABILIZING_TIME, SIMULATION_TIME, SHUTOFF_FITNESS, SHUTOFF_TIME,
		SEED, NB_DIMENSIONS, NB_PARTICLES, 
		INITIAL_MU, INITIAL_SIGMA, INITIAL_THETA, D_MU, D_SIGMA, D_THETA,
		STATISTICS, STATISTICS_2D,
		ONE_AXIS, WEIGHT_FITNESS,
		NO_NOISE, ISOTROPIC_NOISE, NO_ROTATION, QAGI)

