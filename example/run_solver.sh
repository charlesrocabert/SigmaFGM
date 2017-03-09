
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

../build/bin/run_solver \
-stabt          0 \
-t              20000 \
-shutofffitness 0.9 \
-shutofftime    1000 \
-seed           123 \
-nbdim          2 \
-nbparticles    5000 \
-initmu         3 \
-initsigma      1 \
-inittheta      0.0 \
-dmu            0.01 \
-dsigma         0.01 \
-dtheta         0.01 \
-statistics \
-2Dstatistics \
-oneaxis \
-isotropicnoise \
#-nonoise \
#-norotation \
#-weightfitness \

Rscript plot_data.R /Users/charlesrocabert/git/NoisyFGM/example/output.png


