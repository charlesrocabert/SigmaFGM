#!/bin/bash
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

echo "#**********************************************************************"
echo "# Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard"
echo "#"
echo "# This program is free software: you can redistribute it and/or modify"
echo "# it under the terms of the GNU General Public License as published by"
echo "# the Free Software Foundation, either version 3 of the License, or"
echo "# (at your option) any later version."
echo "#"
echo "# This program is distributed in the hope that it will be useful,"
echo "# but WITHOUT ANY WARRANTY; without even the implied warranty of"
echo "# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
echo "# GNU General Public License for more details."
echo "#"
echo "# You should have received a copy of the GNU General Public License"
echo "# along with this program.  If not, see <http://www.gnu.org/licenses/>."
echo "#**********************************************************************"

echo ""
echo "###### SCRIPT 1 ######"
echo ""
python generate_data.py

echo ""
echo "###### SCRIPT 2 ######"
echo ""
python estimate_intrastrain_data.py

echo ""
echo "###### SCRIPT 3 ######"
echo ""
python merge_estimated_data.py

echo ""
echo "###### SCRIPT 4 ######"
echo ""
mkdir ./pic
mkdir ./pic/cor_strain
mkdir ./pic/cor_replicate
path=$(pwd)
Rscript analyze_data.R $path

