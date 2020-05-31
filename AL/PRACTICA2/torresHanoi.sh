#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "torresHanoi.eps"
set key right bottom
set xlabel "N"
set ylabel "T"
plot 'torresHanoi.txt' using 1:2 t "Tiempo real" w l, 'torresHanoi.txt' using 1:3 t "Tiempo estimado" w l
_end_
