import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
from scipy.interpolate import interp1d
from scipy.interpolate import CubicSpline

def load_data(filename):
    data = np.loadtxt(filename, delimiter='\t')
    data = data[(data[:, 1] > 0) & (data[:, 0] > 0)]
    n = np.log(data[:, 1])
    t = np.log(data[:, 0])

    # mask = t > 2

    # n = n[mask]
    # t = t[mask]

    # n = data[:, 1]
    # t = data[:, 0]
    return n, t


def linear_model(x, a, b):
    return a * x + b

part = 1

files1 = ["laba 2/output/strategy_1.txt", "laba 2/output/strategy_2.txt", "laba 2/output/strategy_3.txt"]
labels1 = ["Линейное", "Блочное", "Экспоненциальное"]
colors1 = ["darkgreen", "purple", "orange"]

files2 = ["laba 2/output/push.txt", "laba 2/output/poll.txt"]
labels2 = ["Добавление элемента", "Чтение элемента"]
colors2 = ["orange", "purple"]

files3 = ["laba 2/output/3_push_front.txt", "laba 2/output/3_push_back.txt", "laba 2/output/3_poll_back.txt", "laba 2/output/3_poll_front.txt"]
labels3 = ["Добавление элемента в начало", "Добавление последнего элемента", "Чтение последнего элемента", "Чтение первого элемента"]
colors3 = ["red", "blue", "green", "orange"]

many_files = [files1, files2, files3]
many_colors = [colors1, colors2, colors3]
many_labels = [labels1, labels2, labels3]

files = many_files[part-1]
colors = many_colors[part-1]
labels = many_labels[part-1]

fig, ax = plt.subplots(figsize=(8, 5))

for i, file in enumerate(files):
    x, y = load_data(file)
    ax.scatter(x, y, color=colors[i], s=10, alpha=0.75, label=labels[i])
    if i == 2:
        mask = y > 2
        x = x[mask]
        y = y[mask]
    if i == 0 and part == 2:
        mask = y > 8
        x = x[mask]
        y = y[mask]

    model = linear_model
    coef, _ = curve_fit(model, x, y)
    x_fit = np.linspace(min(x), max(x), 50)
    y_fit = model(x_fit, *coef)
    y_fit = y_fit.tolist()
    y_fit.append(coef[1]) 
    y_fit = np.array(y_fit)
    x_fit = x_fit.tolist() 
    x_fit.append(0)
    x_fit = np.array(x_fit)
    ax.plot(x_fit, y_fit, linestyle=':', color=colors[i], linewidth=1.5)
    print(labels[i], f"{coef[0]:.2f}")


ax.set_xlabel("$ln N$")
ax.set_ylabel("$ln T$")
ax.legend()
# ax.set_xscale("log")
# ax.set_yscale("log")

ax.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)

plt.tight_layout()
plt.savefig(r'laba 2\plots\plot_laba2_1_new.pdf')
plt.show()
