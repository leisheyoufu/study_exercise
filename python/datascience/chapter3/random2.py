# Load Libraries
import numpy as np
# 1.    Generate some random data for scaling
np.random.seed(10)
x = [np.random.randint(10,25)*1.0 for i in range(10)]
# Now, we will demonstrate scaling:
# 2.Define a function, which can perform min max scaling given a list of numbers
def min_max(x):
    return [round((xx-min(x))/(1.0*(max(x)-min(x))),2) for xx in x]
# 3.Perform scaling on the given input list.
print x
print min_max(x)