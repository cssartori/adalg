import os

dirname="../instances/exp"
total = 0
count = 0
d = dict()
for i in range(6,11):
    for j in range(6,11):
        if i+j <= 18 and not (i+j in d):  #maximum sum of exponents so that run time is not > 300 s
            r = 2**i
            c = 2**j
            d[i+j] = True
            print "G(%i,%i):  %i , %i" % (i,j,r,c)
            for k in [100,10000]:
                par1 = ("../instances/new_washington 1 %i %i %i %s/gm1_r%i_c%i_k%i.gr" % (r,c,k,dirname,r,c,k))
                os.system(par1)
                par2 = ("../instances/new_washington 2 %i %i %i %s/gm2_r%i_c%i_k%i.gr" % (r,c,k,dirname,r,c,k))
                os.system(par2)
                par3 = ("../instances/new_washington 3 %i %i %i %s/gm3_r%i_c%i_k%i.gr" % (r,c,k,dirname,r,c,k))    
                os.system(par3)
                print "Finished [1,2,3]: %i %i %i" % (r,c,k)
                count += 3
                

print "Finished %i types 1, 2, 3" % (count)
print "========================================"
total += count

count = 0
d = dict()
for i in range(6,12):
    for j in range(6,i+1):
        if i+j <= 22 and not (i+j in d):
            r = 2**i
            c = 2**j
            d[i+j] = True
            print "G(%i,%i):  %i , %i" % (i,j,r,c)
            for k in [100, 10000]:
                par4 = ("../instances/new_washington 4 %i %i %i %s/gm4_r%i_c%i_k%i.gr" % (r,c,k,dirname,r,c,k))
                os.system(par4)
                print "Finished [4]: %i %i %i" % (r,c,k)
                count += 1
                
print "Finished %i type 4" % (count)
print "========================================"
total += count

count = 0
for i in range(6,10):
    for j in range(3,5):
        d = 2**i
        D = 2**j
        for k in [100,10000]:
            par5 = ("../instances/new_washington 5 %i %i %i %s/gm5_d%i_D%i_k%i.gr" % (d,D,k,dirname,d,D,k))
            os.system(par5)
            print "Finished [5]: %i %i %i" % (d,D,k)
            count += 1
            
print "Finished %i type 5" % (count)
print "========================================"
total += count

count = 0
dc = dict()
for i in range(6,9):
    for j in range(6,9):
        n = 2**i
        m = 2**j
        if i+j in dc:
            continue
        dc[i+j] = True
        for d in range(3,5):
            D = 2**d
            print "G(%i,%i,%i):  %i , %i" % (i,j,D,n,m)
            for k in [100,10000]:
                par6 = ("../instances/new_washington 6 %i %i %i %i %s/gm6_n%i_m%i_D%i_k%i.gr" % (n,m,D,k,dirname,n,m,D,k))
                os.system(par6)
                print "Finished [6]: %i %i %i %i" % (n,m,D,k)
                count += 1
            
print "Finished %i type 6" % (count)
print "========================================"
total += count

count = 0
dc = dict()
for i in range(6,10):
    for j in range(6,10):
        n = 2**i
        m = 2**j
        if i+j in dc:
            continue
        dc[i+j] = True
        for d in range(3,5):
            D = 2**d
            print "G(%i,%i,%i):  %i , %i" % (i,j,D,n,m)
            for k in [100,10000]:
                par7 = ("../instances/new_washington 7 %i %i %i %i %s/gm7_n%i_m%i_D%i_k%i.gr" % (n,m,D,k,dirname,n,m,D,k))
                os.system(par7)
                par8 = ("../instances/new_washington 8 %i %i %i %i %s/gm8_n%i_m%i_D%i_k%i.gr" % (n,m,D,k,dirname,n,m,D,k))
                os.system(par8)
                print "Finished [7,8]: %i %i %i %i" % (n,m,D,k)
                count += 2
            
print "Finished %i types 7,8" % (count)
print "========================================"
total += count      

count = 0
for i in range(14,25):
    n = 2**i
    par9 = ("../instances/new_washington 9 %i %s/gm9_n%i.gr" % (n,dirname,n))
    os.system(par9)
    print "Finished [9]: %i" % (n)
    count += 1

print "Finished %i types 9" % (count)
print "========================================"
total += count

count = 0
for i in range(6,16):
    n = 2**i
    par10 = ("../instances/new_washington 10 %i %s/gm10_n%i.gr" % (n,dirname,n))
    os.system(par10)
    print "Finished [10]: %i" % (n)
    count += 1

print "Finished %i types 10" % (count)
print "========================================"
total += count

print "Generated %i total instances" % (total)
