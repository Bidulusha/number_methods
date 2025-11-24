from perfect_table import perfect_table_manager

def __nm(fun, der, last, ptm : perfect_table_manager, eps): 
    while abs(fun(last)) >= eps:
        last = last - fun(last) / der(last)
        ptm.add_line([last, fun(last)])
    print('ans =', last)

def newthon_method(fun, der, x0, eps = 0.000001):
    ptm = perfect_table_manager(['xi', 'f(xi)'])
    __nm(fun, der, x0, ptm, eps)