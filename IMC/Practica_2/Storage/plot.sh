#!/bin/bash
FILE1="$1"
OUTPUT="$2"


echo $FILE1

cat << _end_ | gnuplot
set terminal postscript eps color
set output "$OUTPUT"
set key right top
set datafile separator "\t"
set xlabel "Iteration"
set ylabel "CCR value"
plot "$FILE1" using 1:2 t "Train" w l, "$FILE1" using 1:3 t "Test" w l, "$FILE1" using 1:4 t "Validation" w l
_end_
