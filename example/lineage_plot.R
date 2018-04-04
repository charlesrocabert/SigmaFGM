library("caTools")

setwd("/Users/charlesrocabert/git/SigmaFGM/example/")

get_ridge <- function( x, n, w )
{
	v = (x^2-n*w)/n
	v[v<0] = 0
	return(v)
}

plot_data <- function( t, m, title )
{
	RGX = range(t)
	RGY = range(m)
	plot(x=NULL, xlim=RGX, ylim=RGY, main=title)
	lines(t, m, col="tomato")
}

phase_portrait <- function( mu, sigma )
{
	plot(x=NULL, main="Phase portrait", xlim=c(0,4), ylim=c(0,4), type="l")
	x = seq(0,4,by=0.01)
	bottom = rep(0,length(x))
	top = rep(4,length(x))
	ridge = sqrt(get_ridge(x, 1, 1))
	polygon(c(x,rev(x)), c(bottom,rev(ridge)),border=F,col=adjustcolor("green",alpha.f=0.2))
	polygon(c(x,rev(x)), c(top,rev(ridge)),border=F,col=adjustcolor("tomato",alpha.f=0.2))
	lines(x, ridge, col="purple", lwd=2)
	lines(mu,sigma)
}

M = read.table("best_lineage.txt", sep=" ", h=T)

# "id" "t" "dg" "dp" "wg" "wp" "EV" "EV_contrib" "EV_dot_product" "r_mu" "r_sigma" "r_theta"

par(mfrow=c(3,3), mar=c(2,2,2,2))
plot_data(M$t, M$dg, "Euclidean distance")
plot_data(M$t, M$wg, "Absolute fitness")
plot_data(M$t, M$EV, "Max(EV)")
plot_data(M$t, M$EV_contrib, "Contrib(EV)")
plot_data(M$t, M$EV_dot_product, "Dot(EV)")
plot_data(M$t, runmean(M$r_mu, k=10), "r(mu)")
phase_portrait(M$dg, M$EV)
