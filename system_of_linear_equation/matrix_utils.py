def matrix_multiply(A, B):
    """Умножение матриц A * B"""
    rows_A = len(A)
    cols_A = len(A[0])
    cols_B = len(B[0])
    
    result = [[0 for _ in range(cols_B)] for _ in range(rows_A)]
    
    for i in range(rows_A):
        for j in range(cols_B):
            for k in range(cols_A):
                result[i][j] += A[i][k] * B[k][j]
    
    return result

def matrix_subtract(A, B):
    """Вычитание матриц A - B"""
    return [[A[i][j] - B[i][j] for j in range(len(A[0]))] for i in range(len(A))]

def vector_norm(v):
    """Норма вектора"""
    return max(abs(x) for x in v)

def jacobian_inverse(J):
    """Обращение матрицы 2x2 (якобиана)"""
    a, b, c, d = J[0][0], J[0][1], J[1][0], J[1][1]
    det = a * d - b * c
    
    if abs(det) < 1e-12:
        raise ValueError("Якобиан вырожден")
    
    return [[d/det, -b/det], [-c/det, a/det]]