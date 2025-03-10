import matplotlib.pyplot as plt
import numpy as np
val = np.random.randint(1, 10, 20)
plt.figure(figsize=(10, 5))
plt.errorbar(range(len(val)), val, val, fmt='o', capsize=6)
plt.show()