# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from sympy import symbols, Matrix, simplify

a10, a20, a30, a11, a21, a31, a12, a22, a32, a42, a03, a23, a43, a04, a44 = symbols("a10 a20 a30 a11 a21 a31 a12 a22 a32 a42 a03 a23 a43 a04 a44")

M = Matrix([[0, a10, a20, a30, 0], [0, a11, a21, a31, 0], [0, a12, a22, a32, a42], [a03, 0, a23, 0, a43], [a04, 0, 0, 0, a44]])

M_det = M.det()
M_inv = M.inverse_ADJ()

print(M_det)

print(simplify(M_inv * M_det))
