#-*- encoding=utf-8 -*-
# Load libraries
from sklearn.datasets import load_iris
from sklearn.preprocessing import scale
import numpy as np
import matplotlib.pyplot as plt
# 1. Load iris dataset
data = load_iris()
x = data['data']
y = data['target']
col_names = data['feature_names']
# 2. Scale the variables, with mean value
x = scale(x,with_std=False)
x_ = x[1:26,]
y_labels = range(1,26)
#Let’s plot our heat map:
# 3. Plot the Heat map
plt.close('all')
plt.figure(1)
fig,ax = plt.subplots()
ax.pcolor(x_,cmap=plt.cm.Greens,edgecolors='k')
ax.set_xticks(np.arange(0,x_.shape[1])+0.5)
ax.set_yticks(np.arange(0,x_.shape[0])+0.5)
ax.xaxis.tick_top()
ax.yaxis.tick_left()
ax.set_xticklabels(col_names,minor=False,fontsize=10)
ax.set_yticklabels(y_labels,minor=False,fontsize=10)
plt.show()