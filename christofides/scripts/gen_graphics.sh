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

#plot "file" using 1:3 notitle with points linestyle 1, \
#     "" using 1:3 notitle smooth csplines with lines linestyle 1, \
#     1 / 0 title "title" with linespoints linestyle 1

#plot    "../data/graphics/gbc.dat" u 3:4 notitle w p linestyle 7 lw 3,\
#        "" using 3:4 notitle smooth sbezier w l linestyle 7,\
#        1 / 0 title "Blossom Complete" w lp linestyle 7
#  
#replot "../data/graphics/gbs.dat" u 3:4 w p pt 7 lw 3 smooth sbezier title "Blossom"
#replot "../data/graphics/ggc.dat" u 3:4 w p pt 7 lw 3 smooth sbezier title "Greedy"
#set output "../data/graphics/gTime.eps"
#replot
#unset output


#times
plot "../data/graphics/gbc.dat" u 3:4 w lp pt 7 lw 3 title "BC"
replot "../data/graphics/gbs.dat" u 3:4 w lp pt 7 lw 3 title "BS"
replot "../data/graphics/ggc.dat" u 3:4 w lp pt 7 lw 3 title "GR"
set output "../data/graphics/gTime.eps"
replot
unset output

#deviation
set ylabel "desvio ((v-b)/b)"
set xrange[20:22000]
plot "../data/graphics/gbc.dat" u 3:7 w lp pt 7 lw 3 title "BC"
replot "../data/graphics/gbs.dat" u 3:7 w lp pt 7 lw 3 title "BS"
replot "../data/graphics/ggc.dat" u 3:7 w lp pt 7 lw 3 title "GR"
replot 0.5 notitle w l lt 0 # limit line
set output "../data/graphics/gDev.eps"
replot
unset output
