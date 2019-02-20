import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Use latex interpreter in plot
plt.rc('text', usetex=True)
plt.rc('font', family='serif')

# Import data
file = "dynsys_data.csv"
data = pd.read_csv(file)

# Plot data
fig = plt.figure()
plt.plot(data.x, data.y, 'b')
plt.plot(data.x[0], data.y[0], 'ro')
plt.plot(data.x[len(data.x)-1], data.y[len(data.y)-1], 'r*', markersize=10)
plt.title('Dynamical System Solver - Trajectory', fontsize=14)
plt.xlabel('$x$', fontsize=14)
plt.ylabel('$y$', fontsize=14)
fig.savefig("trajectory.png")

plt.show()