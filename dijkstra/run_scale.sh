#!/bin/bash

mkdir "scale"

drh="scale/hollow"
drk="scale/kheap"

mkdir $drh
mkdir $drk

for filename in ../../instances/*.gr
	do
		o=$(echo $filename| cut -d'/' -f 4)
        echo "Running instance "$o
	   	o=$(echo $outf| cut -d'.' -f  2)
	   	ork=$drk"/"$o"-K.dat"
        orh=$drh"/"$o"-H.dat"
		./exp -t s -h k -n 50 < $filename > $ork		
		echo "Finished k-heap. Results in "$ork
    	./exp -t s -h h -n 50 < $filename > $orh
    	echo "Finished hollow. Results in "$orh
	   	echo "Done with "$filename
done

