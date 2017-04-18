#!/bin/bash

for hd in {10,16}
do
	dirname="chd_"$hd
	mkdir $dirname

	for filename in ./ci/t/*.gr
	do
		outf=$(echo $filename| cut -d'/' -f 4)
	   	outf=$(echo $outf| cut -d'.' -f  1)
	   	outf=$dirname"/"$outf".dat"  
		./exp -t s -n 50 -h $hd < $filename > $outf		
	   	echo "Done with "$filename
		echo "Results in file "$outf
		
	done
done
