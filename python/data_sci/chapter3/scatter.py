#-*- encoding=utf-8 -*-
# Load Librarires
from sklearn.datasets import load_iris
import numpy as np
import matplotlib.pyplot as plt
import itertools
# 1. Load Iris dataset
data = load_iris()
x = data['data']
y = data['target']
col_names = data['feature_names']
# We will proceed with demonstrating with a scatter plot:
# 2.Perform a simple scatter plot.
# Plot 6 graphs, combinations of our columns, sepal length, sepal width,
# petal length and petal width.
plt.close('all')
plt.figure(1)
# We want a plot with
# 3 rows and 2 columns, 3 and 2 in
# below variable signifies that.
subplot_start = 321
col_numbers = range(0,4)
# Need it for labeling the graph
col_pairs = itertools.combinations(col_numbers,2)
plt.subplots_adjust(wspace = 0.5)
for col_pair in col_pairs:
    plt.subplot(subplot_start)
    # [:,0] 取嵌套array中每个array的第一个元素,  [:,1] 取嵌套array中每个array的第二个元素
    plt.scatter(x[:,col_pair[0]],x[:,col_pair[1]],c=y)  # scatter  散点图
    plt.xlabel(col_names[col_pair[0]])
    plt.ylabel(col_names[col_pair[1]])
    subplot_start+=1

plt.show()