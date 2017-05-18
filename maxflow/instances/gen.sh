gcc -O3 new_washington.c -o new_washington 2> /dev/null

mkdir "exp"

for s in {50,100,200,300,400,500,600,700,800}
do
    ./new_washington 1 $s $s $s exp/it_1_$s.gr
    ./new_washington 2 $s $s $s exp/it_2_$s.gr
    ./new_washington 3 $s $s $s exp/it_3_$s.gr
    ./new_washington 4 $s $s $s exp/it_4_$s.gr
done
echo "Done types 1,2,3,4"

for s in {50,100,200,300,400,500,600,800}
do
    ./new_washington 5 $s 8 $s exp/it_5_$s.gr
    ./new_washington 6 $s $s 8 $s exp/it_6_$s.gr
    ./new_washington 7 $s $s 8 $s exp/it_7_$s.gr
    ./new_washington 8 $s $s 8 $s exp/it_8_$s.gr
done
echo "Done types 5,6,7,8"

for s in {32768,65536,131072,262144}
do
    ./new_washington 9 $s exp/it_9_$s.gr
    ./new_washington 10 $s exp/it_10_$s.gr
done
echo "Done types 9,10"
