#!/usr/bin/gnuplot

set terminal postscript eps enhanced color
#set term x11 persist
set format y "%.2e"
set datafile separator ","

#===============================================================================
#===============================================================================
#===============================================================================
#===============================================================================

#Big time graphic
set logscale y
set logscale x
set key top left
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"

# Strict times
plot "<cat ../data/dt1_k100.dat ../data/dt1_k10000.dat | sort -n -t \",\" -k 2,2" u 2:13 w p pt 7 title "Type 1"
replot "<cat ../data/dt2_k100.dat ../data/dt2_k10000.dat | sort -n -t \",\" -k 2,2" u 2:13 w p pt 7 title "Type 2"
replot "<cat ../data/dt3_k100.dat ../data/dt3_k10000.dat | sort -n -t \",\" -k 2,2" u 2:13 w p pt 7 title "Type 3"
replot "<cat ../data/dt4_k100.dat ../data/dt4_k10000.dat | sort -n -t \",\" -k 2,2" u 2:13 w p pt 7 title "Type 4"
replot "<cat ../data/dt5_d8_k100.dat ../data/dt5_d8_k10000.dat ../data/dt5_d16_k10000.dat ../data/dt5_d16_k100.dat | sort -n -t \",\" -k 2,2" u 2:13 w p pt 7 title "Type 5"
replot "<cat ../data/dt6_d8_k100.dat ../data/dt6_d8_k10000.dat ../data/dt6_d16_k10000.dat ../data/dt6_d16_k100.dat | sort -n -t \",\" -k 2,2" u 2:13 w p pt 7 title "Type 6"
replot "<cat ../data/dt7_d8_k100.dat ../data/dt7_d8_k10000.dat ../data/dt7_d16_k10000.dat ../data/dt7_d16_k100.dat | sort -n -t \",\" -k 2,2" u 2:13 w p pt 7 title "Type 7"
replot "<cat ../data/dt8_d8_k100.dat ../data/dt8_d8_k10000.dat ../data/dt8_d16_k10000.dat ../data/dt8_d16_k100.dat | sort -n -t \",\" -k 2,2" u 2:13 w p pt 7 title "Type 8"
replot "../data/dt9.dat" u 2:13 w p pt 13 title "Type 9"
replot "../data/dt10.dat" u 2:13 w p pt 13 title "Type 10"
set output "../data/graphs/gBTime.eps"
replot
unset output

# time-complexity ratio
set key bottom left
plot "<cat ../data/dt1_k100.dat ../data/dt1_k10000.dat | sort -n -t \",\" -k 2,2" u 2:14 w p pt 7 title "Type 1"
replot "<cat ../data/dt2_k100.dat ../data/dt2_k10000.dat | sort -n -t \",\" -k 2,2" u 2:14 w p pt 7 title "Type 2"
replot "<cat ../data/dt3_k100.dat ../data/dt3_k10000.dat | sort -n -t \",\" -k 2,2" u 2:14 w p pt 7 title "Type 3"
replot "<cat ../data/dt4_k100.dat ../data/dt4_k10000.dat | sort -n -t \",\" -k 2,2" u 2:14 w p pt 7 title "Type 4"
replot "<cat ../data/dt5_d8_k100.dat ../data/dt5_d8_k10000.dat ../data/dt5_d16_k10000.dat ../data/dt5_d16_k100.dat | sort -n -t \",\" -k 2,2" u 2:14 w p pt 7 title "Type 5"
replot "<cat ../data/dt6_d8_k100.dat ../data/dt6_d8_k10000.dat ../data/dt6_d16_k10000.dat ../data/dt6_d16_k100.dat | sort -n -t \",\" -k 2,2" u 2:14 w p pt 7 title "Type 6"
replot "<cat ../data/dt7_d8_k100.dat ../data/dt7_d8_k10000.dat ../data/dt7_d16_k10000.dat ../data/dt7_d16_k100.dat | sort -n -t \",\" -k 2,2" u 2:14 w p pt 7 title "Type 7"
replot "<cat ../data/dt8_d8_k100.dat ../data/dt8_d8_k10000.dat ../data/dt8_d16_k10000.dat ../data/dt8_d16_k100.dat | sort -n -t \",\" -k 2,2" u 2:14 w p pt 7 title "Type 8"
replot "../data/dt9.dat" u 2:14 w p pt 13 title "Type 9"
replot "../data/dt10.dat" u 2:14 w p pt 13 title "Type 10"
set output "../data/graphs/gBTimeComp.eps"
replot
unset output

