#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "file.txt"

set term jpeg size 1366,768 background "#eeeeee"
set output "data.jpg"

set grid x,y,mxtics,mytics

set mxtic 2
set mytic 2

set xlabel "Число Куранта 1"
set ylabel "Число Куранта 2"

#set yrange [0:2]
#set xrange [0:5.5]


plot datafile using 1:2 notitle with points pt 1 ps 2


EOP
