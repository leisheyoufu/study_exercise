#Alternate ways of creating arrays
import numpy as np
# 1. Leverage np.arrange to create numpy array

def display_shape(a):
    print
    print
    print "Number of elements in a = %d" % (a.size)
    print "Number of dimensions in a =%d" % (a.ndim)
    print "Rows and Columns in a ", a.shape
    print

created_array = np.arange(1,10,dtype=float)
display_shape(created_array)

# 2. Using np.linspace to create numpy array
created_array = np.linspace(1,10)
display_shape(created_array)

# 3. Create numpy arrays in using np.logspace
created_array = np.logspace(1,10,base=10.0)
display_shape(created_array)
