#!/bin/bash

timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}

idir="../instances/"

odir="../data/"
mkdir $odir
bodir=$odir"blossom/"
godir=$odir"greedy/"
mkdir $bodir
mkdir $godir

unzip -d $idir $idir"instances.zip" 
#gunzip $idir"*.gz"

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
    	
		rmain=$(../main < $filename)

		dev=$(bc <<< "scale=2; ("$rmain"-"${bks[$ni]}")/"${bks[$ni]})
		echo $dev

		comp=$(bc -l <<< $dev">0.5")
		echo "comp = "$comp
		if (($comp == 0)) ; then
		    echo -n "Correct"   
		    c=$((c + 1))
		else
		    echo -n "WARNING: approx. is not right"
		fi
		echo "  ( "$rmain" = "${bks[$ni]}" )"
		echo -n -e "Finished:\t" 
		timestamp
		echo "----------"
		i=$((i + 1))
		
#		./main < $filename
done		

echo "Result:  "$c" out of "$i" correct."



make -C ../ clean
rm main
rm instances/*.tsp

echo "DONE"
