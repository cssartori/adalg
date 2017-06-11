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
set xlabel "Num. Vertices (n)"
set ylabel "tempo (s)"

#time p = 1
plot "../data/graphics/gmatp1.dat" u 1:9 w lp pt 7 title "Hopcroft-Karp"
replot "../data/graphics/gflowp1.dat" u 1:9 w lp pt 7 title "Push-Relabel"
set output "../data/graphics/gTimep1.eps"
replot
unset output


#phases/max p = 1
set ylabel "phases/sqrt(n)"
plot "../data/graphics/gmatp1.dat" u 1:10 w lp pt 7 title "Hopcroft-Karp"
set output "../data/graphics/gPhasesp1.eps"
replot
unset output


#dfsi/max p = 1
set ylabel "dfsi/(m+n)"
plot "../data/graphics/gmatp1.dat" u 1:11 w lp pt 7 title "Hopcroft-Karp"
set output "../data/graphics/gDfsip1.eps"
replot
unset output

#pd/comp p = 1
set ylabel "phases*dfsi/sqrt(n)(m+n)"
plot "../data/graphics/gmatp1.dat" u 1:12 w lp pt 7 title "Hopcroft-Karp"
set output "../data/graphics/gPdcompp1.eps"
replot
unset output

#time/comp p = 1
set ylabel "tempo/sqrt(n)(n+m)"
plot "../data/graphics/gmatp1.dat" u 1:13 w lp pt 7 title "Hopcroft-Karp"
set output "../data/graphics/gTcompp1.eps"
replot
unset output

