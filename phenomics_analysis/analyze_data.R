
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
setwd(experiment_path)

library("ellipse")
library("corrplot")

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

### Compute colSds ###
colSds <- function( data )
{
	sds = rep(0.0, dim(data)[2])
	for (col in seq(1,dim(data)[2]))
	{
		sds[col] = sd(data[,col])
	}
	return(sds)
}

### Load strain names ###
load_strain_names <- function()
{
	d = read.table("strain_names.txt", h=F, sep=" ")
	return(d[,1])
}

### Get replicate data ###
get_replicate_data <- function( strain, rep )
{
	d = read.table(paste("interpolated/",strain,"_",rep,".txt",sep=""), h=T, sep=" ")
	return(as.matrix(d))
}

### Get merged strain data ###
get_strain_data <- function( strain )
{
	d = read.table(paste("interpolated/",strain,"_merged.txt",sep=""), h=T, sep=" ")
	return(as.matrix(d))
}

### Clean data (remove zero lines) ###
clean_data <- function( data )
{
	new_data = c()
	dims     = dim(data)
	for (i in seq(1,dims[1]))
	{
		if (sum(abs(data[i,]))!=0)
		{
			new_data = rbind(new_data, data[i,])
		}
	}
	return(as.matrix(new_data))
}

### Plot each strain correlation matrix including a Pearson test ###
plot_corr_mat_per_strain <- function( strains, V, D_1 )
{
	for (strain in strains)
	{
		png(filename=paste("./pic/cor_strain/",strain,".png",sep=""), width=1000, height=1000)
		Mx = get_strain_data(strain)
		Px = Mx %*% V %*% D_1
		Px = clean_data(Px)
		COR = cor(Px)
		test = cor.mtest(Px, 1-0.05/28)
		corrplot(COR, method="circle", p.mat = test[[1]], insig = "pch")
		dev.off()
	}
}

### Compute the mean correlation matrix among all replicates ###
compute_mean_cor_matrix <- function( strains, reps, V, D_1, CUT )
{
	M     = matrix(rep(0.0, CUT*CUT), nrow=CUT)
	count = 0.0
	for (strain in strains)
	{
		for (rep in reps)
		{
			Mx    = get_replicate_data(strain, rep)
			Px    = Mx %*% V %*% D_1
			Px    = clean_data(Px)
			COV   = cor(Px)
			M     = M+COV
			count = count+1.0
		}
	}
	M = M/count
	vec    = c()
	vnames = c()
	for (i in seq(1,CUT))
	{
		if (i+1 <= CUT)
		{
			for (j in seq(i+1,CUT))
			{
				vec    = c(vec, abs(M[i,j]))
				vnames = c(vnames, paste(i,"-",j,sep=""))
			}
		}
	}
	names(vec) = vnames
	vec = sort(vec, decreasing=T)
	png(filename=paste("./pic/mean_correlations.png",sep=""), width=1000, height=500)
	par(mfrow=c(1,2))
	barplot(vec, names.arg=names(vec), col="cornflowerblue", las=2)
	corrplot(COV, method="circle")
	dev.off()
}

### Compute mean correlations and plot 2 first PCs ###
plot_mean_PC1_PC2 <- function( strains, V, D_1, MINX, MAXX, MINY, MAXY )
{
	PC1 = 1
	PC2 = 2
	png(filename=paste("./pic/PC1_PC2.png",sep=""), width=1000, height=500)
	par(mfrow=c(1,2))
	### First plot ###
	plot(x=NULL, xlim=c(MINX, MAXX), ylim=c(MINY, MAXY), xlab="PC1", ylab="PC2", main="Noise structure with no observed correlations")
	abline(h=0, lty=2)
	abline(v=0, lty=2)
	for (strain in strains)
	{
		Mx      = get_strain_data(strain)
		Px      = Mx %*% V %*% D_1
		Px      = clean_data(Px)
		x       = mean(Px[,PC1])
		y       = mean(Px[,PC2])
		COV     = cov(Px[,c(PC1,PC2)])
		val     = diag(COV)
		COV     = diag(val, nrow=length(val), ncol=length(val))
		ELLIPSE = ellipse(COV*0.002, centre=c(x, y))
		polygon(ELLIPSE, col=rgb(1,0.9,0.9), border="tomato", lwd=2)
		text(x, y, strain, cex=0.5, font=2)
	}
	### Second plot ###
	plot(x=NULL, xlim=c(MINX, MAXX), ylim=c(MINY, MAXY), xlab="PC1", ylab="PC2", main="Observed noise structure")
	abline(h=0, lty=2)
	abline(v=0, lty=2)
	for (strain in strains)
	{
		Mx      = get_strain_data(strain)
		Px      = Mx %*% V %*% D_1
		Px      = clean_data(Px)
		x       = mean(Px[,PC1])
		y       = mean(Px[,PC2])
		COV     = cov(Px[,c(PC1,PC2)])
		ELLIPSE = ellipse(COV*0.002, centre=c(x, y))
		polygon(ELLIPSE, col=rgb(0.9,0.9,1), border="cornflowerblue", lwd=2)
		text(x, y, strain, cex=0.5, font=2)
	}
	dev.off()
}

### Plot singular values ###
plot_singular_values <- function( SV )
{
	png(filename=paste("./pic/SV.png",sep=""))
	plot(SV, pch=20, xlab="Singular value rank", ylab="Singular value", main="Ordered singular values")
	points(SV[1:8], col="cornflowerblue")
	abline(v=8.5, col="cornflowerblue", lty=2)
	dev.off()
}

