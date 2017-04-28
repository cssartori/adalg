#!/bin/bash

dirname="inst/hs_k"
mkdir $dirname

for filename in ./inst/k/*.gr
	do
		outf=$(echo $filename| cut -d'/' -f 4)
	   	outf=$(echo $outf| cut -d'.' -f  1)
	   	outf=$dirname"/"$outf".dat"  
		./exp -t s -h k -n 50 < $filename > $outf		
	   	echo "Done with "$filename
		echo "Results in file "$outf
done

