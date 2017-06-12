#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "file.txt"



set term jpeg size 1366,768 background "#eeeeee"
set output "data.jpg"

set grid x,y,z
set xlabel "K"
set ylabel "delta"

#set yrange [1:100]
#set xrange [1:100]

#set title "Vx= 0.5, Vy= 0.25"


plot datafile using 1:2 notitle with lines




EOP
