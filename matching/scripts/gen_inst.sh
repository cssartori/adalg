#!/bin/bash

# Define a timestamp function                                                                                                                                           
timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}

mkdir "../instances/"
dirn1="../instances/exp_p1/"
dirn2="../instances/exp_p2/"
dirn0="../instances/exp_p0/"
mkdir $dirn1
mkdir $dirn2
mkdir $dirn0

echo "================================================"
echo "Generating instances with p = 1"

for n in {8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304}
do
    fname=$dirn1"bg_n"$n".gr"
    ../gen -n $n -p 1 > $fname
    echo "Finished "$n" in file "$fname
    timestamp
done    

echo "================================================"


echo "================================================"
echo "Generating instances with p = 0.5"

for n in {8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304}
do
    fname=$dirn0"bg_n"$n".gr"
    ../gen -n $n -p 0.5 > $fname
    echo "Finished "$n" in file "$fname
    timestamp
done    

echo "================================================"

echo "================================================"
echo "Generating instances with p = 2"

for n in {8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304}
do
    fname=$dirn2"bg_n"$n".gr"
    ../gen -n $n -p 2 > $fname
    echo "Finished "$n" in file "$fname
    timestamp
done    

echo "================================================"
