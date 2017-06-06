#!/bin/bash

# Define a timestamp function                                                                                                                                           
timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}

mkdir "../instances/"
dirn="../instances/exp/"
mkdir $dirn

for n in {128,256,512,1024,2048,4096,8192,16384,32768,65536}
do
    p="0.001"
    fname=$dirn"bg_n"$n".gr"
    ../gen -n $n -p $p > $fname
    echo "Finished "$n" in file "$fname
    timestamp
    
done    
