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


### Run numerical function numerical analysis from the parameters set ###
def run_numerical_analysis( Xmin, Xmax, Xstep, Vemin, Vemax, Vestep, alpha, beta, Q, epsilon ):
	cmdline = "../build/bin/SigmaFGM_W1_numerical_analysis"
	cmdline += " -Xmin "+str(Xmin)
	cmdline += " -Xmax "+str(Xmax)
	cmdline += " -Xstep "+str(Xstep)
	cmdline += " -Vemin "+str(Vemin)
	cmdline += " -Vemax "+str(Vemax)
	cmdline += " -Vestep "+str(Vestep)
	cmdline += " -alpha "+str(alpha)
	cmdline += " -beta "+str(beta)
	cmdline += " -Q "+str(Q)
	cmdline += " -epsilon "+str(epsilon)
	os.system(cmdline)

############
#   MAIN   #
############

if __name__ == '__main__':
	X_MIN   = 0.0
	X_MAX   = 5.0
	X_STEP  = 0.01
	VE_MIN  = 0.0
	VE_MAX  = 5.0
	VE_STEP = 0.01
	EPSILON = 1e-3

	ALPHA_RANGE = [10.0]
	#ALPHA_RANGE = [0.01, 0.1, 0.5, 1.0, 10.0]
	#BETA_RANGE  = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
	BETA_RANGE  = [0.9]
	#Q_RANGE     = [2.0]
	Q_RANGE     = [10.0]

	for alpha in ALPHA_RANGE:
		for beta in BETA_RANGE:
			for q in Q_RANGE:
				print "> Alpha="+str(alpha)+", Beta="+str(beta)+", Q="+str(q)
				run_numerical_analysis(X_MIN, X_MAX, X_STEP, VE_MIN, VE_MAX, VE_STEP, alpha, beta, q, EPSILON)



