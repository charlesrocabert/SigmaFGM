
import os
import time
import math
from matplotlib.pyplot import *
from matplotlib.patches import Ellipse

### Load z points ###
def load_all_z():
	z = {}
	z["t"] = []
	z["z1"]   = []
	z["z2"]   = []
	try:
		f = open("z_state.txt", "r")
	except:
		return -1
	l = f.readline()
	while l:
		l = l.strip("\n")
		l = l.split(" ")
		try:
			v1 = float(l[0])
			v2 = float(l[1])
			v3 = float(l[2])
		except:
			toto = 1
		else:
			z["t"].append(v1)
			z["z1"].append(v2)
			z["z2"].append(v3)
		l = f.readline()
	f.close()
	return z

### Load best state ###
def load_best_state():
	try:
		f = open("best_state.txt", "r")
	except:
		return -1, -1, -1, -1, -1, -1
	l = f.readline()
	l = l.strip("\n")
	l = l.split(" ")
	if len(l) == 6:
		t      = float(l[0])
		mu1    = float(l[1])
		mu2    = float(l[2])
		sigma1 = float(l[3])
		sigma2 = float(l[4])
		theta  = float(l[5])
		return t, mu1, mu2, sigma1, sigma2, theta
	return -1, -1, -1, -1, -1, -1
	

### Load mean state ###
def load_mean_state():
	try:
		f = open("mean_state.txt", "r")
	except:
		return -1, -1, -1, -1, -1, -1
	l = f.readline()
	l = l.strip("\n")
	l = l.split(" ")
	if len(l) == 6:
		t      = float(l[0])
		mu1    = float(l[1])
		mu2    = float(l[2])
		sigma1 = float(l[3])
		sigma2 = float(l[4])
		theta  = float(l[5])
		return t, mu1, mu2, sigma1, sigma2, theta
	return -1, -1, -1, -1, -1, -1

##################
#      MAIN      #
##################

ion()
files = []
increment = 1

current_t = 0
mu1mean = []
mu2mean = []
mu1best = []
mu2best = []

while True:
	tm, mu1m, mu2m, sigma1m, sigma2m, thetam = load_mean_state()
	tb, mu1b, mu2b, sigma1b, sigma2b, thetab = load_best_state()
	zall = load_all_z()
	if zall != -1 and tm != -1 and tb != -1 and tm == tb and current_t < tm:
		increment += 1
		current_t = tm
		mu1mean.append(mu1m)
		mu2mean.append(mu2m)
		mu1best.append(mu1b)
		mu2best.append(mu2b)
		clf()
		emean = Ellipse(xy=[mu1m, mu2m], width=2*sigma1m, height=2*sigma2m, angle=math.degrees(thetam))
		ebest = Ellipse(xy=[mu1b, mu2b], width=2*sigma1b, height=2*sigma2b, angle=math.degrees(thetab))
		fig   = figure(0)
		ax    = fig.add_subplot(111, aspect='equal')
		
		scatter(zall["z1"], zall["z2"], c="g", alpha=0.05)

		plot(mu1mean, mu2mean, "b")

		ax.add_artist(emean)
		emean.set_clip_box(ax.bbox)
		emean.set_alpha(0.7)
		emean.set_facecolor("b")

		ax.add_artist(ebest)
		ebest.set_clip_box(ax.bbox)
		ebest.set_alpha(0.2)
		ebest.set_facecolor("r")

		plot([0,0], [-4, 4], "r")
		plot([-4, 4], [0,0], "r")
		ax.set_xlim(-2, 2)
		ax.set_ylim(-2, 2)
		draw()

		fname = 'tmp/_tmp%03d.png' % increment
		savefig(fname)
		files.append(fname)

	time.sleep(0.5)

