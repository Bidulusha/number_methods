from linear_equation.perfect_table import perfect_table_manager

def mei_slu(fun, eps=0.001, max_iter=1000, relaxation=0.5):
    x = -1.0
    y = 0.5
    ptm = perfect_table_manager(['x1', 'x2', '|xk - xk-1|', '|yk - yk-1|'])
    
    for i in range(max_iter):
        old_x, old_y = x, y
        
        new_x, new_y = fun(x, y)
        
        x = old_x + relaxation * (new_x - old_x)
        y = old_y + relaxation * (new_y - old_y)
        
        ptm.add_line([x, y,abs(new_x - old_x), abs(new_y - old_y)])
        
        if abs(old_x - x) < eps and abs(old_y - y) < eps:
            print(f'Решение найдено за {i+1} итераций:')
            print(f'x = {x}, y = {y}')
            return (x, y)
    
    print('Достигнут предел итераций')
    return (x, y)