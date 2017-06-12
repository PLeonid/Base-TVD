#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "file.txt"

set term gif animate optimize delay 0 size 1366,768 background "#eeeeee"
set output "data.gif"
set border 4095 front lt black linewidth 1.000 dashtype solid

set grid x,y,z
set xlabel "X"
set ylabel "Y"
set zlabel "U"

set yrange [1:100]
set xrange [1:100]
set zrange [0:1]

#set title "Vx= 0.5, Vy= 0.25"

set ticslevel 0

set pm3d
set palette rgbformulae 33,13,10
set contour base


set view 65, 15, 1, 1

do for [i=1:500] {
splot datafile index i using 1:2:3 notitle with pm3d
}



EOP
