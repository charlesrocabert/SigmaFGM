# X Ve W1 lnW1 dW1_dX dW1_dVe dlnW1_dX dlnW1_dVe d2lnW1_dXdVE
# 1 2  3   4      5      6         7       8          9


library("RColorBrewer")
library("caTools")

setwd("/Users/charlesrocabert/git/SigmaFGM/example/")

plot_dW1_dX_isocline <- function( data )
{
	ld    = data[,c(1,2,3)]
	sigma = unique(ld[,2])
	sigma = sort(sigma)
	mu    = c()
	for (sigma_i in sigma)
	{
		ldlocal = ld[ld[,2]==sigma_i,]
		index   = which(ldlocal[,3]==max(ldlocal[,3]))
		if (length(index) > 1)
		{
			index = index[1]
		}
		mu = c(mu, ldlocal[index,1])
	}
	lines(mu, sigma, lwd=3, col="purple")
}

plot_dW1_dVe_isocline <- function( data )
{
	ld    = data[,c(1,2,3)]
	mu    = unique(ld[,1])
	mu    = sort(mu)
	sigma = c()
	for (mu_i in mu)
	{
		ldlocal = ld[ld[,1]==mu_i,]
		index   = which(ldlocal[,3]==max(ldlocal[,3]))
		if (length(index) > 1)
		{
			index = index[1]
		}
		sigma = c(sigma, ldlocal[index,2])
	}
	lines(mu, sigma, lwd=3, col="orange")
}

plot_dlnW1_dXdVe_isocline <- function( data )
{
	ld    = data[,c(1,2,7)]
	mu    = unique(ld[,1])
	mu    = sort(mu)
	sigma = c()
	for (mu_i in mu)
	{
		ldlocal = ld[ld[,1]==mu_i,]
		index   = which(ldlocal[,3]==min(ldlocal[,3]))
		if (length(index) > 1)
		{
			index = index[1]
		}
		sigma = c(sigma, ldlocal[index,2])
	}
	lines(mu, sigma, lwd=3, col="green")
}

d = read.table("W1.txt", h=T, sep=" ")
names(d)
RGX = range(d$X)
RGY = range(d$Ve)
plot(x=NULL, xlim=RGX, ylim=RGY)

plot_dW1_dX_isocline(d)
plot_dW1_dVe_isocline(d)
plot_dlnW1_dXdVe_isocline(d)


