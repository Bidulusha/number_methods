from binsearch import *
from mei import *
from secant_method import *
from newton_method import *
from combined_method import *

def fun(x):
    return x*x*x -2*x -5

def der(x):
    return 3*x*x - 2

def der1(x):
    return 6*x

def der2(x):
    return 6

left = -10000
right = 10000 

# print('Метод половинного деления')
# binsearch(fun, left,right, 0.00000001)

# print('\n\nМетод простых итераций')
# mei(fun, der, -10, 0.000000001)

# print('Метод хорд')
# secant_method(fun, -10, 10, 0.0000001)

# print('\n\nМетод Ньютона')
# newthon_method(fun, der, -10, 0.0000000000001)

# print('\n\nКомбинированный метод')
# cm(fun, der, der1, -10, 10, 0.000000000001)