import numpy as np

def display_shape(a):
    print
    print
    print "Number of elements in a = %d" % (a.size)
    print "Number of dimensions in a =%d" % (a.ndim)
    print "Rows and Columns in a ", a.shape
    print


# Matrix operations
# 0 1 2
# 3 4 5
# 6 7 8
a_matrix = np.arange(9).reshape(3,3)
b_matrix = np.arange(9).reshape(3,3)

# [3 12 21]     0+1+2, 3+4+5, 6+7+8
print "a_matrix, row sum", a_matrix.sum(axis=1)

display_shape(a_matrix[::-1])
b_matrix = a_matrix[::-1]
# b_matrix
# 6 7 8
# 3 4 5
# 0 1 2

# Generate random number
genaral_random_numbers = np.random.randint(1,100, size=10)
print genaral_random_numbers
uniform_rnd_numbers = np.random.normal(loc=0.2, scale=0.2, size=(3,3))
print uniform_rnd_numbers
