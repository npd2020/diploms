import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt("res.txt", delimiter=' ', dtype=np.float, skip_header=2)
fon = np.genfromtxt("fon.txt", delimiter=' ', dtype=np.float, skip_header=2)

plt.plot(data[:,0], data[:,1], "r", label = "Gas")
plt.plot(fon[:,0], fon[:,1], "k--", label = "Background")
plt.legend()
plt.title('Spectrum')
plt.xlabel('Energy (MeV)')
plt.ylabel('Counts')
plt.show()
