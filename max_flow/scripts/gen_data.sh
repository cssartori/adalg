#!/bin/bash

basedir="../res/"
datadir="../data/"
graphdir=$datadir"graphs/"

mkdir $datadir
mkdir $datadir"t1/"
mkdir $datadir"t2/"
mkdir $datadir"t3/"
mkdir $datadir"t4/"
mkdir $datadir"t5/"
mkdir $datadir"t5/D8/"
mkdir $datadir"t5/D16/"
mkdir $datadir"t6/"
mkdir $datadir"t6/D8/"
mkdir $datadir"t6/D16/"
mkdir $datadir"t7/"
mkdir $datadir"t7/D8/"
mkdir $datadir"t7/D16/"
mkdir $datadir"t8/"
mkdir $datadir"t8/D8/"
mkdir $datadir"t8/D16/"
mkdir $datadir"t9/"
mkdir $datadir"t10/"

# Type 1 instances
python tabler.py -d $basedir"t1/C100/" -o $datadir"t1/dt1_k100.dat" -x 1
python tabler.py -d $basedir"t1/C10000/" -o $datadir"t1/dt1_k10000.dat" -x 1

# Type 2 instances
python tabler.py -d $basedir"t2/C100/" -o $datadir"t2/dt2_k100.dat" -x 1
python tabler.py -d $basedir"t2/C10000/" -o $datadir"t2/dt2_k10000.dat" -x 1

# Type 3 instances
python tabler.py -d $basedir"t3/C100/" -o $datadir"t3/dt3_k100.dat" -x 1
python tabler.py -d $basedir"t3/C10000/" -o $datadir"t3/dt3_k10000.dat" -x 1

# Type 4 instances
python tabler.py -d $basedir"t4/C100/" -o $datadir"t4/dt4_k100.dat" -x 1
python tabler.py -d $basedir"t4/C10000/" -o $datadir"t4/dt4_k10000.dat" -x 1

# Type 5 instances
python tabler.py -d $basedir"t5/D8/C100/" -o $datadir"t5/D8/dt5_d8_k100.dat" -x 1
python tabler.py -d $basedir"t5/D8/C10000/" -o $datadir"t5/D8/dt5_d8_k10000.dat" -x 1
python tabler.py -d $basedir"t5/D16/C100/" -o $datadir"t5/D16/dt5_d16_k100.dat" -x 1
python tabler.py -d $basedir"t5/D16/C10000/" -o $datadir"t5/D16/dt5_d16_k10000.dat" -x 1

# Type 6 instances
python tabler.py -d $basedir"t6/D8/C100/" -o $datadir"t6/D8/dt6_d8_k100.dat" -x 1
python tabler.py -d $basedir"t6/D8/C10000/" -o $datadir"t6/D8/dt6_d8_k10000.dat" -x 1
python tabler.py -d $basedir"t6/D16/C100/" -o $datadir"t6/D16/dt6_d16_k100.dat" -x 1
python tabler.py -d $basedir"t6/D16/C10000/" -o $datadir"t6/D16/dt6_d16_k10000.dat" -x 1

# Type 7 instances
python tabler.py -d $basedir"t7/D8/C100/" -o $datadir"t7/D8/dt7_d8_k100.dat" -x 1
python tabler.py -d $basedir"t7/D8/C10000/" -o $datadir"t7/D8/dt7_d8_k10000.dat" -x 1
python tabler.py -d $basedir"t7/D16/C100/" -o $datadir"t7/D16/dt7_d16_k100.dat" -x 1
python tabler.py -d $basedir"t7/D16/C10000/" -o $datadir"t7/D16/dt7_d16_k10000.dat" -x 1

# Type 8 instances
python tabler.py -d $basedir"t8/D8/C100/" -o $datadir"t8/D8/dt8_d8_k100.dat" -x 1
python tabler.py -d $basedir"t8/D8/C10000/" -o $datadir"t8/D8/dt8_d8_k10000.dat" -x 1
python tabler.py -d $basedir"t8/D16/C100/" -o $datadir"t8/D16/dt8_d16_k100.dat" -x 1
python tabler.py -d $basedir"t8/D16/C10000/" -o $datadir"t8/D16/dt8_d16_k10000.dat" -x 1

# Type 9 instances
python tabler.py -d $basedir"t9/" -o $datadir"t9/dt9.dat" -x 1

# Type 10 instances
python tabler.py -d $basedir"t10/" -o $datadir"t10/dt10.dat" -x 1


# Generate Latex table files
tablesdir=$datadir"tables/"
mkdir $tablesdir

python tabler.py -d $datadir"t1/" -o $tablesdir"tab_t1.dat" -x 2
python tabler.py -d $datadir"t2/" -o $tablesdir"tab_t2.dat" -x 2
python tabler.py -d $datadir"t3/" -o $tablesdir"tab_t3.dat" -x 2
python tabler.py -d $datadir"t4/" -o $tablesdir"tab_t4.dat" -x 2
python tabler.py -d $datadir"t5/D8/" -o $tablesdir"tab_t5_d8.dat" -x 2
python tabler.py -d $datadir"t5/D16/" -o $tablesdir"tab_t5_d16.dat" -x 2
python tabler.py -d $datadir"t6/D8/" -o $tablesdir"tab_t6_d8.dat" -x 2
python tabler.py -d $datadir"t6/D16/" -o $tablesdir"tab_t6_d16.dat" -x 2
python tabler.py -d $datadir"t7/D8/" -o $tablesdir"tab_t7_d8.dat" -x 2
python tabler.py -d $datadir"t7/D16/" -o $tablesdir"tab_t7_d16.dat" -x 2
python tabler.py -d $datadir"t8/D8/" -o $tablesdir"tab_t8_d8.dat" -x 2
python tabler.py -d $datadir"t8/D16/" -o $tablesdir"tab_t8_d16.dat" -x 2
python tabler.py -d $datadir"t9/" -o $tablesdir"tab_t9.dat" -x 2
python tabler.py -d $datadir"t10/" -o $tablesdir"tab_t10.dat" -x 2

# Create folder for graphics
mkdir $graphdir

./gen_graphs.sh
