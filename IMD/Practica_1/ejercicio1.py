# Implemente mediante un programa Python la asignación del reparto de escaños de una circunscripción electoral usando la Ley D’Hondt. 
# Los datos se pueden introducir por teclado o leerse desde un fichero

import numpy as np

def leyDHont(partidos, escaños):
    cocientes = np.ones(len(partidos))
    resultados = np.zeros(len(partidos))
    
    # Repartir los escaños. Cuando un partido tiene el número máximo de votos, gana un escaño y su divisor aumenta en 1. 
    # Esto se repite para cada escaño, siendo los cocientes del primer escaño 1.
    while escaños > 0:
        mayor = 0
        i = 0
        for votos in partidos:
            votos = votos / cocientes[i]
            if votos > mayor:
                mayor = votos
                partido = i

            i+=1
        cocientes[partido] += 1
        resultados[partido] += 1
        escaños -= 1

    return resultados

#-----------------------------------------#
#Leer datos (comentar una de las opciones)
partidos = []


#Opción 1: por teclado. Para simplificar la lectura, el número de partidos es constante (5). Por tanto, solo se pedirá el número de votos por orden.
num = 5
i = 1

#Escaños
print("Número de escaños a repartir: ")
escaños = int(input())

#Votos
while num > 0:
    print(f"Número de votos del partido {i}: ")
    partidos.append(int(input()))
    num -= 1
    i += 1

'''
#Opción 2: Leer un fichero de texto. Cada fila corresponde a un partido y su número de votos, exceptuando la primera fila que contiene el número de escaños.
#Escaños
f = open("ejercicio1_1.txt", "r")
escaños = int(f.readline())

#Votos
for line in f:
    partidos.append(int(line))

'''
#----------------------------------------#
#Llamar a la función. Los resultados representan el número de escaños para cada partido en orden.
resultados = leyDHont(partidos, escaños)
print(resultados)