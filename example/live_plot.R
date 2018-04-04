setwd("/Users/charlesrocabert/git/SigmaFGM/example/")

get_ridge <- function( x, n, w )
{
	v = (x^2-n*w)/n
	v[v<0] = 0
	return(v)
}

plot_data <- function( t, m, v, title )
{
	RGX = range(t)
	RGY = range(c(m-v, m+v))
	plot(x=NULL, xlim=RGX, ylim=RGY, main=title)
	lines(t, m, col="tomato")
	polygon(c(t, rev(t)), c(m-v, rev(m+v)), border=F, col=adjustcolor("tomato", alpha.f=0.3))
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

M = read.table("mean.txt", sep=" ", h=T)
V = read.table("sd.txt", sep=" ", h=T)

# "t" "dg" "dp" "wg" "wp" "EV" "EV_contrib" "EV_dot_product" "r_mu" "r_sigma" "r_theta" 

N = length(M[,1])
M = M[10:N,]
V = V[10:N,]

par(mfrow=c(2,3), mar=c(2,2,2,2))
plot_data(M$t, M$dg, V$dg, "Euclidean distance")
plot_data(M$t, M$wg, V$wg, "Absolute fitness")
plot_data(M$t, M$EV, V$EV, "Max(EV)")
plot_data(M$t, M$EV_contrib, V$EV_contrib, "Contrib(EV)")
plot_data(M$t, M$EV_dot_product, V$EV_dot_product, "Dot(EV)")
phase_portrait(M$dg, sqrt(M$EV))
