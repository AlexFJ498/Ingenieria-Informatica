# Implemente un programa Python que lea una matriz de número reales desde un fichero texto con formato libre. 
# Una vez leído el programa debe obtener la inversa de la matriz y realizar un producto matricial para comprobar que el cálculo de la inversa es correcto.

import numpy as np

# Leer matriz
matriz = np.loadtxt("ejercicio5.txt")
print(matriz)

# Obtener inversa
inversa = np.linalg.inv(matriz)
print(inversa)

# Realizar producto. El resultado debe ser la matriz identidad
producto = np.matmul(matriz, inversa).round(0)
print(producto)