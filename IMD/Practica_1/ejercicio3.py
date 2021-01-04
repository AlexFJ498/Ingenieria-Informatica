# Implemente un programa Python que lea una matriz de número reales desde teclado de una dimensión dada. 
# A partir de la matriz leída debe calcular la siguiente información:
# - Máximo por filas y por columnas
# - Determinante de la matriz
# - Rango de la matriz

import numpy as np

# Construir matriz
filas = int(input("Número de filas: "))
columnas = int(input("Número de columnas: "))

matriz = np.zeros(shape=(filas, columnas))

for i in range(0, filas):
    for j in range(0, columnas):
        matriz[i, j] = float(input(f"matriz[{i}][{j}]: "))

print(matriz)

# Obtener el máximo de cada fila
for i in range(0, filas):
    print(f"Máximo de la fila {i}: {np.max(matriz[i, :])}")

# Obtener el máximo de cada columna
for i in range(0, columnas):
    print(f"Máximo de la columna {i}: {np.max(matriz[:, i])}")

# Obtener determinante
print(f"Determinante de la matriz: {np.linalg.det(matriz)}")

# Obtener rango
print(f"Rango de la matriz: {np.linalg.matrix_rank(matriz)}")