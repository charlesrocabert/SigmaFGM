setwd("/Users/charlesrocabert/git/SigmaFGM/example/")

plot_data <- function( g, m, v, title )
{
	RGX = range(g)
	RGY = range(c(m-v, m+v))
	plot(x=NULL, xlim=RGX, ylim=RGY, main=title)
	lines(g, m, col="tomato")
	#polygon(c(g, rev(g)), c(m-v, rev(m+v)), border=F, col=adjustcolor("tomato", alpha.f=0.3))
}

M = read.table("mean.txt", sep=" ", h=T)
V = read.table("sd.txt", sep=" ", h=T)
names(M)
# "t" "dg" "dp" "wg" "wp" "EV" "EV_contrib" "EV_dot_product" "r_mu" "r_sigma" "r_theta" 

N = length(M[,1])
M = M[10:N,]
V = V[10:N,]

par(mfrow=c(2,3), mar=c(2,2,2,2))
plot_data(M$g, M$dX, V$dX, "Euclidean distance")
plot_data(M$g, M$WX, V$WX, "Absolute fitness")
plot_data(M$g, M$EV, V$EV, "Max(EV)")
plot_data(M$g, M$EV_contrib, V$EV_contrib, "Contrib(EV)")
plot_data(M$g, M$EV_dot_product, V$EV_dot_product, "Dot(EV)")
#phase_portrait(M$dg, sqrt(M$EV))
