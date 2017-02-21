
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

d = read.table("/Users/charlesrocabert/svn/noisyfgm/branches/development/beta/example/output.txt", sep=" ", h=T)

MIN_DIM = 1
MAX_DIM = 10

MIN_MU = 0.0
MAX_MU = 10.0

MIN_SIGMA = 0.0
MAX_SIGMA = 10.0

colors = rainbow(MAX_DIM)

par(mfrow=c(1,2))

plot(x=NULL, xlim=c(MIN_MU, MAX_MU), ylim=c(MIN_SIGMA, MAX_SIGMA), xlab="Mu", ylab="Optimal sigma")
DIM = unique(d$dim)
for (dim in DIM)
{
	dd = d[d$dim==dim,]
	MU = unique(dd$mu)
	sigma = c()
	for (mu in MU)
	{
		md = dd[dd$mu==mu,]
		sigma = c(sigma, md$sigma[which(md$meanW==max(md$meanW))])
	}
	lines(MU, sigma, col=colors[dim], lwd=2)
}
legend("topleft", legend=DIM, col=colors, lwd=rep(2,MAX_DIM))

plot(x=NULL, xlim=c(MIN_MU, MAX_MU), ylim=c(0, 1), xlab="Mu", ylab="Best W")

DIM = unique(d$dim)
for (dim in DIM)
{
	dd = d[d$dim==dim,]
	MU = unique(dd$mu)
	w = c()
	for (mu in MU)
	{
		md = dd[dd$mu==mu,]
		w = c(w, max(md$meanW))
	}
	lines(MU, w, col=colors[dim], lwd=2)
}
legend("topright", legend=DIM, col=colors, lwd=rep(2,MAX_DIM))
