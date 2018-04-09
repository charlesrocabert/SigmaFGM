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

### Run the numerical analysis from the parameters set ###
def run_numerical_analysis( Xmin, Xmax, Xstep, Vemin, Vemax, Vestep, alpha, beta, Q, epsilon ):
	cmdline = "../build/bin/SigmaFGM_numerical_analysis"
	cmdline += " -xmin "+str(Xmin)
	cmdline += " -xmax "+str(Xmax)
	cmdline += " -xstep "+str(Xstep)
	cmdline += " -vemin "+str(Vemin)
	cmdline += " -vemax "+str(Vemax)
	cmdline += " -vestep "+str(Vestep)
	cmdline += " -alpha "+str(alpha)
	cmdline += " -beta "+str(beta)
	cmdline += " -Q "+str(Q)
	cmdline += " -epsilon "+str(epsilon)
	os.system(cmdline)
	#os.system("Rscript plot_data.R /Users/charlesrocabert/git/SigmaFGM/example/output.png")


############
#   MAIN   #
############

if __name__ == '__main__':
	X_MIN   = 0.0
	X_MAX   = 10.0
	X_STEP  = 0.1
	VE_MIN  = 0.0
	VE_MAX  = 10.0
	VE_STEP = 0.1
	ALPHA   = 0.5
	BETA    = 0.0
	Q       = 2.0
	EPSILON = 1e-6

	run_numerical_analysis(X_MIN, X_MAX, X_STEP, VE_MIN, VE_MAX, VE_STEP, ALPHA, BETA, Q, EPSILON)

