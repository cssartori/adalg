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

dm1=$drn1"mat/"
dm0=$drn0"mat/"
dm2=$drn2"mat/"
mkdir $dm1
mkdir $dm0
mkdir $dm2

df1=$drn1"flow/"
df0=$drn0"flow/"
df2=$drn2"flow/"
mkdir $df1
mkdir $df0
mkdir $df2

da1=$drn1"fat/"
da0=$drn0"fat/"
da2=$drn2"fat/"
mkdir $da1
mkdir $da0
mkdir $da2

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
		echo "Push-relabel running"
		../exp -o 2 < $filename > $df1$of
		echo "Fattest path running"
		../exp -o 3 < $filename > $da1$of		
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
		echo "Push-relabel running"
		../exp -o 2 < $filename > $df0$of		
		echo "Fattest path running"
		../exp -o 3 < $filename > $da0$of
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
		echo "Push-relabel running"
		../exp -o 2 < $filename > $df2$of		
		echo "Fattest path running"
		../exp -o 3 < $filename > $da2$of
		echo "Finished "$i"."
		timestamp
	   	echo "Done with "$filename
	   	i=$((i + 1))
done
