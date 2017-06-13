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
plot "../data/graphics/p1/gmatp1.dat" u 1:9 w lp pt 7 title "Hopcroft-Karp"
replot "../data/graphics/p1/gflowp1.dat" u 1:9 w lp pt 7 title "Push-Relabel"
replot "../data/graphics/p1/gfatp1.dat" u 1:9 w lp pt 7 title "Fattest Path"
set output "../data/graphics/gTimep1.eps"
replot
unset output
#time p = 0.5
plot "../data/graphics/p0/gmatp0.dat" u 1:9 w lp pt 7 title "Hopcroft-Karp"
replot "../data/graphics/p0/gflowp0.dat" u 1:9 w lp pt 7 title "Push-Relabel"
replot "../data/graphics/p0/gfatp0.dat" u 1:9 w lp pt 7 title "Fattest Path"
set output "../data/graphics/gTimep0.eps"
replot
unset output
#time p = 2
plot "../data/graphics/p2/gmatp2.dat" u 1:9 w lp pt 7 title "Hopcroft-Karp"
replot "../data/graphics/p2/gflowp2.dat" u 1:9 w lp pt 7 title "Push-Relabel"
replot "../data/graphics/p2/gfatp2.dat" u 1:9 w lp pt 7 title "Fattest Path"
set output "../data/graphics/gTimep2.eps"
replot
unset output


#phases/max
set ylabel "phases/sqrt(n)"
plot "../data/graphics/p1/gmatp1.dat" u 1:10 w lp pt 7 title "HK p=1.0"
replot "../data/graphics/p0/gmatp0.dat" u 1:10 w lp pt 7 title "HK p=0.5"
replot "../data/graphics/p2/gmatp2.dat" u 1:10 w lp pt 7 title "HK p=2.0"
set output "../data/graphics/gPhases.eps"
replot
unset output


#dfsi/max p = 1
set ylabel "dfsi/(m+n)"
plot "../data/graphics/p1/gmatp1.dat" u 1:11 w lp pt 7 title "HK p=1.0"
replot "../data/graphics/p0/gmatp0.dat" u 1:11 w lp pt 7 title "HK p=0.5"
replot "../data/graphics/p2/gmatp2.dat" u 1:11 w lp pt 7 title "HK p=2.0"
set output "../data/graphics/gDfsi.eps"
replot
unset output


#pd/comp p = 1
set ylabel "phases*dfsi/sqrt(n)(m+n)"
plot "../data/graphics/p1/gmatp1.dat" u 1:12 w lp pt 7 title "HK p=1.0"
replot "../data/graphics/p0/gmatp0.dat" u 1:12 w lp pt 7 title "HK p=0.5"
replot "../data/graphics/p2/gmatp2.dat" u 1:12 w lp pt 7 title "HK p=2.0"
set output "../data/graphics/gPdcomp.eps"
replot
unset output


#time/comp p = 1
set ylabel "tempo/sqrt(n)(n+m)"
plot "../data/graphics/p1/gmatp1.dat" u 1:13 w lp pt 7 title "HK p=1.0"
replot "../data/graphics/p0/gmatp0.dat" u 1:13 w lp pt 7 title "HK p=0.5"
replot "../data/graphics/p2/gmatp2.dat" u 1:13 w lp pt 7 title "HK p=2.0"
set output "../data/graphics/gTcomp.eps"
replot
unset output