#===============================================================================
#===============================================================================
#===============================================================================
#===============================================================================

# Separated graphs
set key top left

# Type 1
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"
set samples 10000
plot "../data/dt1_k100.dat" u 2:13 w lp pt 7 title "Type 1: C = 100    "
replot "../data/dt1_k100.dat" u 2:13 w p pt 7 title "Type 1: C = 100    "
#plot "../data/dt1_k100.dat" u 2:13 w lp pt 7 title "Type 1: C = 100    "
#replot "../data/dt1_k10000.dat" u 2:13 w lp pt 7 title "Type 1: C = 10000"
set output "../data/graphs/gt1Time.eps"
replot
unset output

set xlabel "Num. Arestas (m)"
set ylabel "tempo/Comp."
plot "../data/dt1_k100.dat" u 2:14 w lp pt 7 title "Type 1: C = 100    "
replot "../data/dt1_k10000.dat" u 2:14 w lp pt 7 title "Type 1: C = 10000"
set output "../data/graphs/gt1TimeComp.eps"
replot
unset output


# Type 2
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"
plot "../data/dt2_k100.dat" u 2:13 w lp pt 7 title "Type 2: C = 100    "
replot "../data/dt2_k10000.dat" u 2:13 w lp pt 7 title "Type 2: C = 10000"
set output "../data/graphs/gt2Time.eps"
replot
unset output

set xlabel "Num. Arestas (m)"
set ylabel "tempo/Comp."
plot "../data/dt2_k100.dat" u 2:14 w lp pt 7 title "Type 2: C = 100    "
replot "../data/dt2_k10000.dat" u 2:14 w lp pt 7 title "Type 2: C = 10000"
set output "../data/graphs/gt2TimeComp.eps"
replot
unset output


# Type 3
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"
plot "../data/dt3_k100.dat" u 2:13 w lp pt 7 title "Type 3: C = 100    "
replot "../data/dt3_k10000.dat" u 2:13 w lp pt 7 title "Type 3: C = 10000"
set output "../data/graphs/gt3Time.eps"
replot
unset output

set xlabel "Num. Arestas (m)"
set ylabel "tempo/Comp."
plot "../data/dt3_k100.dat" u 2:14 w lp pt 7 title "Type 3: C = 100    "
replot "../data/dt3_k10000.dat" u 2:14 w lp pt 7 title "Type 3: C = 10000"
set output "../data/graphs/gt3TimeComp.eps"
replot
unset output


# Type 4
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"
plot "../data/dt4_k100.dat" u 2:13 w lp pt 7 title "Type 4: C = 100    "
replot "../data/dt4_k10000.dat" u 2:13 w lp pt 7 title "Type 4: C = 10000"
set output "../data/graphs/gt4Time.eps"
replot
unset output

set xlabel "Num. Arestas (m)"
set ylabel "tempo/Comp."
plot "../data/dt4_k100.dat" u 2:14 w lp pt 7 title "Type 4: C = 100    "
replot "../data/dt4_k10000.dat" u 2:14 w lp pt 7 title "Type 4: C = 10000"
set output "../data/graphs/gt4TimeComp.eps"
replot
unset output


# Type 5
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"
plot "../data/dt5_d8_k100.dat" u 2:13 w lp pt 7 title "Type 5: D=8, C=100      "
replot "../data/dt5_d8_k10000.dat" u 2:13 w lp pt 7 title "Type 5: D=8, C=10000  "
replot "../data/dt5_d16_k100.dat" u 2:13 w lp pt 7 title "Type 5: D=16, C=100    "
replot "../data/dt5_d16_k10000.dat" u 2:13 w lp pt 7 title "Type 5: D=16, C=10000"
set output "../data/graphs/gt5Time.eps"
replot
unset output

set key bottom left
set xlabel "Num. Arestas (m)"
set ylabel "tempo/Comp."
plot "../data/dt5_d8_k100.dat" u 2:14 w lp pt 7 title "Type 5: D=8, C=100      "
replot "../data/dt5_d8_k10000.dat" u 2:14 w lp pt 7 title "Type 5: D=8, C=10000  "
replot "../data/dt5_d16_k100.dat" u 2:14 w lp pt 7 title "Type 5: D=16, C=100    "
replot "../data/dt5_d16_k10000.dat" u 2:14 w lp pt 7 title "Type 5: D=16, C=10000"
set output "../data/graphs/gt5TimeComp.eps"
replot
unset output


