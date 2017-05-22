#!/usr/bin/gnuplot

#set terminal postscript eps enhanced color
set format y "%.2e"
set term x11 persist
#===============================================================================
#===============================================================================
#===============================================================================
#===============================================================================

#Big time graphic
set datafile separator ","
set logscale y
set logscale x
set key top left
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"

#plot "<cat ../data/dt1_k100.dat ../data/dt1_k10000.dat | sort -n" u 2:13 w p pt 7 title "Type 1"
#replot "<cat ../data/dt2_k100.dat ../data/dt2_k10000.dat | sort -n" u 2:13 w p pt 7 title "Type 2"
#replot "<cat ../data/dt3_k100.dat ../data/dt3_k10000.dat | sort -n" u 2:13 w p pt 7 title "Type 3"
#replot "<cat ../data/dt4_k100.dat ../data/dt4_k10000.dat | sort -n" u 2:13 w p pt 7 title "Type 4"
#replot "<cat ../data/dt5_d8_k100.dat ../data/dt5_d8_k10000.dat ../data/dt5_d16_k10000.dat ../data/dt5_d16_k100.dat | sort -n" u 2:13 w p pt 7 title "Type 5"
#replot "<cat ../data/dt6_d8_k100.dat ../data/dt6_d8_k10000.dat ../data/dt6_d16_k10000.dat ../data/dt6_d16_k100.dat | sort -n" u 2:13 w p pt 7 title "Type 6"
#replot "<cat ../data/dt7_d8_k100.dat ../data/dt7_d8_k10000.dat ../data/dt7_d16_k10000.dat ../data/dt7_d16_k100.dat | sort -n" u 2:13 w p pt 7 title "Type 7"
#replot "<cat ../data/dt8_d8_k100.dat ../data/dt8_d8_k10000.dat ../data/dt8_d16_k10000.dat ../data/dt8_d16_k100.dat | sort -n" u 2:13 w p pt 7 title "Type 8"
#replot "../data/dt9.dat" u 2:13 w p pt 7 title "Type 9"
#replot "../data/dt10.dat" u 2:13 w p pt 7 title "Type 10"


plot "<cat ../data/dt1_k100.dat ../data/dt1_k10000.dat | sort -n" u 2:14 w p pt 7 title "Type 1"
replot "<cat ../data/dt2_k100.dat ../data/dt2_k10000.dat | sort -n" u 2:14 w p pt 7 title "Type 2"
replot "<cat ../data/dt3_k100.dat ../data/dt3_k10000.dat | sort -n" u 2:14 w p pt 7 title "Type 3"
replot "<cat ../data/dt4_k100.dat ../data/dt4_k10000.dat | sort -n" u 2:14 w p pt 7 title "Type 4"
replot "<cat ../data/dt5_d8_k100.dat ../data/dt5_d8_k10000.dat ../data/dt5_d16_k10000.dat ../data/dt5_d16_k100.dat | sort -n" u 2:14 w p pt 7 title "Type 5"
replot "<cat ../data/dt6_d8_k100.dat ../data/dt6_d8_k10000.dat ../data/dt6_d16_k10000.dat ../data/dt6_d16_k100.dat | sort -n" u 2:14 w p pt 7 title "Type 6"
replot "<cat ../data/dt7_d8_k100.dat ../data/dt7_d8_k10000.dat ../data/dt7_d16_k10000.dat ../data/dt7_d16_k100.dat | sort -n" u 2:14 w p pt 7 title "Type 7"
replot "<cat ../data/dt8_d8_k100.dat ../data/dt8_d8_k10000.dat ../data/dt8_d16_k10000.dat ../data/dt8_d16_k100.dat | sort -n" u 2:14 w p pt 7 title "Type 8"
replot "../data/dt9.dat" u 2:14 w p pt 7 title "Type 9"
replot "../data/dt10.dat" u 2:14 w p pt 7 title "Type 10"






# Inserts
#plot "../res/heap/insert/tinsk2.dat" u 1:7 w lp lw 3 title "2-heap"
#replot "../res/heap/insert/tinsh.dat" u 1:7 w lp lw 3 title "hollow heap"
#set output "../res/heap/gins_2.eps"
#replot
#unset output

## Updates
#plot "../res/heap/update/tupdk2.dat" u 1:7 w lp lw 3 title "2-heap"
#replot "../res/heap/update/tupdh.dat" u 1:7 w lp lw 3 title "hollow heap"
#set output "../res/heap/gupd_2.eps"
#replot
#unset output

## Deletes
#plot "../res/heap/delete/deterministic/tdelDk2.dat" u 1:7 w lp lw 3 title "2-heap"
#replot "../res/heap/delete/deterministic/tdelDh.dat" u 1:7 w lp lw 3 title "hollow heap"
#set output "../res/heap/gdelD_2.eps"
#replot
#unset output

