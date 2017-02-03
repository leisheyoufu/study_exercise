import numpy as np

a_list = [1,2,3]
an_array = np.array(a_list)
an_array = np.array(a_list, dtype=float)

# Creating matrices
a_listoflist = [[1,2,3],[5,6,7],[8,9,10]]
a_matrix = np.matrix(a_listoflist, dtype=float)

def display_shape(a):
    print
    print
    print "Number of elements in a = %d" % (a.size)
    print "Number of dimensions in a =%d" % (a.ndim)
    print "Rows and Columns in a ", a.shape
    print

display_shape(a_matrix)


