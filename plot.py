# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import matplotlib.pyplot as plt
import pandas as pd

funName = ["Michalewicz"]
deName = ["dim=2", "dim=10", "dim=30"]

font = {'family': 'normal',
        'weight': 'bold',
        'size': 24}

plt.rc('font', **font)

data = pd.read_csv(funName[0]+".csv")


i = 0
plt.plot(data["eva"], data["2"], label=deName[0], linewidth=3, alpha=1)
plt.plot(data["eva"], data["10"], label=deName[1], linewidth=3, alpha=1)
plt.plot(data["eva"], data["30"], label=deName[2], linewidth=3, alpha=1)

plt.xlabel("Function evaluations", fontsize=36, fontweight='bold')
plt.ylabel(funName[i] + " function values", fontsize=36, fontweight='bold')
plt.xlim(1, 300000)
#plt.ylim(0, 1.0E+18)
#plt.ylim(0, 1)
plt.title(funName[i] + ' function', fontsize=36, fontweight='bold')
plt.legend()
plt.grid(True)
plt.yscale("log")
# plt.yscale("symlog")

fig = plt.gcf()
fig.set_size_inches(16, 12)
fig.savefig(funName[i] + '.jpg', dpi=100)

plt.clf()
