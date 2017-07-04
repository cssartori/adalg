#!/bin/bash

ddir="../data/"

rdir=$ddir"results/"
bdir=$rdir"blossom/"
bcdir=$bdir"complete/"
bsdir=$bdir"solve/"
gdir=$rdir"greedy/"


# create graphics folder
grdir=$ddir"graphics/"
mkdir $grdir

# generate graphics data files
python tabler.py -d $bcdir -o $grdir"gbc.dat" -x 1
python tabler.py -d $bsdir -o $grdir"gbs.dat" -x 1
python tabler.py -d $gdir -o $grdir"ggc.dat" -x 1

# create tables folder
trdir=$ddir"tables/"
mkdir $trdir

# generate tables
python tabler.py -d $grdir -o $trdir"tabbg.dat" -x 2

# generate graphics image files
./gen_graphics.sh
