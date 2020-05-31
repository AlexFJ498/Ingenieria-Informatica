#!/bin/bash
if [ $# != 1 ]
then
	echo "Error, debes incluir un directorio como parametro"
	exit
else
	cd $1
	echo "Tenemos $(find -name "*.c" | wc -l) ficheros con extension .c y $(find -name "*.h" | wc -l) ficheros con extension .h"
	for dir in $(find -name "*.c" -o -name "*.h")
	do
		lin=$(wc -l < $dir)
		car=$(wc -m < $dir)
		echo "El fichero $dir tiene $lin lineas y $car caracteres"
	done | sort -nr -k 8
fi


