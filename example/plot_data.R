
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

#options(show.error.messages=FALSE, warn=-1)
args <- commandArgs(trailingOnly = TRUE)
if (length(args) == 0)
{
  stop("You must give the figure name")
}
figurename = args[1]

plot_data <- function( vt, vbest, vmean, vsd, title )
{
	MINX = min(vt)
	MAXX = max(vt)
	MINY = min(c(vbest, vmean-vsd))
	MAXY = max(c(vbest, vmean+vsd))
	plot(x=NULL, xlim=c(MINX, MAXX), ylim=c(MINY, MAXY), main=title)
	lines(vt, vbest, col="lightgrey")
	lines(vt, vmean, col="cornflowerblue", lwd=2)
	lines(vt, vmean-vsd, col="cornflowerblue", lty=2)
	lines(vt, vmean+vsd, col="cornflowerblue", lty=2)
}

dbest = read.table("/Users/charlesrocabert/git/NoisyFGM/example/best.txt", h=T, sep=" ")
dmean = read.table("/Users/charlesrocabert/git/NoisyFGM/example/mean.txt", h=T, sep=" ")
dsd = read.table("/Users/charlesrocabert/git/NoisyFGM/example/sd.txt", h=T, sep=" ")

figurename = "/Users/charlesrocabert/git/NoisyFGM/example/output.png"
png(filename=figurename, pointsize=15, width=1500, height=1000)

par(mfrow=c(3,3), mar=c(2,2,2,2))

D = sqrt(-2*log(0.9))

### PLOT GENOTYPIC EUCLIDEAN DISTANCE ###
plot_data(dmean$t, dbest$dmu, dmean$dmu, dsd$dmu, "Genotypic distance")
abline(h=D, col="red")

### PLOT PHENOTYPIC EUCLIDEAN DISTANCE ###
plot_data(dmean$t, dbest$dp, dmean$dp, dsd$dp, "Phenotypic distance")
abline(h=D, col="red")

### PLOT GENOTYPIC FITNESS ###
plot_data(dmean$t, dbest$wmu, dmean$wmu, dsd$wmu, "Genotypic fitness")
abline(h=0.9, col="red")

### PLOT PHENOTYPIC FITNESS ###
plot_data(dmean$t, dbest$wp, dmean$wp, dsd$wp, "Phenotypic fitness")
abline(h=0.9, col="red")

### PLOT EIGEN VALUE ###
plot_data(dmean$t, dbest$EV, dmean$EV, dsd$EV, "Eigen value")

### PLOT EIGEN VALUE CONTRIBUTION ###
plot_data(dmean$t, dbest$EV_contrib, dmean$EV_contrib, dsd$EV_contrib, "Eigen value contribution")

### PLOT EIGEN VALUE DOT PRODUCT ###
plot_data(dmean$t, dbest$EV_dot_product, dmean$EV_dot_product, dsd$EV_dot_product, "Dot product")

dev.off()




