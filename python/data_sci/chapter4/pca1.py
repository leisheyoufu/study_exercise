import numpy as np
from sklearn.datasets import load_iris
from sklearn.preprocessing import scale
import scipy
import matplotlib.pyplot as plt
# Load Iris data
data = load_iris()
x = data['data']
y = data['target']
# Since PCA is an unsupervised method, we will not be using the target variable y
# scale the data such that mean = 0 and standard deviation = 1
x_s = scale(x,with_mean=True,with_std=True,axis=0)
# Calculate correlation matrix
x_c = np.corrcoef(x_s.T)
# Find eigen value and eigen vector from correlation matrix
eig_val,r_eig_vec = scipy.linalg.eig(x_c)
print 'Eigen values \n%s'%(eig_val)
print '\n Eigen vectors \n%s'%(r_eig_vec)
# Select the first two eigen vectors.
w = r_eig_vec[:,0:2]
# # Project the dataset in to the dimension
# from 4 dimension to 2 using the right eignen vector
x_rd = x_s.dot(w)
# Scatter plot the new two dimensions
plt.figure(1)
plt.scatter(x_rd[:,0],x_rd[:,1],c=y)
plt.xlabel("Component 1")
plt.ylabel("Component 2")
# Now, we will proceed to Standardize this data, with a zero mean and standard deviation of one, we will leverage the numpyscorr_coef function to find the correlation matrix:
x_s = scale(x,with_mean=True,with_std=True,axis=0)
x_c = np.corrcoef(x_s.T)
# We will then do the Eigenvalue decomposition and project our Iris data on the first two principal Eigenvectors. Finally, we will plot the dataset in the reduced space:
eig_val,r_eig_vec = scipy.linalg.eig(x_c)
print 'Eigen values \n%s'%(eig_val)
print '\n Eigen vectors \n%s'%(r_eig_vec)

# Select the first two eigen vectors.
w = r_eig_vec[:,0:2]
# # Project the dataset in to the dimension
# from 4 dimension to 2 using the right eignen vector
x_rd = x_s.dot(w)
# Scatter plot the new two dimensions
plt.figure(1)
plt.scatter(x_rd[:,0],x_rd[:,1],c=y)
plt.xlabel("Component 1")
plt.ylabel("Component 2")
plt.show()