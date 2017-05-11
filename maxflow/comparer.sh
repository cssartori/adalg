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
    	echo -n -e "Started:\t" 
    	timestamp
		rfat=$(./fat < $filename)
		rtester=$(./tester < $filename)

		if ((rfat==rtester)) ; then
		    echo -n "Correct"   
		    c=$((c + 1))
		else
		    echo -n "Incorrect"
		fi
		echo "  ( "$rfat" = "$rtester" )"
		echo -n -e "Finished:\t" 
		timestamp
		echo "----------"
		i=$((i + 1))
done		

echo "Result:  "$c" out of "$i" correct."
