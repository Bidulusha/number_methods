from perfect_table import perfect_table_manager

def cm(fun, der, der1, a, b, eps = 0.0001):
    ptm = perfect_table_manager(['a', 'b', '(a - b) / 2'])
    while abs(a - b) > 2*eps:
        ptm.add_line([a, b, (a + b) / 2])
        if fun(a) * der1(a) < 0:
            a = a - fun(a)*(a - b)/(fun(a) - fun(b))
        else:
            a = a - fun(a) / der(a)
        
        if fun(b) * der1(b) < 0:
            b = b - fun(b) * (b - a) / (fun(b) - fun(a))
        else:
            b = b - fun(b) / der(b)
    print('ans =', (a + b) / 2)
    return (a + b) / 2
