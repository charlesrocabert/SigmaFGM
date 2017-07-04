
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

args <- commandArgs(trailingOnly = TRUE)
experiment_path = args[1]
print(experiment_path)
setwd(experiment_path)

library("ellipse")
library("corrplot")

### Get strain names from file ###
get_strain_names <- function()
{
	d = read.table("strain_names.txt", h=F)
	return(d[,1])
}

### Get strain data ###
get_strain_data <- function( strain )
{
	d = read.table(paste("corrected/centered_scaled_",strain,".txt",sep=""), h=T, sep=" ")
	return(as.matrix(d))
}

### Isolate data lines with Inf or NAs ###
isolate_bad_data <- function( data )
{
	Nrow = length(data[,1])
	new_data = c()
	for (i in seq(1,Nrow))
	{
		vec = data[i,]
		if (length(vec[is.na(vec)])==0 & length(vec[is.infinite(vec)])==0)
		{
			new_data = rbind(new_data, vec)
		}
	}
	return(new_data)
}

### Compute a correlation test on the entire COR ###
cor.mtest <- function( mat, conf.level = 0.95 )
{
  mat <- as.matrix(mat)
    n <- ncol(mat)
    p.mat <- lowCI.mat <- uppCI.mat <- matrix(NA, n, n)
    diag(p.mat) <- 0
    diag(lowCI.mat) <- diag(uppCI.mat) <- 1
    for(i in 1:(n-1)){
        for(j in (i+1):n){
            tmp <- cor.test(mat[,i], mat[,j], conf.level = conf.level)
            p.mat[i,j] <- p.mat[j,i] <- tmp$p.value
            lowCI.mat[i,j] <- lowCI.mat[j,i] <- tmp$conf.int[1]
            uppCI.mat[i,j] <- uppCI.mat[j,i] <- tmp$conf.int[2]
        }
    }
    return(list(p.mat, lowCI.mat, uppCI.mat))
}

### Plot noise correlations for interstrain axis PC1 and PC2 ###
plot_corr_mat <- function( V, SIGMA_1 )
{
	strains = get_strain_names()
	Nst = length(strains)
	colors = rainbow(Nst)
	for (i in seq(1, Nst))
	{
		strain = strains[i]
		png(filename=paste("pic/",strain,".png",sep=""), width=1000, height=1000)
		st = get_strain_data(strain)
		st_proj = st %*% V %*% SIGMA_1
		st_proj = isolate_bad_data(st_proj)
		COV = cor(st_proj)
		test = cor.mtest(st_proj, 1-0.05/666)
		corrplot(COV, method="circle", p.mat = test[[1]], insig = "pch")
		dev.off()
	}
}

### Compute mean correlations and plot 2 first PCs ###
plot_mean_best_noise <- function( V, SIGMA_1, MINX, MAXX, MINY, MAXY )
{
	### Compute mean cor and get PC1,PC2 ###
	strains = get_strain_names()
	Nst = length(strains)
	colors = rainbow(Nst)
	MEAN_COV = matrix(rep(0.0,Nst*Nst), nrow=Nst)
	for (i in seq(1, Nst))
	{
		strain = strains[i]
		st = get_strain_data(strain)
		st_proj = st %*% V %*% SIGMA_1
		st_proj = isolate_bad_data(st_proj)
		COV = cor(st_proj)
		MEAN_COV = MEAN_COV+COV
	}
	MEAN_COV = MEAN_COV/Nst
	COVPOS = abs(COV)
	diag(COVPOS) = 0.0
	maxi = which(COVPOS==max(COVPOS), arr.ind=T)
	PC1 = maxi[2,1]
	PC2 = maxi[2,2]
	### Plot data ###
	strains = get_strain_names()
	Nst = length(strains)
	colors = rainbow(Nst)
	png(filename=paste("pic/PC1_PC2.png",sep=""), width=1000, height=500)
	par(mfrow=c(1,2))
	### first plot ###
	plot(x=NULL, xlim=c(MINX, MAXX), ylim=c(MINY, MAXY), xlab="PC1", ylab="PC2")
	abline(h=0, lty=2)
	abline(v=0, lty=2)
	for (i in seq(1, Nst))
	{
		colors[i] = "cornflowerblue"
		strain    = strains[i]
		st        = get_strain_data(strain)
		st_proj   = st %*% V %*% SIGMA_1
		st_proj   = isolate_bad_data(st_proj)
		x         = mean(st_proj[,PC1])
		y         = mean(st_proj[,PC2])
		COV       = cov(st_proj[,c(PC1,PC2)])
		val       = diag(COV)
		COV       = diag(val, nrow=length(val), ncol=length(val))
		ELLIPS    = ellipse(COV*0.005, centre=c(x, y))
		polygon(ELLIPS, col=rgb(0.9,0.9,1), border=colors[i], lwd=2)
		text(x, y, strain, cex=0.5, font=2)
	}
	### Second plot ###
	plot(x=NULL, xlim=c(MINX, MAXX), ylim=c(MINY, MAXY), xlab="PC1", ylab="PC2")
	abline(h=0, lty=2)
	abline(v=0, lty=2)
	for (i in seq(1, Nst))
	{
		colors[i] = "tomato"
		strain    = strains[i]
		st        = get_strain_data(strain)
		st_proj   = st %*% V %*% SIGMA_1
		st_proj   = isolate_bad_data(st_proj)
		x         = mean(st_proj[,PC1])
		y         = mean(st_proj[,PC2])
		COV       = cov(st_proj[,c(PC1,PC2)])
		ELLIPS    = ellipse(COV*0.005, centre=c(x, y))
		polygon(ELLIPS, col=rgb(1,0.9,0.9), border=colors[i], lwd=2)
		text(x, y, strain, cex=0.5, font=2)
	}
	dev.off()
}


##################
#      MAIN      #
##################

INTER = read.table("interstrain_means/centered_scaled_mean.txt", sep=" ", h=T)

N = length(INTER[1,])
colnames = names(INTER)[2:N]
rownames = INTER[,1]
INTER = as.matrix(INTER[,2:N])
colnames(INTER) = colnames
rownames(INTER) = rownames

SVD = svd(INTER)

SV = SVD$d
SIGMA = diag(SVD$d)
SIGMA_1 = diag(1/SVD$d)
U = as.matrix(SVD$u)
V = as.matrix(SVD$v)

plot_corr_mat(V, SIGMA_1)
plot_mean_best_noise(V, SIGMA_1, -0.6, 0.6, -0.6, 0.6)




