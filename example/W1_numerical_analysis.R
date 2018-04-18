setwd("/Users/charlesrocabert/git/SigmaFGM/example/")

##################
#      MAIN      #
##################

d = read.table("0.5_0_2.txt", h=T, sep=" ")

N = length(d[,1])

x    = d[,1]
zero = rep(0.0, N)
maxi = rep(5.0, N)
RGX = range(x)
RGY = range(c(d[,2], d[,3]))

plot(x=NULL, xlim=RGX, ylim=RGY, xlab="X", ylab="Ve")
polygon(c(x,rev(x)), c(d[,2],zero), border=F, col=adjustcolor("darkolivegreen3", alpha.f=0.4))
polygon(c(x,rev(x)), c(d[,2],maxi), border=F, col=adjustcolor("tomato", alpha.f=0.4))
polygon(c(x,rev(x)), c(d[,3],zero), border=F, col=adjustcolor("darkolivegreen3", alpha.f=0.5))
lines(x, d[,2], col="black", lwd=3)
lines(x, d[,3], col="black", lty=4, lwd=3)

legend("topleft", legend=c("dW(X,VE)/dVe=0 isocline", "d2lnW(X,VE)/dXdVe=0 isocline", "Increasing Ve decreases W(X,VE)", "Increasing Ve increases W(X,VE)", "Increasing Ve increases dlnW(X,VE)/dX"), lty=c(1,4,0,0,0), lwd=c(3,3,3,3,3), pt.cex=c(2), pch=c(NA,NA,15,15,15), col= c("black","black","tomato","darkolivegreen3","darkolivegreen"), bg="white", inset=0.01)