# Type 6
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"
plot "../data/dt6_d8_k100.dat" u 2:13 w lp pt 7 title "Type 6: D=8, C=100      "
replot "../data/dt6_d8_k10000.dat" u 2:13 w lp pt 7 title "Type 6: D=8, C=10000  "
replot "../data/dt6_d16_k100.dat" u 2:13 w lp pt 7 title "Type 6: D=16, C=100    "
replot "../data/dt6_d16_k10000.dat" u 2:13 w lp pt 7 title "Type 6: D=16, C=10000"
set output "../data/graphs/gt6Time.eps"
replot
unset output

set key bottom left
set xlabel "Num. Arestas (m)"
set ylabel "tempo/Comp."
plot "../data/dt6_d8_k100.dat" u 2:14 w lp pt 7 title "Type 6: D=8, C=100      "
replot "../data/dt6_d8_k10000.dat" u 2:14 w lp pt 7 title "Type 6: D=8, C=10000  "
replot "../data/dt6_d16_k100.dat" u 2:14 w lp pt 7 title "Type 6: D=16, C=100    "
replot "../data/dt6_d16_k10000.dat" u 2:14 w lp pt 7 title "Type 6: D=16, C=10000"
set output "../data/graphs/gt6TimeComp.eps"
replot
unset output


# Type 7
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"
plot "../data/dt7_d8_k100.dat" u 2:13 w lp pt 7 title "Type 7: D=8, C=100      "
replot "../data/dt7_d8_k10000.dat" u 2:13 w lp pt 7 title "Type 7: D=8, C=10000  "
replot "../data/dt7_d16_k100.dat" u 2:13 w lp pt 7 title "Type 7: D=16, C=100    "
replot "../data/dt7_d16_k10000.dat" u 2:13 w lp pt 7 title "Type 7: D=16, C=10000"
set output "../data/graphs/gt7Time.eps"
replot
unset output

set key bottom left
set xlabel "Num. Arestas (m)"
set ylabel "tempo/Comp."
plot "../data/dt7_d8_k100.dat" u 2:14 w lp pt 7 title "Type 7: D=8, C=100      "
replot "../data/dt7_d8_k10000.dat" u 2:14 w lp pt 7 title "Type 7: D=8, C=10000  "
replot "../data/dt7_d16_k100.dat" u 2:14 w lp pt 7 title "Type 7: D=16, C=100    "
replot "../data/dt7_d16_k10000.dat" u 2:14 w lp pt 7 title "Type 7: D=16, C=10000"
set output "../data/graphs/gt7TimeComp.eps"
replot
unset output


# Type 8
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"
plot "../data/dt8_d8_k100.dat" u 2:13 w lp pt 7 title "Type 8: D=8, C=100      "
replot "../data/dt8_d8_k10000.dat" u 2:13 w lp pt 7 title "Type 8: D=8, C=10000  "
replot "../data/dt8_d16_k100.dat" u 2:13 w lp pt 7 title "Type 8: D=16, C=100    "
replot "../data/dt8_d16_k10000.dat" u 2:13 w lp pt 7 title "Type 8: D=16, C=10000"
set output "../data/graphs/gt8Time.eps"
replot
unset output

set key bottom left
set xlabel "Num. Arestas (m)"
set ylabel "tempo/Comp."
plot "../data/dt8_d8_k100.dat" u 2:14 w lp pt 7 title "Type 8: D=8, C=100      "
replot "../data/dt8_d8_k10000.dat" u 2:14 w lp pt 7 title "Type 8: D=8, C=10000  "
replot "../data/dt8_d16_k100.dat" u 2:14 w lp pt 7 title "Type 8: D=16, C=100    "
replot "../data/dt8_d16_k10000.dat" u 2:14 w lp pt 7 title "Type 8: D=16, C=10000"
set output "../data/graphs/gt8TimeComp.eps"
replot
unset output


# Type 9
set xlabel "Num. Arestas (m)"
set ylabel "tempo (s)"
plot "../data/dt9.dat" u 2:13 w lp pt 7 title "Type 9  "
replot "../data/dt10.dat" u 2:13 w lp pt 7 title "Type 10"
set output "../data/graphs/gt9-10Time.eps"
replot
unset output

set key bottom left
set xlabel "Num. Arestas (m)"
set ylabel "tempo/Comp."
plot "../data/dt9.dat" u 2:14 w lp pt 7 title "Type 9  "
replot "../data/dt10.dat" u 2:14 w lp pt 7 title "Type 10"
set output "../data/graphs/gt9-10TimeComp.eps"
replot
unset output

