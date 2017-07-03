#!/bin/bash

timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}

idir="../instances/"

odir="../data/"
mkdir $odir
odir=$odir"results/"
mkdir $odir
bodir=$odir"blossom/"
godir=$odir"greedy/"
mkdir $bodir
mkdir $godir

unzip -d $idir $idir"instances.zip" 

make -C ../

#declare a dictionary to keep BKS information
declare -A bks

#Read the BKS data and insert it in a dictionary
while IFS=, read col1 col2
do
    if [[ $col1 != \#* ]]; then 
        bks+=(["$col1"]="$col2")
    fi
done < $idir"bks.dat"

#run instances
c=0
i=0
for filename in ../instances/*.tsp
	do
		fn=$(echo $filename| cut -d'/' -f 3)
    	echo -n -e "Started:\t" 
    	timestamp
    	
    	ni=$(echo $fn| cut -d'.' -f 1)
    	echo "Running instance "$ni
    	
    	bof=$bodir$ni".dat"
    	gof=$godir$ni".dat"
    	echo "Running christofides using blossom v"
		../exp -b ${bks[$ni]} -m b -n 10 < $filename > $bof
		echo "Running christofides using greedy"
		../exp -b ${bks[$ni]} -m g -n 10 < $filename > $gof

		echo -n -e "Finished:\t" 
		timestamp
		echo "----------"
		i=$((i + 1))
done		

echo "Executed "$i" instances."


make -C ../ clean
rm ../main
rm ../instances/*.tsp

echo "DONE"
