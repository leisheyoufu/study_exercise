import numpy as np

# The mgrid functionality can be used to get the coordinates in the m-dimension.
xx,yy,zz = np.mgrid[0:3,0:3,0:3]
# The ravel and flatten functions can be used to convert a matrix to
# a one-dimensional array
xx = xx.flatten()
yy = yy.flatten()
zz = zz.flatten()
print xx
print yy
print zz