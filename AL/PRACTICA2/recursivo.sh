#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "recursivo.eps"
set key right bottom
set xlabel "N"
set ylabel "T"
plot 'recursivo.txt' using 1:2 t "Tiempo real" w l, 'recursivo.txt' using 1:3 t "Tiempo estimado" w l
_end_
