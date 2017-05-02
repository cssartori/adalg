#!/usr/bin/gnuplot

set terminal postscript eps enhanced color
set format y "%.2e"

#===============================================================================
#===============================================================================
#===============================================================================
#===============================================================================

#Heap graphics
set datafile separator ","
set logscale y
set key top left
set xlabel "n=2^x elementos"
set ylabel "tempo (s)"

# Inserts
plot "../res/heap/insert/tinsk2.dat" u 1:7 w lp lw 3 title "2-heap"
replot "../res/heap/insert/tinsh.dat" u 1:7 w lp lw 3 title "hollow heap"
set output "../res/heap/gins_2.eps"
replot
unset output

# Updates
plot "../res/heap/update/tupdk2.dat" u 1:7 w lp lw 3 title "2-heap"
replot "../res/heap/update/tupdh.dat" u 1:7 w lp lw 3 title "hollow heap"
set output "../res/heap/gupd_2.eps"
replot
unset output

# Deletes
plot "../res/heap/delete/deterministic/tdelDk2.dat" u 1:7 w lp lw 3 title "2-heap"
replot "../res/heap/delete/deterministic/tdelDh.dat" u 1:7 w lp lw 3 title "hollow heap"
set output "../res/heap/gdelD_2.eps"
replot
unset output

plot "../res/heap/delete/random/tdelRk2.dat" u 1:7 w lp lw 3 title "2-heap"
replot "../res/heap/delete/random/tdelRh.dat" u 1:7 w lp lw 3 title "hollow heap"
set output "../res/heap/gdelR_2.eps"
replot
unset output

set ylabel "(tempo / E) (s)"

plot "../res/heap/delete/deterministic/tdelDk2.dat" u 1:9 w lp lw 3 title "2-heap"
replot "../res/heap/delete/deterministic/tdelDh.dat" u 1:9 w lp lw 3 title "hollow heap"
set output "../res/heap/gcdelD_2.eps"
replot
unset output

plot "../res/heap/delete/random/tdelRk2.dat" u 1:9 w lp lw 3 title "2-heap"
replot "../res/heap/delete/random/tdelRh.dat" u 1:9 w lp lw 3 title "hollow heap"
set output "../res/heap/gcdelR_2.eps"
replot
unset output

#===============================================================================
#===============================================================================
#===============================================================================
#===============================================================================

# Complexity graphics 

unset datafile separator
set logscale y
set logscale x
set key top left

# Varying M
set xlabel "Numero de arestas m"
set ylabel "(tempo / (n+m)log n)"
plot "../res/comp/RM/Grmk.dat" u 5:14 w lp lw 3 title "2-heap"
replot "../res/comp/RM/Grmh.dat" u 5:14 w lp lw 3 title "hollow heap"
set output "../res/comp/gclm.eps"
replot
unset output

unset logscale y
unset logscale x
plot "../res/comp/RM/Grmk.dat" u 5:14 w lp lw 3 title "2-heap"
replot "../res/comp/RM/Grmh.dat" u 5:14 w lp lw 3 title "hollow heap"
set output "../res/comp/gcm.eps"
replot
unset output

# Varying N
set logscale y
set logscale x
set xlabel "Numero de vertices n"
set ylabel "(tempo / (n+m)log n)"
plot "../res/comp/RN/Grnk.dat" u 4:14 w lp lw 3 title "2-heap"
replot "../res/comp/RN/Grnh.dat" u 4:14 w lp lw 3 title "hollow heap"
set output "../res/comp/gcln.eps"
replot
unset output

unset logscale y
unset logscale x
set xlabel "Numero de vertices n"
set ylabel "(tempo / (n+m)log n)"
plot "../res/comp/RN/Grnk.dat" u 4:14 w lp lw 3 title "2-heap"
replot "../res/comp/RN/Grnh.dat" u 4:14 w lp lw 3 title "hollow heap"
set output "../res/comp/gcn.eps"
replot
unset output

#===============================================================================
#===============================================================================
#===============================================================================
#===============================================================================

# Scale graphics 

set logscale y
set logscale x
set key top left

set xlabel "Numero de vertices n"
set ylabel "tempo (s)"
plot "../res/scale/GK.dat" u 4:13 w lp lw 3 title "2-heap"
replot "../res/scale/GH.dat" u 4:13 w lp lw 3 title "hollow heap"
set output "../res/scale/gBIGt.eps"
replot
unset output


set xlabel "Numero de vertices n"
set ylabel "Memoria (MB)"
plot "../res/scale/GK.dat" u 4:12 w lp lw 3 title "2-heap"
replot "../res/scale/memh/GH.dat" u 4:12 w lp lw 3 title "hollow heap"
set output "../res/scale/gBIGm.eps"
replot
unset output


