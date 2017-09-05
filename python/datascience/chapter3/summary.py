#-*- encoding=utf-8 -*-
# Load Libraries
from sklearn.datasets import load_iris
import numpy as np
from scipy.stats import trim_mean
# Load iris data
data = load_iris()
x = data['data']
y = data['target']
col_names = data['feature_names']
# Let’s now demonstrate how to calculate the mean, trimmed mean, and range values:
# 1.    Calculate and print the mean value of each column in the Iris dataset
print "col name,mean value"
for i,col_name in enumerate(col_names):
    print "%s,%0.2f"%(col_name,np.mean(x[:,i]))
print
# 2.    Trimmed mean calculation.
p = 0.1 # 10% trimmed mean
print
print "col name,trimmed mean value"
for i,col_name in enumerate(col_names):
    print "%s,%0.2f"%(col_name,trim_mean(x[:,i],p))
print
# 3.    Data dispersion, calculating and display the range values.
print "col_names,max,min,range"
for i,col_name in enumerate(col_names):
    print "%s,%0.2f,%0.2f,%0.2f"% (col_name,max(x[:,i]),min(x[:,i]),max(x[:,i])-min(x[:,i]))
print
# Finally, we will show the variance, standard deviation, mean absolute deviation, and median absolute deviation calculations:
# 4.    Data dispersion, variance and standard deviation
print "col_names,variance,std-dev"
for i,col_name in enumerate(col_names):
    print "%s,%0.2f,%0.2f"%(col_name,np.var(x[:,i]),np.std(x[:,i]))
print
# 5.    Mean absolute deviation calculation
def mad(x,axis=None):
    mean = np.mean(x,axis=axis)
    return np.sum(np.abs(x-mean))/(1.0 * len(x))
print "col_names,mad"

for i,col_name in enumerate(col_names):
    print "%s,%0.2f"%(col_name,mad(x[:,i]))
print
# 6.    Median absolute deviation calculation
def mdad(x,axis=None):
    median = np.median(x,axis=axis)
    return np.median(np.abs(x-median))
print "col_names,median,median abs dev,inter quartile range"
for i,col_name in enumerate(col_names):
    iqr = np.percentile(x[:,i],75) - np.percentile(x[i,:],25)
    print "%s,%0.2f,%0.2f,%0.2f"%(col_name,np.median(x[:,i]), mdad(x[:,i]),iqr)
print