# Implemente un programa Python que genere aleatoriamente una matriz de valores reales de un tamaño indicado por teclado. 
# Sobre la matriz generada realice las siguientes operaciones:
# - Obtenga los valores máximos y mínimos de la matriz.
# - Use el producto escalar para obtener el ángulo formado por dos vectores fila o columna solicitados por teclado.

import numpy as np
import sys

print("Número de filas de la matriz: ")
filas = int(input())

print("Número de columnas de la matriz: ")
columnas = int(input())

# Genera una matriz con valores entre 0 y 1
matriz = np.random.rand(filas,columnas)
print(matriz)

print(f"\nValor máximo de la matriz: {np.max(matriz)}")
print(f"Valor máximo de la matriz: {np.min(matriz)}\n")

print("0: obtener ángulos formados entre dos filas || 1: obtener ángulos formados entre dos columnas")
opcion = int(input())

# Filas
if opcion == 0:
    indice1 = int(input("Fila 1: "))
    indice2 = int(input("Fila 2: "))

    if indice1 not in range(0, filas) or indice2 not in range(0, filas):
        print("Fila incorrecta")
        sys.exit(-1)

    fila1 = matriz[indice1, :]
    fila2 = matriz[indice2, :]

    producto = np.dot(fila1, fila2)
    pvect1 = np.sqrt(np.dot(fila1, fila1))
    pvect2 = np.sqrt(np.dot(fila2, fila2))

# Columnas
if opcion == 1:
    indice1 = int(input("Columna 1: "))
    indice2 = int(input("Columna 2: "))

    if indice1 not in range(0, columnas) or indice2 not in range(0, columnas):
        print("Columna incorrecta")
        sys.exit(-1)

    columna1 = matriz[:, indice1]
    columna2 = matriz[:, indice2]

    producto = np.dot(columna1, columna2)
    pvect1 = np.sqrt(np.dot(columna1, columna2))
    pvect2 = np.sqrt(np.dot(columna1, columna2))

# Obtener ángulo
angulo = producto / (pvect1 * pvect2)
print(f"Ángulo obtenido: {np.degrees(angulo)}")