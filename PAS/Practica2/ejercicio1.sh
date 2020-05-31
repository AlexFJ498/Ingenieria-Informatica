#!/bin/bash
if [ $# != 1 ] #comprobar argumento
then
	echo "Error, debes incluir el fichero de texto como parametro"
	exit
elif [ $1 != "peliculas.txt" ] #comprobar que el fichero es el correcto
then
	echo "Error: fichero incorrecto (peliculas.txt)"
	exit
fi

#1
echo "1) Lineas con la duracion de las peliculas:"
cat $1 |  grep -E -e '^.* .*min$'
echo "*******"
#2
echo "2) Lineas con el pais de las peliculas:"
cat $1 | grep -E -e '^.* -.*-$'
echo "*******"
#3
echo "3) Solo el pais de las peliculas:"
cat $1 | grep -E -e '^.* -.*-$' | grep -E -o ' -.*-$'
echo "*******"
#4
cont16=$(cat $1 | grep -E -e '^.*.*.2016. -.*-$' | wc -l) #contar 2016
cont17=$(cat $1 | grep -E -e '^.*.*.2017. -.*-$' | wc -l) #contar 2017
echo "4) Hay $cont16 peliculas del 2016 y $cont17 peliculas del 2017"
echo "*******"
#5
echo "5) Eliminar lineas vacias:"
cat $1 | grep -E -v -e '^$'
echo "*******"
#6
echo "6) Lineas que empiezan por la letra E (con o sin espacios antes):"
cat $1 | grep -E -e '^ *E'
echo "*******"
#7
echo "7) Lineas que contienen d, l o t, una vocal y la misma letra:"
cat $1 | grep -E -e '([dlt])[aeiou]\1'
echo "*******"
#8
