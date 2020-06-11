import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt("res.txt", delimiter=' ', dtype=np.float, skip_header=2)
fon = np.genfromtxt("fon.txt", delimiter=' ', dtype=np.float, skip_header=2)

np.savetxt('data1.txt', data[:,0], fmt='%.2f')
np.savetxt('data2.txt', data[:,1]+1, fmt='%.d')
np.savetxt('fon1.txt', fon[:,0], fmt='%.2f')
np.savetxt('fon2.txt', fon[:,1]+1, fmt='%.d')


