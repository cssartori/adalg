#!/bin/bash

# Define a timestamp function
timestamp() {
  date +"%Y-%m-%d :: %H:%M:%S"
}


./exp -t i -h k -k 2 -n 25 > tinsk4.dat
./exp -t u -h k -k 2 -n 26 > tupdk4.dat
./exp -t d -h k -k 2 -n 26 > tdelRk4.dat


