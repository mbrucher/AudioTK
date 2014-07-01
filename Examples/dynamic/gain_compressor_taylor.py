
from sympy import Symbol, log, sqrt, series, exp

K = Symbol("K")
S = Symbol("S")
slope = Symbol("slope")
x = Symbol("x")

def f(x):
    return 10 * log (K * (1 + x)) / log(10)

print series(f(x), x)

def g(x):
    return -(S-1)/(20*S) * (sqrt(f(x)**2 + slope**2) + f(x))
    
print series(g(x), x)

def h(x):
    return exp(g(x) * log(10))

print series(h(x), x)
