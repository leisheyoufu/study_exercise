import numpy as np

def display_shape(a):
    print
    print
    print "Number of elements in a = %d" % (a.size)
    print "Number of dimensions in a =%d" % (a.ndim)
    print "Rows and Columns in a ", a.shape
    print

# Array shaping
# The shape of the arrays can be controlled by the reshape function:
a_matrix = np.arange(9).reshape(3,3)
display_shape(a_matrix)