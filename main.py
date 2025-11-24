import math
from system_of_linear_equation.mei import mei_with_jacobian
from system_of_linear_equation.newton_method import newton_method

# Функции системы
def fun1(x, y):
    return x**(2.0/3.0) + y**(2.0/3.0) - 4

def fun2(x, y):
    return x**2 - 2*y

# Для простого МПИ (преобразованная система)
def fun_simple(x01, x02):
    term = 4 - x02**(2.0/3.0)
    x1 = (term)**(3.0/2.0)
    x2 = x01*x01 / 2.0
    return (x1, x2)

# Производные для якобиана
def der1_x(x, y):
    return 2.0 / (3.0 * x**(1.0 / 3.0))

def der1_y(x, y):
    return 2.0 / (3.0 * y**(1.0 / 3.0))

def der2_x(x, y):
    return 2.0 * x

def der2_y(x, y):
    return -2.0

def main():

    print('Метод простых итераций с Якобианом')
    mei_with_jacobian(fun1, fun2, der1_x, der1_y, der2_x, der2_y, 
                     x0=1, y0=1, eps=0.000000000001)
    print()

    print('Метод Ньютона')
    newton_method(fun1, fun2, der1_x, der1_y, der2_x, der2_y, 
                 x01=1, x02=1, eps=0.000000000001)
    print()

if __name__ == '__main__':
    main()