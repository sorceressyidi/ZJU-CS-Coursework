import numpy as np
from sympy import symbols, log,exp
from scipy.integrate import odeint

def fun(t, y):
    return np.array([y[1],t*exp(t)-t-y[0]+2*y[1] ])

def exact_sol(t):
    return 1/6*t**3*exp(t)-t*exp(t)+2*exp(t)-t-2
def adams_predictor_corrector(f, y0, t):
    h = t[1] - t[0]
    n = len(t)
    y = np.zeros((n, len(y0)))
    y[0] = y0

    # Use 4th order Runge-Kutta method to get the initial values
    for i in range(3):
        k1 = h * f(t[i], y[i])
        k2 = h * f(t[i] + 0.5 * h, y[i] + 0.5 * k1)
        k3 = h * f(t[i] + 0.5 * h, y[i] + 0.5 * k2)
        k4 = h * f(t[i] + h, y[i] + k3)
        y[i + 1] = y[i] + (k1 + 2 * k2 + 2 * k3 + k4) / 6

    for i in range(3, n - 1):
        # Adams-Bashforth predictor
        y_pred = y[i] + h / 24 * (55 * f(t[i], y[i]) - 59 * f(t[i - 1], y[i - 1]) + 37 * f(t[i - 2], y[i - 2]) - 9 * f(t[i - 3], y[i - 3]))

        # Adams-Moulton corrector (implicit step)
        y[i + 1] = y[i] + h / 24 * (9 * f(t[i + 1], y_pred) + 19 * f(t[i], y[i]) - 5 * f(t[i - 1], y[i - 1]) + f(t[i - 2], y[i - 2]))

    return y

# Set up the time points
t_range = [0, 1]
h = 0.1
t = np.arange(t_range[0], t_range[1] + h, h)

# Set up the initial condition
y0 = np.array([0, 0])

# Use Adams predictor-corrector to solve the ODE
y_pred_corr = adams_predictor_corrector(fun, y0, t)

# Calculate the exact solution for comparison
exact_solution = np.array([exact_sol(ti) for ti in t])

# Display results
print('Results with initial values from 4th order Runge-Kutta method:')
for i in range(len(t)):
    u1_exact = exact_sol(t[i])
    error = abs(u1_exact - y_pred_corr[i, 0])
    print(f't = {t[i]}, Approximate u1 = {y_pred_corr[i, 0]}, Exact u1 = {u1_exact}, Approximate u2 = {y_pred_corr[i, 1]}, Error = {error}')




