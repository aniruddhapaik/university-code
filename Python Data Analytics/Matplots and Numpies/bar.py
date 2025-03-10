import matplotlib.pyplot as plt
import numpy as np

while True:
    val = np.random.randint(1, 10, 10)
    plt.bar(range(len(val)), val)
    plt.draw()
    plt.pause(0.5)
    plt.clf()