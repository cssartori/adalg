#!/bin/bash

basedir="../res/"
datadir="../data/"

mkdir $datadir

# Type 1 instances
python tabler.py -d $basedir"t1/C100/" -o $datadir"dt1_k100.dat" -x 1
python tabler.py -d $basedir"t1/C10000/" -o $datadir"dt1_k10000.dat" -x 1

# Type 2 instances
python tabler.py -d $basedir"t2/C100/" -o $datadir"dt2_k100.dat" -x 1
python tabler.py -d $basedir"t2/C10000/" -o $datadir"dt2_k10000.dat" -x 1

# Type 3 instances
python tabler.py -d $basedir"t3/C100/" -o $datadir"dt3_k100.dat" -x 1
python tabler.py -d $basedir"t3/C10000/" -o $datadir"dt3_k10000.dat" -x 1

# Type 4 instances
python tabler.py -d $basedir"t4/C100/" -o $datadir"dt4_k100.dat" -x 1
python tabler.py -d $basedir"t4/C10000/" -o $datadir"dt4_k10000.dat" -x 1

# Type 5 instances
python tabler.py -d $basedir"t5/D8/C100/" -o $datadir"dt5_d8_k100.dat" -x 1
python tabler.py -d $basedir"t5/D8/C10000/" -o $datadir"dt5_d8_k10000.dat" -x 1
python tabler.py -d $basedir"t5/D16/C100/" -o $datadir"dt5_d16_k100.dat" -x 1
python tabler.py -d $basedir"t5/D16/C10000/" -o $datadir"dt5_d16_k10000.dat" -x 1

# Type 6 instances
python tabler.py -d $basedir"t6/D8/C100/" -o $datadir"dt6_d8_k100.dat" -x 1
python tabler.py -d $basedir"t6/D8/C10000/" -o $datadir"dt6_d8_k10000.dat" -x 1
python tabler.py -d $basedir"t6/D16/C100/" -o $datadir"dt6_d16_k100.dat" -x 1
python tabler.py -d $basedir"t6/D16/C10000/" -o $datadir"dt6_d16_k10000.dat" -x 1

# Type 7 instances
python tabler.py -d $basedir"t7/D8/C100/" -o $datadir"dt7_d8_k100.dat" -x 1
python tabler.py -d $basedir"t7/D8/C10000/" -o $datadir"dt7_d8_k10000.dat" -x 1
python tabler.py -d $basedir"t7/D16/C100/" -o $datadir"dt7_d16_k100.dat" -x 1
python tabler.py -d $basedir"t7/D16/C10000/" -o $datadir"dt7_d16_k10000.dat" -x 1

# Type 8 instances
python tabler.py -d $basedir"t8/D8/C100/" -o $datadir"dt8_d8_k100.dat" -x 1
python tabler.py -d $basedir"t8/D8/C10000/" -o $datadir"dt8_d8_k10000.dat" -x 1
python tabler.py -d $basedir"t8/D16/C100/" -o $datadir"dt8_d16_k100.dat" -x 1
python tabler.py -d $basedir"t8/D16/C10000/" -o $datadir"dt8_d16_k10000.dat" -x 1

# Type 9 instances
python tabler.py -d $basedir"t9/" -o $datadir"dt9.dat" -x 1

# Type 10 instances
python tabler.py -d $basedir"t10/" -o $datadir"dt10.dat" -x 1
