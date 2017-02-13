
#options(show.error.messages=FALSE, warn=-1)
args <- commandArgs(trailingOnly = TRUE)
if (length(args) == 0)
{
  stop("You must give the experiment path")
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

dbest = read.table("/Users/charlesrocabert/svn/noisyfgm/branches/development/beta/example/best.txt", h=T, sep=" ")
dmean = read.table("/Users/charlesrocabert/svn/noisyfgm/branches/development/beta/example/mean.txt", h=T, sep=" ")
dsd = read.table("/Users/charlesrocabert/svn/noisyfgm/branches/development/beta/example/sd.txt", h=T, sep=" ")

pdf(file=figurename, pointsize=15, width=10, height=6)

par(mfrow=c(2,3), mar=c(2,2,2,2))

### PLOT DISTANCE ###
plot_data(dmean$t, dbest$d, dmean$d, dsd$d, "Distance")

### PLOT FITNESS ###
plot_data(dmean$t, dbest$w, dmean$w, dsd$w, "Fitness")

### PLOT EIGEN VALUE ###
plot_data(dmean$t, dbest$EV, dmean$EV, dsd$EV, "Eigen value")

### PLOT EIGEN VALUE CONTRIBUTION ###
plot_data(dmean$t, dbest$EV_contrib, dmean$EV_contrib, dsd$EV_contrib, "Eigen value contribution")

### PLOT EIGEN VALUE DOT PRODUCT ###
plot_data(dmean$t, dbest$EV_dot_product, dmean$EV_dot_product, dsd$EV_dot_product, "Dot product")

dev.off()