#plot "../res/heap/delete/random/tdelRk2.dat" u 1:7 w lp lw 3 title "2-heap"
#replot "../res/heap/delete/random/tdelRh.dat" u 1:7 w lp lw 3 title "hollow heap"
#set output "../res/heap/gdelR_2.eps"
#replot
#unset output

#set ylabel "(tempo / E) (s)"

#plot "../res/heap/delete/deterministic/tdelDk2.dat" u 1:9 w lp lw 3 title "2-heap"
#replot "../res/heap/delete/deterministic/tdelDh.dat" u 1:9 w lp lw 3 title "hollow heap"
#set output "../res/heap/gcdelD_2.eps"
#replot
#unset output

#plot "../res/heap/delete/random/tdelRk2.dat" u 1:9 w lp lw 3 title "2-heap"
#replot "../res/heap/delete/random/tdelRh.dat" u 1:9 w lp lw 3 title "hollow heap"
#set output "../res/heap/gcdelR_2.eps"
#replot
#unset output

##===============================================================================
##===============================================================================
##===============================================================================
##===============================================================================

## Complexity graphics 

#unset datafile separator
#set logscale y
#set logscale x
#set key top left

## Varying M
#set xlabel "Numero de arestas m"
#set ylabel "(tempo / (n+m)log n)"
#plot "../res/comp/RM/Grmk.dat" u 5:14 w lp lw 3 title "2-heap"
#replot "../res/comp/RM/Grmh.dat" u 5:14 w lp lw 3 title "hollow heap"
#set output "../res/comp/gclm.eps"
#replot
#unset output

#unset logscale y
#unset logscale x
#set key top right
#plot "../res/comp/RM/Grmk.dat" u 5:14 w lp lw 3 title "2-heap"
#replot "../res/comp/RM/Grmh.dat" u 5:14 w lp lw 3 title "hollow heap"
#set output "../res/comp/gcm.eps"
#replot
#unset output

## Varying N
#set logscale y
#set logscale x
#set xlabel "Numero de vertices n"
#set ylabel "(tempo / (n+m)log n)"
#plot "../res/comp/RN/Grnk.dat" u 4:14 w lp lw 3 title "2-heap"
#replot "../res/comp/RN/Grnh.dat" u 4:14 w lp lw 3 title "hollow heap"
#set output "../res/comp/gcln.eps"
#replot
#unset output

#unset logscale y
#unset logscale x
#set key top right
#set xlabel "Numero de vertices n"
#set ylabel "(tempo / (n+m)log n)"
#plot "../res/comp/RN/Grnk.dat" u 4:14 w lp lw 3 title "2-heap"
#replot "../res/comp/RN/Grnh.dat" u 4:14 w lp lw 3 title "hollow heap"
#set output "../res/comp/gcn.eps"
#replot
#unset output

##===============================================================================
##===============================================================================
##===============================================================================
##===============================================================================

## Scale graphics 

#set logscale y
#set logscale x
#set key top left

#set xlabel "Numero de vertices n"
#set ylabel "tempo (s)"
#plot "../res/scale/GK.dat" u 4:13 w lp lw 3 title "2-heap"
#replot "../res/scale/GH.dat" u 4:13 w lp lw 3 title "hollow heap"
#set output "../res/scale/gBIGt.eps"
#replot
#unset output


#set xlabel "Numero de vertices n"
#set ylabel "Memoria (MB)"
#plot "../res/scale/GK.dat" u 4:12 w lp lw 3 title "2-heap"
#replot "../res/scale/memh/GH.dat" u 4:12 w lp lw 3 title "hollow heap"
#set output "../res/scale/gBIGm.eps"
#replot
#unset output

##===============================================================================
##===============================================================================
##===============================================================================
##===============================================================================

## Linear Regression graphics

#unset logscale y
#unset logscale x
#set key top right

#set xlabel "Numero de vertices n"
#set ylabel "Numero de arestas m"
#set zlabel "Tempo (s)"

#f(x,y) = 10**(-12.159)*x**(0.845)*y**(1.057)
#splot f(x,y) lw 3 title "T(n,m)"
#replot "../res/comp/linreg/lrh.dat" u 4:5:13 w lp lw 3 title "hollow heap"
#set output "../res/comp/linreg/gLRh.eps"
#replot
#unset output

#f(x,y) = 10**(-12.912)*x**(0.824)*y**(1.127)
#splot f(x,y) lw 3 title "T(n,m)"
#replot "../res/comp/linreg/lrk.dat" u 4:5:13 w lp lw 3 title "2-heap"
#set output "../res/comp/linreg/gLRk.eps"
#replot
#unset output

