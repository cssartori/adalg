#!/bin/bash

# Define a timestamp function                                                                                                                                           
timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}

mkdir "../data/"

drn1="../data/res_p1/"
drn0="../data/res_p0/"
drn2="../data/res_p2/"
mkdir $drn1
mkdir $drn0
mkdir $drn2

dm1=$drn1"mat_p1/"
dm0=$drn0"mat_p0/"
dm2=$drn2"mat_p2/"
mkdir $dm1
mkdir $dm0
mkdir $dm2

df1=$drn1"flow_p1/"
df0=$drn0"flow_p0/"
df2=$drn2"flow_p2/"
mkdir $df1
mkdir $df0
mkdir $df2

i=0
for filename in ../instances/exp_p1/*.gr
	do
		f=$(echo $filename| cut -d'/' -f 4)
		echo "==============================================="
        echo "Running instance "$i": "$f
	    timestamp
	   	f=$(echo $f| cut -d'.' -f 1)
        of="/R_"$f".dat"
        echo "Matching running"
		../exp -o 1 < $filename > $dm1$of
		echo "Flow running"
		../exp -o 2 < $filename > $df1$of		
		echo "Finished "$i"."
		timestamp
	   	echo "Done with "$filename
	   	i=$((i + 1))
done

i=0
for filename in ../instances/exp_p2/*.gr
	do
		f=$(echo $filename| cut -d'/' -f 4)
		echo "==============================================="
        echo "Running instance "$i": "$f
	    timestamp
	   	f=$(echo $f| cut -d'.' -f 1)
        of="/R_"$f".dat"
        echo "Matching running"
		../exp -o 1 < $filename > $dm2$of
		echo "Flow running"
		../exp -o 2 < $filename > $df2$of		
		echo "Finished "$i"."
		timestamp
	   	echo "Done with "$filename
	   	i=$((i + 1))
done

i=0
for filename in ../instances/exp_p0/*.gr
	do
		f=$(echo $filename| cut -d'/' -f 4)
		echo "==============================================="
        echo "Running instance "$i": "$f
	    timestamp
	   	f=$(echo $f| cut -d'.' -f 1)
        of="/R_"$f".dat"
        echo "Matching running"
		../exp -o 1 < $filename > $dm0$of
		echo "Flow running"
		../exp -o 2 < $filename > $df0$of		
		echo "Finished "$i"."
		timestamp
	   	echo "Done with "$filename
	   	i=$((i + 1))
done
