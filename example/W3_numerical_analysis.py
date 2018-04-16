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
def run_numerical_analysis( Xbarmin, Xbarmax, Xbarstep, Vebarmin, Vebarmax, Vebarstep, Vgx, Vge, alpha, beta, Q, epsilon ):
	cmdline = "../build/bin/SigmaFGM_W3_numerical_analysis"
	cmdline += " -Xbarmin "+str(Xbarmin)
	cmdline += " -Xbarmax "+str(Xbarmax)
	cmdline += " -Xbarstep "+str(Xbarstep)
	cmdline += " -Vebarmin "+str(Vebarmin)
	cmdline += " -Vebarmax "+str(Vebarmax)
	cmdline += " -Vebarstep "+str(Vebarstep)
	cmdline += " -Vgx "+str(Vgx)
	cmdline += " -Vge "+str(Vge)
	cmdline += " -alpha "+str(alpha)
	cmdline += " -beta "+str(beta)
	cmdline += " -Q "+str(Q)
	cmdline += " -epsilon "+str(epsilon)
	os.system(cmdline)

############
#   MAIN   #
############

if __name__ == '__main__':
	XBAR_MIN   = 0.0
	XBAR_MAX   = 5.0
	XBAR_STEP  = 0.05
	VEBAR_MIN  = 0.0
	VEBAR_MAX  = 5.0
	VEBAR_STEP = 0.05
	VGX        = 0.1
	VGE        = 0.1
	ALPHA      = 0.5
	BETA       = 0.0
	Q          = 2.0
	EPSILON    = 1e-3
	run_numerical_analysis(XBAR_MIN, XBAR_MAX, XBAR_STEP, VEBAR_MIN, VEBAR_MAX, VEBAR_STEP, VGX, VGE, ALPHA, BETA, Q, EPSILON)



