#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "file.txt"



set terminal jpeg size 640,480
set output "data.jpg"

#set border 4095 front lt black linewidth 1.000 dashtype solid
set style line 100  linecolor rgb "#f0e442"  linewidth 0.500 dashtype solid pointtype 5 pointsize default pointinterval 0
unset surface 
set pm3d implicit at s
set samples 20, 20
set isosamples 20, 20


set grid x,y,z
set xlabel "X"
set ylabel "Y"
set zlabel "U"
set yrange [1:99]
set xrange [1:99]

set view 65, 15, 1, 1


splot datafile using 1:2:3 notitle with lines 
#splot x+y notitle with lines


EOP
