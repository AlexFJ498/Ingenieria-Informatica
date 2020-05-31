#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "recursivoTablas.eps"
set key right bottom
set xlabel "N"
set ylabel "T"
plot 'recursivoTablas.txt' using 1:2 t "Tiempo real" w l, 'recursivoTablas.txt' using 1:3 t "Tiempo estimado" w l
_end_
