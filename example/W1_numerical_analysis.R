setwd("/Users/charlesrocabert/git/SigmaFGM/example/")

##################
#      MAIN      #
##################

fitn = read.table("fitness.txt", h=T, sep=" ")
iso1 = read.table("dW1_dVe_isocline.txt", h=T, sep=" ")
iso2 = read.table("dlnW1_dXdVe_isocline.txt", h=T, sep=" ")

N = length(fitn[,1])

x    = fitn[,1]
zero = rep(0.0, N)
maxi = rep(5.0, N)
RGX = range(iso1[,1])
RGY = range(c(iso1[,2], iso2[,2]))

plot(x=NULL, xlim=RGX, ylim=RGY, xlab="X", ylab="Ve")
polygon(c(x,rev(x)), c(iso1[,2],zero), border=F, col=adjustcolor("darkolivegreen3", alpha.f=0.4))
polygon(c(x,rev(x)), c(iso1[,2],maxi), border=F, col=adjustcolor("tomato", alpha.f=0.4))
polygon(c(x,rev(x)), c(iso2[,2],zero), border=F, col=adjustcolor("darkolivegreen3", alpha.f=0.5))
lines(x, iso1[,2], col="black", lwd=3)
lines(x, iso2[,2], col="black", lty=4, lwd=3)

legend("topleft", legend=c("dW1/dVe=0 isocline", "d2lnW1/dXdVe=0 isocline"), lty=c(1,4), lwd=c(3,3), bg="white")


