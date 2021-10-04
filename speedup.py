import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("speedup.csv")

threads = df["num_threads"]
times = df["time_ms"]

fig, ax = plt.subplots()
ax.plot(threads, times)
ax.set(xlabel='Number of threads',
       ylabel='Compute time (ms)',
       title='Speedup factor')
ax.grid()

fig.savefig("speedup.png")
