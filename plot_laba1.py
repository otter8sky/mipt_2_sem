import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

# в данном файле накидан код для построения графиков для всех трёх частей лабы в рандомном порядке (иногда с пояснениями)
def input_file(method):
    x, y = [], []
    with open(f'output\{method}.txt', 'r') as f:
        for line in f:
            numbers = line.strip().split('\t')
            x.append(float(numbers[0]))
            y.append(float(numbers[1]))
    return np.array(y), np.array(x)

fig, axs = plt.subplots(1, 2, figsize=(8, 5))
# в третьей части у нас будет 1 график (на нём 3 набора точек)
colors = ['orange', 'red', 'blue', 'purple', 'green', 'brown', 'gray']

# для первой части лабы
def model_1(x, a, b):
    return a * np.log(x) + b

def model_2(x, a, b):
    return a * x + b

# для второй части лабы
def model_3(x, a, b, c):
    return a * x**2 + b * x + c

def quadratic_approximation(x, y):
  A = np.column_stack([x**2, x, np.ones(len(x))])
  b = y
  coefficients, residuals, rank, singular_values = np.linalg.lstsq(A, b, rcond=None)
  a, b_coeff, c = coefficients
  return a, b_coeff, c

x_linear, y_linear = input_file("out_linear_pair4")
# для первой части лабы
# y_binar = y_binar / 1e6

# для второй части лабы
x_linear = x_linear / 10000
y_linear = x_linear / 5000

x_quadric, y_quadric = input_file("out_quadric_pair4")
x_quadric = x_quadric / 10000
y_quadric = y_quadric / 1e6

axs[1].scatter(x_quadric, y_quadric, color=colors[1], s=20, alpha=0.75)
axs[0].scatter(x_linear, y_linear, color=colors[4], s=20, alpha=0.75)

# для третьей части лабы
# x_A, y_A = inp("out_A2_new")
# y_A = y_A / 1000000
# x_B, y_B = inp("out_B2_new")
# y_B = y_B / 1000000
# x_C, y_C = inp("out_C2_new")
# y_C = y_C / 1000000

#для третьей части лабы
# axs.scatter(x_A, y_A, color=colors[3], label="Стратегия А", s=20, alpha=0.75)
# axs.scatter(x_B, y_B, color=colors[4], label="Стратегия В", s=20, alpha=0.75)
# axs.scatter(x_C, y_C, color=colors[1], label="Стратегия С", s=20, alpha=0.75)

# для третьей части лабы
# axs.legend()
# axs.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)
# axs.set_ylabel("t, с")
# axs.set_xlabel("size")

# для первой части лабы:
#coef_binar, _ = curve_fit(model_1, x_binar, y_binar)
#coef_linear, _ = curve_fit(model_2, x_linear, y_linear)

# для второй части лабы:
coef_linear_pair, _ = curve_fit(model_3, x_quadric, y_quadric)
coef_binar_pair, _ = curve_fit(model_2, x_linear, y_linear)

x_th = np.linspace(min(x_linear), max(x_linear), 50)
y_th_binar = model_2(x_th, *coef_binar_pair)
a, b, c = quadratic_approximation(x_quadric, y_quadric)
y_th_linar = model_3(x_th, a, b, c)

axs[0].plot(x_th, y_th_binar, color=colors[4], linestyle='--', linewidth=1.5, alpha=0.8)
axs[1].plot(x_th, y_th_linar, color=colors[1], linestyle='--', linewidth=1.5, alpha=0.8)
axs[1].grid(True, linestyle='--', linewidth=0.5, alpha=0.7)
axs[0].grid(True, linestyle='--', linewidth=0.5, alpha=0.7)

axs[0].set_title("Линейный")
axs[1].set_title("Перебор")

axs[0].set_xlabel("size/10^4")
axs[0].set_ylabel("t, мкс")

axs[1].set_xlabel("size/10^4")
axs[1].set_ylabel("t, мс")
plt.tight_layout()

# для первой части лабы:
plt.savefig(r'plot.pdf')
# для второй части лабы:
plt.savefig(r'plot_pair_new.pdf')
plt.show()
