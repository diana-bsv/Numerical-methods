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
 
a = 1
b = 10
K = 9

x = np.linspace(a, b, 90)
y = (b**4-a**4)*5.0

c=(b-a)/K

fig,ax = plt.subplots()
ax.set_xlim(min(x2)-1, max(x2)+1)
ax.set_ylim(min(y2)-1, max(y2)+1)

ax.grid()

ax.set_xlabel('x')

plt.plot(x,(x**4)*5.0)
plt.scatter(x1, y1, color = 'darkblue', label = 'h')
plt.scatter(x2, y2, color = 'red', label = 'Рунге')

ax.legend()

plt.show()
