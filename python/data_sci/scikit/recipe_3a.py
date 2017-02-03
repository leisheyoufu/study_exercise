from sklearn.datasets import load_iris,load_boston,make_classification,make_circles, make_moons

# Iris dataset
# The iris dataset is a classic and very easy multi-class classification dataset.
data = load_iris()
x = data['data']
y = data['target']
y_labels = data['target_names']
x_labels = data['feature_names']
print
print x.shape
print y.shape
print x_labels
print y_labels
# Boston dataset
data = load_boston()
x = data['data']
y = data['target']
x_labels = data['feature_names']
print
print x.shape
print y.shape
print x_labels

# make some classification dataset
x,y = make_classification(n_samples=50,n_features=5, n_classes=2)
print
print x.shape
print y.shape
print x[1,:]
print y[1]
# Some non linear dataset
x,y = make_circles()
import numpy as np
import matplotlib.pyplot as plt
plt.close('all')
plt.figure(1)
plt.scatter(x[:,0],x[:,1],c=y)
x,y = make_moons()
import numpy as np
import matplotlib.pyplot as plt
plt.figure(2)
plt.scatter(x[:,0],x[:,1],c=y)
plt.show()