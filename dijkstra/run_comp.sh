#!/bin/bash

N=(2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576)
M=(256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576)

n=1048576
m=20971521

# 1048576 2097152 4194304 8388608 16777216 33554432 67108864

mkdir "rcomp"

for m in ${M[*]}
do
	
	./gen -n $n -m $m > "rcomp/temp"$n"-"$m".gr"
	echo "Created graph with "$n" nodes and "$m" edges"
	outf="./rcomp/RC-"$n"."$m".dat"
	./exp -t s -n 50 -h 2 < "rcomp/temp"$n"-"$m".gr" > $outf 	
	
	echo "Done with "$m
	echo "Results in file "$outf
		
done

rm "temp.gr"
