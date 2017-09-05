import numpy as np

def display_shape(a):
    print
    print
    print "Number of elements in a = %d" % (a.size)
    print "Number of dimensions in a =%d" % (a.ndim)
    print "Rows and Columns in a ", a.shape
    print

# Create a matrix with all elements

ones_matrix = np.ones((3,3))   # 1
display_shape(ones_matrix)
# Create a matrix with all elements
zeros_matrix = np.zeros((3,3))
display_shape(zeros_matrix)

identity_matrix = np.eye(N=3,M=3,k=0)
display_shape(identity_matrix)
identity_matrix = np.eye(N=3,k=1)
display_shape(identity_matrix)