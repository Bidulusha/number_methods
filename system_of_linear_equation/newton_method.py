from linear_equation.perfect_table import perfect_table_manager


#Main function
def newton_method(fun1, fun2, der1_x, der1_y, der2_x, der2_y, x01 = 0, x02 = 0, eps = 0.001, max_iter = 1000):
    new_x, new_y = x01, x02
    ptm = perfect_table_manager(['x1', 'x2', '|xk-xk-1|', '|yk-yk-1|'])
    for i in range(max_iter):
        x, y = new_x, new_y

        a11 = der2_y(x, y)
        a12 = -der1_y(x, y)
        a21 = -der2_x(x, y)
        a22 = der1_x(x, y)
        d = a22 * a11 - a12 * a21

        new_x = x - (a11 * fun1(x, y) + a12 * fun2(x, y))/ d 
        new_y = y - (a21*fun1(x,y) + a22 * fun2(x,y)) / d

        ptm.add_line([x, y,abs(new_x - x), abs(new_y - y)])

        if abs(new_x - x) < eps and abs(new_y - y) < eps:
            print(f'Решение найдено за {i+1} итераций:')
            print(f'x = {new_x}, y = {new_y}')
            return (new_x, new_y)
        
    print('Достигнут предел итерации')
    return None


