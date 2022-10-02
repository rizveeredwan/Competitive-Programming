import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(-10,20,2)
y = 2.414*x-0.83
plt.plot(x, y, '-r', label='y=2.414*x-0.83', color="red")
#plt.title('Graph of y=2x+4')
plt.xlabel('x', color='#1C2833')
plt.ylabel('y', color='#1C2833')
X = [1, 2, 3, 4, 5, 6]
Y = [ 1.5, 3.8, 6.7, 9, 11.2, 13.6]
for i in range(0, len(X)):
    plt.plot(X[i],Y[i], color="blue")

data = np.array([
    [1, 1.5],
    [2, 3.8],
    [3, 6.7],
    [4, 9],
    [5, 11.2],
    [6, 13.6],
])
x, y = data.T
plt.scatter(x,y)

"""
y = -5*x+3
plt.plot(x, y, '-r', label='y=-5*x+3', color="blue")

y = 12*x+4
plt.plot(x, y, '-r', label='y=12*x+4', color="black")
"""


plt.legend(loc='upper left')
plt.grid()
plt.show()
