import numpy as np

def swarm_gathering(cost, cen, ran, swarm_size=32, epochs=128):
    swarm = np.array([cen] + [cen + (np.random.randint(10000, size=len(cen))-5000)/10000*ran for _ in range(swarm_size-1)])
    for _ in range(epochs):
        fl = tuple(map(cost, swarm))
        best = swarm[fl.index(min(fl))]
        swarm += np.random.randint(5000, 30000, size=(swarm_size, len(cen)))/10000 * (best-swarm)
    fl = tuple(map(cost, swarm))
    return swarm[fl.index(min(fl))]

def momentum_swarm_gathering(cost, cen, ran, gamma=0.1, swarm_size=32, epochs=128):
    swarm = np.array([cen] + [cen + (np.random.randint(10000, size=len(cen))-5000)/10000*ran for _ in range(swarm_size-1)])
    fl = tuple(map(cost, swarm))
    bestp = swarm[fl.index(min(fl))]
    for _ in range(epochs):
        fl = tuple(map(cost, swarm))
        best = swarm[fl.index(min(fl))]
        move = np.random.randint(5000, 30000, size=(swarm_size, len(cen)))/10000 * (best-swarm)
        swarm += gamma*(best-bestp) + (1-gamma)*move
        bestp = best
    fl = tuple(map(cost, swarm))
    return swarm[fl.index(min(fl))]
