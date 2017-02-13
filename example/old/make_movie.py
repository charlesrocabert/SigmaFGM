
import os

os.system("mencoder 'mf://tmp/_tmp*.png' -mf type=png:fps=10 -ovc lavc -lavcopts vcodec=wmv2 -oac copy -o animation.mpg")
os.system("rm tmp/_tmp*.png")
