#-*- encoding=utf-8 -*-
# Load Libraries
from sklearn.datasets import load_iris
from sklearn.preprocessing import Imputer
import numpy as np
import numpy.ma as ma
# 1. Load Iris Data Set
data = load_iris()
x = data['data']
y = data['target']
# Make a copy of hte original x value
x_t = x.copy()
# 2.    Introduce missing values into second row
x_t[2,:] = np.repeat(0,x.shape[1])
# Let’s see some data imputation in action:
# 3.    Now create an imputer object with strategy as mean,
# i.e. fill the missing values with the mean value of the missing column.
imputer = Imputer(missing_values=0,strategy="mean")
x_imputed = imputer.fit_transform(x_t)
mask = np.zeros_like(x_t)
mask[2,:] = 1
x_t_m = ma.masked_array(x_t,mask)
print np.mean(x_t_m,axis=0)
print x_imputed[2,:]