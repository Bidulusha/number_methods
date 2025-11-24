from linear_equation.perfect_table import perfect_table_manager
from system_of_linear_equation.matrix_utils import matrix_multiply, matrix_subtract, vector_norm, jacobian_inverse

def mei_with_jacobian(fun1, fun2, der1_x, der1_y, der2_x, der2_y, x0=0, y0=0, eps=0.001, max_iter=1000):
    """
    Метод простых итераций с использованием матрицы Якоби
    
    Parameters:
    fun1, fun2 - функции системы уравнений
    der1_x, der1_y - производные первой функции по x и y
    der2_x, der2_y - производные второй функции по x и y
    x0, y0 - начальное приближение
    eps - точность
    max_iter - максимальное число итераций
    """
    x, y = x0, y0
    ptm = perfect_table_manager(['x1', 'x2', '|xk - xk-1|', '|yk - yk-1|', 'Норма'])
    
    for i in range(max_iter):
        old_x, old_y = x, y
        
        # Вычисляем якобиан
        J = [
            [der1_x(x, y), der1_y(x, y)],
            [der2_x(x, y), der2_y(x, y)]
        ]
        
        # Вычисляем обратный якобиан
        try:
            J_inv = jacobian_inverse(J)
        except ValueError:
            print("Якобиан вырожден, метод расходится")
            return None
        
        # Вектор невязки
        F = [-fun1(x, y), -fun2(x, y)]
        
        # Коррекция
        delta = matrix_multiply(J_inv, [[F[0]], [F[1]]])
        
        # Новое приближение
        x = x + delta[0][0]
        y = y + delta[1][0]
        
        # Вычисляем норму разности
        dx = abs(x - old_x)
        dy = abs(y - old_y)
        norm = max(dx, dy)
        
        ptm.add_line([x, y, dx, dy, norm])
        
        if norm < eps:
            print(f'Решение найдено за {i+1} итераций:')
            print(f'x = {x}, y = {y}')
            print(f'f1(x,y) = {fun1(x, y)}, f2(x,y) = {fun2(x, y)}')
            return (x, y)
    
    print('Достигнут предел итераций')
    return (x, y)