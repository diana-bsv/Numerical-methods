import matplotlib.pyplot as plt
import numpy as np
with open('out1.txt', 'r') as f:
    lines = f.readlines()
    x1 = [float(line.split()[0]) for line in lines]
    y1 = [float(line.split()[1]) for line in lines]
with open('out2.txt', 'r') as f:
    lines = f.readlines()
    x2 = [float(line.split()[0]) for line in lines]
    y2 = [float(line.split()[1]) for line in lines]
 
a = -3
b = 3
K = 3

x = np.linspace(a, b, 90)
y = np.power(x,3)

c=(b-a)/K

fig,ax = plt.subplots()
ax.set_xlim(min(x1)-1, max(x1)+1)
ax.set_ylim(min(y1)-1, max(y1)+1)

ax.set_xlabel('x')


for i in range(0, K+1):
    ax.vlines(a+c*i, min(y1)-10, max(y1)+10, color = 'paleturquoise')

plt.scatter(x1, y1, color = 'darkblue')
plt.plot(x2, y2, color = 'red', label = 'Инт')
plt.plot(x, y, color = 'seagreen', label = 'f(x)')

ax.legend()
ax.grid()

plt.show()
