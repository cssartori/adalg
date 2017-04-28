#!/bin/bash

# Define a timestamp function
timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}

n=65536
for m in {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608}
do
		outf="./inst/"gcm$m".gr"
		echo "Generating for "$m
		./gen -n $n -l $m > $outf		
	   	echo "Created graph in "$outf
	   	timestamp
done
