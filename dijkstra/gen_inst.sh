#!/bin/bash

# Define a timestamp function
timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}

m=16777216

for n in {2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608}
do
		outf="./inst/"gcn$n".gr"
		echo "Generating for "$n
		./gen -n $n -l $m > $outf		
	   	echo "Created graph in "$outf
	   	timestamp
done
