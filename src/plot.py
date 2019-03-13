import sys
import json
import numpy as np
import matplotlib.pyplot as plt

# Use latex interpreter in plot
plt.rc('text', usetex=True)
plt.rc('font', family='serif')

# Import data
data = json.load(open('data/' + sys.argv[1], 'r'))

# Create figure
fig = plt.figure()
plt.title('Particle Advection', fontsize=14)
plt.xlabel('$x$', fontsize=14)
plt.ylabel('$y$', fontsize=14)

# Iterate through particles
for i in data['parts']:
    # Read data into array
    x = np.array(i['x'])
    y = np.array(i['y'])

    # Plot data
    plt.plot(x, y)
    plt.plot(x[0], y[0], 'ro', markersize=5)
    plt.plot(x[-1], y[-1], 'r*', markersize=5)

# Save figure
fig.savefig("data/advection.png")

plt.show()