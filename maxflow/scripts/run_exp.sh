#!/bin/bash

# Define a timestamp function                                                                                                                                           
timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}

drn="../res"
mkdir $drn
i=0

for filename in ../instances/exp/*.gr
	do
		f=$(echo $filename| cut -d'/' -f 4)
		echo "==============================================="
        echo "Running instance "$i": "$f
	    timestamp
	   	f=$(echo $f| cut -d'.' -f 1)
        of=$drn"/R_t_"$f".dat"
		../exp -k 4 -n 10 < $filename > $of		
		echo "Finished "$i". Results in "$of
		timestamp
	   	echo "Done with "$filename
	   	i=$((i + 1))
done
