#!/bin/bash

# Define a timestamp function                                                                                                                                           
timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}


mkdir "scale"

drh="scale/hollow"
drk="scale/kheap"

mkdir $drh
mkdir $drk

for filename in ../../instances/*.gr
	do
		o=$(echo $filename| cut -d'/' -f 4)
		echo "==============================================="
        echo "Running instance "$o
	timestamp
	   	o=$(echo $o| cut -d'.' -f  2)
	   	ork=$drk"/"$o"-K.dat"
        orh=$drh"/"$o"-H.dat"
		./exp -t s -h k -n 50 < $filename > $ork		
		echo "Finished k-heap. Results in "$ork
		timestamp
    	./exp -t s -h h -n 50 < $filename > $orh
    	echo "Finished hollow. Results in "$orh
	timestamp
	   	echo "Done with "$filename
done

