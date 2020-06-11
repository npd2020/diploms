import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt("res.txt", delimiter=' ', dtype=np.float, skip_header=3)
fon = np.genfromtxt("fon.txt", delimiter=' ', dtype=np.float, skip_header=3)

plt.yscale('log')
plt.plot(data[:,0], (data[:,1]+1)/10000000, "r", label = "Mustard gas")
plt.plot(fon[:,0], (fon[:,1]+1)/10000000, "k", label = "Background")
plt.legend()
plt.title('Spectrum')
plt.xlabel('Energy (MeV)')
plt.ylabel('Counts/neutron')
plt.show()
