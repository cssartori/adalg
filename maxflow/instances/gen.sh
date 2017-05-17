gcc -O3 new_washington.c -o new_washington 2> /dev/null

mkdir "exp"

for s in {50,100,150,200,250,300,350,400,450,500}
do
    ./new_washington 1 $s $s $s exp/it_1_$s.gr
done
echo "Done 1"
for s in {50,100,150,200,250,300,350,400,450,500}
do
    ./new_washington 2 $s $s $s exp/it_2_$s.gr
done
echo "Done 2"
for s in {50,100,150,200,250,300,350,400,450,500}
do
    ./new_washington 3 $s $s $s exp/it_3_$s.gr
done
echo "Done 3"
#for s in {50,100,150,200,250,300,350,400,450,500}
#do
#    ./new_washington 5 $s $s $s exp/it_5_$s.gr
#done
