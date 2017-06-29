#!/usr/bin/gnuplot

set terminal postscript eps enhanced color
#set term x11 persist
set format y "%.2e"
set datafile separator ","

#===============================================================================
#===============================================================================
#===============================================================================
#===============================================================================

set logscale y
set logscale x
set key top left
set xlabel "vertices (n)"
set ylabel "tempo (s)"

#times
plot "../data/graphics/blossom.dat" u 3:4 w lp pt 7 lw 3 title "CBlossom"
replot "../data/graphics/greedy.dat" u 3:4 w lp pt 7 lw 3 title "CGreedy"
set output "../data/graphics/gTime.eps"
replot
unset output


#deviation
plot "../data/graphics/blossom.dat" u 3:7 w lp pt 7 lw 3 title "CBlossom"
replot "../data/graphics/greedy.dat" u 3:7 w lp pt 7 lw 3 title "CGreedy"
replot 0.5 w l lt 5 # limit line
set output "../data/graphics/gDev.eps"
replot
unset output
