#!/bin/bash

unzip -d instances/ instances/instances.zip 
gunzip instances/*.gz

make

for filename in instances/*.tsp
do
    echo $filename
    ./main < $filename  
done

make clean
rm main
rm instances/*.tsp

echo "DONE"
