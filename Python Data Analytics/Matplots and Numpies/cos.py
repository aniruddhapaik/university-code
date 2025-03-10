import matplotlib.pyplot as plt
import numpy as np
x = np.arange(0,30,np.pi/pow(2,32))
y = np.cos(x)
plt.plot(x,y)
plt.show()