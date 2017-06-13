#!/bin/bash

bdir="../data/"
rdir0=$bdir"res_p0/"
rdir1=$bdir"res_p1/"
rdir2=$bdir"res_p2/"

# clean folders of zero sized files
find $rdir0 -size 0 -delete
find $rdir1 -size 0 -delete
find $rdir2 -size 0 -delete

# create graphics folder
gdir=$bdir"graphics/"
mkdir $gdir

gdir0=$gdir"p0/"
gdir1=$gdir"p1/"
gdir2=$gdir"p2/"
mkdir $gdir0
mkdir $gdir1
mkdir $gdir2


# generate graphics data files
# p = 1 
python tabler.py -d $rdir1"mat/" -o $gdir1"gmatp1.dat" -x 1
python tabler.py -d $rdir1"flow/" -o $gdir1"gflowp1.dat" -x 2
python tabler.py -d $rdir1"fat/" -o $gdir1"gfatp1.dat" -x 2

# p = 0.5
python tabler.py -d $rdir0"mat/" -o $gdir0"gmatp0.dat" -x 1
python tabler.py -d $rdir0"flow/" -o $gdir0"gflowp0.dat" -x 2
python tabler.py -d $rdir0"fat/" -o $gdir0"gfatp0.dat" -x 2

## p = 2
python tabler.py -d $rdir2"mat/" -o $gdir2"gmatp2.dat" -x 1
python tabler.py -d $rdir2"flow/" -o $gdir2"gflowp2.dat" -x 2
python tabler.py -d $rdir2"fat/" -o $gdir2"gfatp2.dat" -x 2


# generate tables
tdir=$bdir"tables/"
mkdir $tdir

python tabler.py -d $gdir0 -o $tdir"tabp0.dat" -x 3
python tabler.py -d $gdir1 -o $tdir"tabp1.dat" -x 3
python tabler.py -d $gdir2 -o $tdir"tabp2.dat" -x 3

# generate graphics image files
./gen_graphics.sh
