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
import numpy as np
import subprocess


##################
#      MAIN      #
##################

output = subprocess.Popen(["ls raw_data/ex37SingleCell130219"], shell=True, stdout=subprocess.PIPE)
output = output.stdout.read().strip("\n").split("\n")
STRAINS = {}
for folder in output:
	strain = folder.split("_")
	if strain[0] not in STRAINS:
		STRAINS[strain[0]] = 1
	else:
		STRAINS[strain[0]] += 1

f = open("strain_names.txt", "w")
for strain in STRAINS:
	f.write(strain+"\n")
f.close()

