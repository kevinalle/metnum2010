import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

mpl.rcParams['legend.fontsize'] = 10

fig = plt.figure()
ax = Axes3D(fig)
x = np.linspace(-2, 2, 100)
y = x**2
z = -2*x


ax.plot(x, y, z, label='parametric curve')
ax.legend()

plt.show()
