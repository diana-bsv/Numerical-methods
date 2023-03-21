import matplotlib.pyplot as plt
with open('out1.txt', 'r') as f:
    lines = f.readlines()
    x1 = [float(line.split()[0]) for line in lines]
    y1 = [float(line.split()[1]) for line in lines]
with open('out2.txt', 'r') as f:
    lines = f.readlines()
    x2 = [float(line.split()[0]) for line in lines]
    y2 = [float(line.split()[1]) for line in lines]

fig,ax = plt.subplots()
ax.set_xlim(min(x1)-1, max(x1)+1)
ax.set_ylim(min(y1)-1, max(y1)+1)

ax.set_xlabel('x')

plt.scatter(x1, y1, color = 'darkblue')
plt.plot(x2, y2, color = 'seagreen', label = 'Инт')

ax.legend()
ax.grid()

plt.show()
