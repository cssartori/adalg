import os

dirname="exp"

for i in range(6,12):
    for j in range(6,12):
        if i+j <= 18:  #maximum sum of exponents so that run time is not > 300 s
            r = 2**i
            c = 2**j
            for k in [100,10000]:
                par1 = ("./new_washington 1 %i %i %i %s/gm1_r%i_c%i_k%i.gr" % (r,c,k,dirname,r,c,k))
                os.system(par1)
                par2 = ("./new_washington 2 %i %i %i %s/gm2_r%i_c%i_k%i.gr" % (r,c,k,dirname,r,c,k))
                os.system(par2)
                par3 = ("./new_washington 3 %i %i %i %s/gm3_r%i_c%i_k%i.gr" % (r,c,k,dirname,r,c,k))    
                os.system(par3)
                print "Finished [1,2,3]: %i %i %i" % (r,c,k)

