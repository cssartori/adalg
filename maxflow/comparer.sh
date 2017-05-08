#!/bin/bash

# Define a timestamp function                                                                                                                                           
timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}

c=0
i=0

for filename in ./instances/*.gr
	do
		o=$(echo $filename| cut -d'/' -f 3)
        echo "Running instance "$o
    	echo -n "Start:   " 
    	timestamp
		rext=$(./ext < $filename)
		rtester=$(./tester < $filename)

		if ((rext==rtester)) ; then
		    echo -n "Correct"   
		    c=$((c + 1))
		else
		    echo -n "Incorrect"
		fi
		echo "  ( "$rext" = "$rtester" )"
		echo -n "Finished:   " 
		timestamp
		echo "----------"
		i=$((i + 1))
done		

echo $c" correct from "$i
