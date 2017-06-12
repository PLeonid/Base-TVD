#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "file.txt"



set terminal jpeg size 640,480
set output "data.jpg"

set border 4095 front lt black linewidth 1.000 dashtype solid

set pm3d

set grid x,y,z
set xlabel "X"
set ylabel "Y"
set zlabel "U"
set yrange [1:99]
set xrange [1:99]

set view 65, 15, 1, 1


splot datafile using 1:2:3 notitle with pm3d
#splot x+y notitle with lines


EOP
