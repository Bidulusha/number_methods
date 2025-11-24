from perfect_table import perfect_table_manager

def __mei(fun, lmbd, last, ptm : perfect_table_manager, eps):
    xi = last - lmbd * fun(last)
    while abs(fun(xi)) >= eps:
        ptm.add_line([last, fun(last), xi])
        last = xi
        xi = last - lmbd * fun(last)

    print('ans =', xi)

def mei(fun, der, x0, eps = 0.000001):
    ptm = perfect_table_manager(['xi', 'f(xi)', 'xi + 1'])
    lmbd = 1 / der(x0)
    __mei(fun, lmbd, x0, ptm, eps)