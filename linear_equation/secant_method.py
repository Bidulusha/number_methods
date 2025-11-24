from perfect_table import perfect_table_manager 

def _get_koef(x1, y1, x2, y2):
    k = (y2 - y1)/(x2 - x1)
    return (k ,y1 - k * x1)

def _get_zero_point(k, b):
    return -b/k

def secant_method(fun, a, b, eps = 0.01):
    x = a
    num = fun(x)
    f0 = fun(b)
    ptm = perfect_table_manager(['x', 'f(x)'])
    while abs(num) >= eps:
        x = _get_zero_point(*_get_koef(x, num, b, f0))
        num = fun(x)
        ptm.add_line([x, num])
    print('ans =', x)
