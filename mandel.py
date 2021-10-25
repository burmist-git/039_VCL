import sys
import numpy as np
import matplotlib.pyplot as plt
from ctypes import *

if len(sys.argv) > 2:
    print ("Too many arguments")
    print ("usage : %s <arch>?" % sys.argv[0])

arch = '' if len(sys.argv) < 2 else sys.argv[1]

libmandel = CDLL('libmandel%s.so' % arch)

#libmandel.boolPrint(c_int(True))

minx = -2.0
maxx = 0.5
nx = 2504
dx = (maxx - minx) / nx
miny = -1.0
maxy = 1.0
ny = 2000
dy = (maxy - miny) / ny

buffer = ((c_int * nx) * ny) ()
#print(type(buffer))
#print(buffer[2][2])

libmandel.mandel(buffer, c_float(minx), c_float(dx), c_uint(nx), c_float(miny), c_float(dy), c_uint(ny))

plt.imshow(buffer, cmap = plt.cm.prism, interpolation = 'none', extent = (minx, maxx, maxy, miny))
plt.xlabel("Re(c)")
plt.ylabel("Im(c)")
#plt.savefig("mandelbrot_python.svg")
plt.show()
