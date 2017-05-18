import os

for i in range(1,11):
    par = ("./new_washington 1 %i %i 100 it%i.gr" % (i,i,i))    
    os.system(par)
