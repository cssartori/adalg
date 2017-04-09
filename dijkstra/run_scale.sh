#!/bin/bash

for hd in {1..16}
do
	dirname="hd_"$hd
	mkdir $dirname

	for filename in ../../instances/dijkstra/*.gr
	do
		outf=$(echo $filename| cut -d'/' -f 5)
	   	outf=$(echo $outf| cut -d'.' -f  2)
	   	outf=$dirname"/"$outf".dat"  
		./exp -t s -n 50 -h $hd < $filename > $outf		
	   	echo "Done with "$filename
		echo "Results in file "$outf
		
	done
done
