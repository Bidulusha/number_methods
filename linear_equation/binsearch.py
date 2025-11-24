from perfect_table import perfect_table_manager
def binsearch(fun, left, right, eps = 0.00001):
    ptm = perfect_table_manager(['left', 'right', 'center', 'y'])
    while True:
        center = left + (right - left) / 2
        num = fun(center)
        #print('left =', left, 'right =', right,'center =', center, 'y =', num)
        ptm.add_line([left, right, center, num])
        if abs(num) < 0.00001:
            print('ans =', center)
            break
        else:
            if num > 0:
                right = center
            else:
                left = center