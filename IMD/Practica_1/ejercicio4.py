# Implemente un programa Python que lea una matriz de número enteros desde teclado de una dimensión dada. 
# A partir de la matriz leída debe calcular la siguiente información:
# - Moda de la matriz
# - Media de todos los elementos de la matriz

import numpy as np
from scipy import stats

# Construir matriz
filas = int(input("Número de filas: "))
columnas = int(input("Número de columnas: "))

matriz = np.zeros(shape=(filas, columnas))

for i in range(0, filas):
    for j in range(0, columnas):
        matriz[i, j] = int(input(f"matriz[{i}][{j}]: "))

print(matriz)

# Obtener moda
print(f"Moda de la matriz: {stats.mode(matriz, axis=None)[0][0]}")
print(f"Media de la matriz: {np.mean(matriz)}")