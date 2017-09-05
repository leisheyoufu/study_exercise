#-*- encoding=utf-8 -*-
# Load libraries
from sklearn.datasets import load_iris
import numpy as np
# 1.    Load the Iris data set
data = load_iris()
x = data['data']
# Let’s demonstrate how sampling is performed:
# 2.    Randomly sample 10 records from the loaded dataset
no_records = 10
x_sample_indx = np.random.choice(range(x.shape[0]),no_records)
print x[x_sample_indx,:]