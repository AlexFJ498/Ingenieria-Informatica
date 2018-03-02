#!/bin/bash
if [ $# != 1 ]
then
	echo "Error, debes incluir un directorio como primer argumento"
	exit
else
	cd $1
	a=""
	if [ $2 -eq $a ]
	then
		let nBytes=0
	else
		let nBytes=$2
	fi
	for fich in *
	do
		let b=$(wc -c < $fich)
		if [ $b -gt $nBytes ]
		then
			if [ -e $fich ]
			then
				x=1
			else
				x=0
			fi
			echo "Nombre,LongitudUsuario,FechaModificacion,FechaAcceso,Tamano,Bloques,Permisos,Ejecutable"
			echo "$(basename $fich);$(stat -c%U $fich);$(date -r $fich);$(stat -c%X $fich);$(stat -c%s $fich);$(stat -c%b $fich);$(stat -c%A $fich);$x"
		fi | sort -t ";" -k 4
	done
fi
