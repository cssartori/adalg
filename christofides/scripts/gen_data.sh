#!/bin/bash

ddir="../data/"

rdir=$ddir"results/"
bdir=$rdir"blossom/"
gdir=$rdir"greedy/"


# create graphics folder
grdir=$ddir"graphics/"
mkdir $grdir

# generate graphics data files
python tabler.py -d $bdir -o $grdir"gblossom.dat" -x 1
python tabler.py -d $gdir -o $grdir"ggreedy.dat" -x 1

# create tables folder
trdir=$ddir"tables/"
mkdir $trdir

# generate tables
python tabler.py -d $grdir0 -o $trdir"tabbg.dat" -x 2

# generate graphics image files
./gen_graphics.sh
