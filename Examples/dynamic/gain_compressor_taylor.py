
from sympy import Symbol, log, sqrt, series, exp

K = Symbol("K")
S = Symbol("S")
softness = Symbol("softness")
x = Symbol("x")

def f(x):
    return 10 * log (K * (1 + x)) / log(10)

def g(x):
    return -(S-1)/(20*S) * (sqrt(f(x)**2 + softness**2) + f(x))
    
def h(x):
    return exp(g(x) * log(10))

poly = series(h(x), x, n=2)

print poly
print poly.coeff(1)
print poly.coeff(x)
