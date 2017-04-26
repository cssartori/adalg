#!/bin/bash

dirname="hs_n"
mkdir $dirname

for filename in ./inst/*.gr
	do
		outf=$(echo $filename| cut -d'/' -f 3)
	   	outf=$(echo $outf| cut -d'.' -f  1)
	   	outf=$dirname"/"$outf".dat"  
		./exp -t s -h k -n 50 < $filename > $outf		
	   	echo "Done with "$filename
		echo "Results in file "$outf
done

