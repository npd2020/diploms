import matplotlib.pyplot as plt
import numpy as np
import math

data = np.genfromtxt("res.txt", delimiter=' ', dtype=np.float, skip_header=2)

print(np.sum(data[:,1]))
plt.plot(data[:,0], data[:,1], "r", label = "Gas")
plt.legend()
plt.title('Spectrum')
plt.xlabel('Energy (MeV)')
plt.ylabel('Counts')
plt.show()
