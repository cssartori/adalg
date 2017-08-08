gcc -O3 ../instances/new_washington.c -o ../instances/new_washington 2> /dev/null

mkdir "../instances/exp"

python generate.py
