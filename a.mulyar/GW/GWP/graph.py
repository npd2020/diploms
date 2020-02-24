import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt("res.txt", delimiter=' ', dtype=np.float, skip_header=2)

plt.plot(data[:,0], data[:,1])
plt.title('Spectrum')
plt.xlabel('Energy(MeV)')
plt.ylabel('N')
plt.show()