### Plot correlation matrices per replicate ###
plot_corr_per_replicate <- function( strain, reps, V, D_1 )
{
	png(filename=paste("pic/cor_replicate/cor_",strain,".png",sep=""), width=1500, height=300)
	par(mfrow=c(1,5))
	Cmeans = c()
	Csds   = c()
	for (rep in reps)
	{
		### 1) Get replicate matrix ###
		Mx = get_replicate_data(strain, rep)
		Px = Mx %*% V %*% D_1
		Px = clean_data(Px)
		
		### 2) Plot correlation matrices ###
		COV    = cor(Px)
		corrplot(COV, method="circle")
	}
	dev.off()
}

### Plot mean noise structure per replicate ###
plot_mean_noise_per_replicate <- function( strain, reps, V, D_1 )
{
	Cmeans = c()
	for (rep in reps)
	{
		### 1) Get replicate matrix ###
		Mx = get_replicate_data(strain, rep)
		Px = Mx %*% V %*% D_1
		Px = clean_data(Px)
		
		### 2) Compute colMeans ###
		Cmeans = rbind(Cmeans, colMeans(Px))
	}
	plot(x=NULL, xlim=c(1,8), ylim=c(-0.7,0.7), main=strain)
	lines(Cmeans[1,], col="red", lwd=2)
	lines(Cmeans[2,], col="orange", lwd=2)
	lines(Cmeans[3,], col="yellow", lwd=2)
	lines(Cmeans[4,], col="green", lwd=2)
	lines(Cmeans[5,], col="blue", lwd=2)
	points(Cmeans[1,], col="red", pch=20)
	points(Cmeans[2,], col="orange", pch=20)
	points(Cmeans[3,], col="yellow", pch=20)
	points(Cmeans[4,], col="green", pch=20)
	points(Cmeans[5,], col="blue", pch=20)
}

### Plot noise sd structure per replicate ###
plot_sd_noise_per_replicate <- function( strain, reps, V, D_1 )
{
	Csds   = c()
	for (rep in reps)
	{
		### 1) Get replicate matrix ###
		Mx = get_replicate_data(strain, rep)
		Px = Mx %*% V %*% D_1
		Px = clean_data(Px)
		
		### 2) Compute colSds ###
		Csds   = rbind(Csds, colSds(Px))
	}
	plot(x=NULL, xlim=c(1,8), ylim=c(min(Csds), max(Csds)), main=strain)
	lines(Csds[1,], col="red", lwd=2)
	lines(Csds[2,], col="orange", lwd=2)
	lines(Csds[3,], col="yellow", lwd=2)
	lines(Csds[4,], col="green", lwd=2)
	lines(Csds[5,], col="blue", lwd=2)
	points(Csds[1,], col="red", pch=20)
	points(Csds[2,], col="orange", pch=20)
	points(Csds[3,], col="yellow", pch=20)
	points(Csds[4,], col="green", pch=20)
	points(Csds[5,], col="blue", pch=20)
}


##################
#      MAIN      #
##################

strains = load_strain_names()
reps    = c(1,2,3,4,5)

#----------------------------#
# 1) Compute SVD: M = U.D.V' #
#----------------------------#

### 1.1) Build M ###
M           = read.table("interstrain/centered_scaled_mean.txt", sep=" ", h=T)
nM          = length(M[1,])
Mcolnames   = names(M)[2: nM]
Mrownames   = M[,1]
M           = as.matrix(M[,2: nM])
colnames(M) = Mcolnames
rownames(M) = Mrownames

### 1.2) Compute SVD ###
SVD = svd(M)
SV  = SVD$d
D   = diag(SV)
D_1 = diag(1/SV)
U   = as.matrix(SVD$u)
V   = as.matrix(SVD$v)

### 1.3) Isolate significative singular values ###
CUT    = 8
SVcut  = SV[1:CUT]#*(sum(SV)/sum(SV[1:CUT]))
Dcut   = diag(SVcut)
D_1cut = diag(1/SVcut)
Ucut   = U[,1:CUT]
Vcut   = V[,1:CUT]

### 1.4) Plot various figures ###
print("> Plot singular values")
plot_singular_values(SV)

print("> Plot mean correlation matrices per strain")
plot_corr_mat_per_strain(strains, Vcut, D_1cut)

print("> Plot mean correlation matrix")
compute_mean_cor_matrix(strains, reps, Vcut, D_1cut, CUT)

print("> Plot phenotypic noise on PC1/PC2 axes")
VAL = 0.35
plot_mean_PC1_PC2(strains, Vcut, D_1cut, -VAL, VAL, -VAL, VAL)

print("> Plot correlation matrices per replicate")
for (strain in strains)
{
	plot_corr_per_replicate(strain, reps, Vcut, D_1cut)
}

print("> Plot mean phenotypic noise per replicate")
png(filename=paste("./pic/mean_phenotypic_noise.png",sep=""), width=1000, height=500)
par(mfrow=c(6,7), mar=c(2,2,2,2))
for (strain in strains)
{
	plot_mean_noise_per_replicate(strain, reps, Vcut, D_1cut)
}
dev.off()

print("> Plot phenotypic noise std-dev per replicate")
png(filename=paste("./pic/sd_phenotypic_noise.png",sep=""), width=1000, height=500)
par(mfrow=c(6,7), mar=c(2,2,2,2))
for (strain in strains)
{
	plot_sd_noise_per_replicate(strain, reps, Vcut, D_1cut)
}
dev.off()

