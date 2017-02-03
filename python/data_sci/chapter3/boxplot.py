#-*- encoding=utf-8 -*-
# Load Libraries
from sklearn.datasets import load_iris
import matplotlib.pyplot as plt
# Load Iris dataset
data = load_iris()
x = data['data']
plt.close('all')
# Let’s demonstrate how to create a box-and-whisker plot:
# Plot the box and whisker
fig = plt.figure(1)
ax = fig.add_subplot(111)
ax.boxplot(x)
ax.set_xticklabels(data['feature_names'])
plt.show()