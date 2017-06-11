#!/bin/bash

bdir="../data/"
rdir0=$bdir"res_p0/"
rdir1=$bdir"res_p1/"
rdir2=$bdir"res_p2/"
gdir=$bdir"graphics/"

mkdir $gdir

# p = 1 
python tabler.py -d $rdir1"mat/" -o $gdir"gmatp1.dat" -x 1
python tabler.py -d $rdir1"flow/" -o $gdir"gflowp1.dat" -x 2

# p = 0.5
#python tabler.py -d $rdir0"mat/" -o $gdir"gmatp0.dat" -x 1
#python tabler.py -d $rdir0"flow/" -o $gdir"gflowp0.dat" -x 2

## p = 2
#python tabler.py -d $rdir2"mat/" -o $gdir"gmatp2.dat" -x 1
#python tabler.py -d $rdir2"flow/" -o $gdir"gflowp2.dat" -x 2


./gen_graphics.sh
