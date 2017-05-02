import sys, os, csv, argparse;
import math;
from operator import itemgetter

#Prepare the arguments the program shall receive
def __prepareargs__():
    parser = argparse.ArgumentParser(description='Creates result tables for N-Heap Dijkstra implementation')
    parser.add_argument('-d', nargs=1, type=str, help='directory with results', required=True)
    parser.add_argument('-o', nargs=1, type=str, help='output file name', required=True)
    parser.add_argument('-x', nargs=1, type=int, help='experiment identifier (<insert, update, delete> = 1, <complex, scale>Graph = 2, <complex, scale>Table=3)', required=True)
    parser.add_argument('-e', nargs=1, type=str, help='result files extension (default = \'.dat\')', required=False, default = ['.dat'])

        
    return parser

#Parse the input arguments and returns a dictionary with them
def __getargs__(parser):
    args = vars(parser.parse_args())
    return args



def __proc_file_heap__(filename):
    lr = []
    
    with open(filename, 'rb') as cfile:
        cdata = csv.reader(cfile, delimiter=',')
     
        for row in cdata:
            i = int(row[0])
            t = row[1]
            k = int(row[2])
            nswaps = int(row[4])
            time = float(row[6])
            tpe = float(row[8])             
            l = [i, t, k, nswaps, time, tpe]           
            lr.append(l)

    return lr


def __proc_dir_heap__(dirname, outfname, rfext):
    outf = open(outfname, "w")
    
    print("reading files")
    
    lr = [] 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print("Reading file "+file)
               
        lf = __proc_file_heap__(dirname+file)

        for l in lf:
            lr.append(l)
        
        # Generate graph file
#        lf = sorted(lf, key = lambda x: (x[0])) #sort by experiment
#        gfname = "G"+file.split(".")[0]+".dat"
#        outg = open(dirname+gfname, "w")
#        for l in lf:
#            outg.write("%i %i %i %Le %Le\n" % (l[0], l[1], l[2], l[3], l[4]))
#        
#        outg.close()
        
        
    # Generate table file       
	lr = sorted(lr, key = lambda x: (x[0], x[2])) #sort by experiment and k
	avg = dict({})
	for l in lr:
	    avg[l[2]] = [0,0.0,0]
	    
	ne = -1
    for l in lr:
        if ne != l[0]:
            if ne != -1:
                 outf.write("\\\\")
            outf.write("\n%i " % (l[0]))
            ne = l[0]
                        
        outf.write(" & %i & %.2Le " % (l[3], l[4]))
        avg[l[2]] = [avg[l[2]][0]+l[3], avg[l[2]][1]+l[4], avg[l[2]][2]+1]

    outf.write("\\\\\n\\textbf{Media} ")
    for a in avg:
        outf.write(" & %.2f & %.2Le " % (float(avg[a][0]/avg[a][2]), avg[a][1]/avg[a][2]))
    
    outf.write("\\\\")
    outf.close()


   
def __proc_file_scale__(filename, op):
    l = []
    with open(filename, 'rb') as cfile:
            if op == "gr":
                cdata = csv.reader(cfile, delimiter=",")
                t = ' '
                k = 0
                n = 0
                m = 0
                nins = 0
                ndel = 0
                nupd = 0
                mem = 0
                time = 0.0              
                nexp = 0
                
                for row in cdata:
                    t = row[1]
                    k = int(row[2])
                    n = int(row[3])
                    m = int(row[4])
                    nins += int(row[5])
                    ndel += int(row[6])
                    nupd += int(row[7])
                    mem  += int(row[8])
                    time += float(row[9])
                    nexp += 1
                    
                    if int(row[5]) > n:
                        print "Error on I row "+str(row[0])
                    if int(row[6]) > n:
                        print "Error on D row "+str(row[0])
                    if int(row[7]) > m:
                        print "Error on U row "+str(row[0])
                               
                nins_avg = float(nins/nexp)
                ndel_avg = float(ndel/nexp)
                nupd_avg = float(nupd/nexp)
                mem_avg  = float(mem/nexp)
                time_avg = float(time/nexp)
                       
                l = [t, k, n, m, nins_avg, ndel_avg, nupd_avg, mem_avg, time_avg]
            else:
                cdata = csv.reader(cfile, delimiter=" ")
                
                t = ' '
                k = 0
                n = 0
                m = 0
                ins = 0
                ups = 0
                des = 0
                mem = 0
                time = 0.0              
                    
                for row in cdata:
                    t = row[0]
                    k = int(row[1])
                    n = int(row[3])
                    m = int(row[4])
                    ins = int(row[5])
                    des = int(row[6])
                    ups = int(row[7])
                    mem  = float(row[11])
                    time = float(row[12])
                        
                    lt = [t, k, n, m, ins, des, ups, mem, time]
                    l.append(lt)

    return l

def __proc_dir_graph_scale__(dirname, outfname, rfext):
    outf = open(outfname, "w")
    
    print("reading files")
    
    lr = [] 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print("Reading file "+file)
        
        lf = __proc_file_scale__(dirname+file, "gr")        
        lr.append(lf)
  
    # Generate graph file       
	lr = sorted(lr, key = lambda x: (x[2])) #sort by number of vertices

    for l in lr:
        # type k log2(n) n m I D U pI pD pU mem t t/O
        outf.write("%c %i %u %u %u %u %u %u %f %f %f %f %Le %Le\n" % (l[0], l[1], math.log(l[2], 2), l[2], l[3], l[4], l[5], l[6], float(l[4]/l[2]), float(l[5]/l[3]), float(l[6]/l[3]), float(l[7]/(1024*1024)), l[8], l[8]/((l[2]+l[3])*math.log(l[2]))))
        
    outf.close()


def __proc_dir_table_scale__(dirname, outfname, rfext, x=3):
    outf = open(outfname, "w")
    
    print("reading files")
    
    lr = [] 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print("Reading file "+file)
        
        lf = __proc_file_scale__(dirname+file, "tb")
        for l in lf:        
            lr.append(l)
    
    
	
	vr = 2
    if x == 4:
        vr = 3    
    
    #print ("vr = " % (vr))
    # Generate table file       
    lr = sorted(lr, key = lambda x: (x[vr], x[1])) #sort by number of vertices and k
	
    avg = dict({})
    for l in lr:
        # ins des ups mem time
        avg[l[1]] = [0.0,0.0,0.0,0.0,0.0]
    
    nn = -1
    c=0
    mavg = 0
    navg = 0
   
    for l in lr:
        if nn != l[vr]:
            if nn != -1:
                outf.write("\\\\")
            c += 1
            navg += l[2]
            mavg += l[3]
                      
            outf.write("\n%u & %u & %u " % (c, l[2], l[3]))            
            nn = l[vr]
        
        if x == 3 or x == 4: # print operations, but not memory (complexity)
            outf.write(" & %i & %i & %i & %.2Le " % (l[4], l[5], l[6], l[8]))            
        elif x == 5: # print memory, but not operations (scale)
            outf.write(" & %.2Le & %.2Le " % (l[7], l[8]))
            
        avg[l[1]][0] += l[4]
        avg[l[1]][1] += l[5]
        avg[l[1]][2] += l[6]
        avg[l[1]][3] += l[7]
        avg[l[1]][4] += l[8]
        
    outf.write("\\\\\n\\textbf{Media} & %.2f & %.2f " % (navg/c, mavg/c))
    
    for a in avg:
        if x == 3 or x == 4:
            outf.write(" & %.2Le & %.2Le & %.2Le & %.2Le" % (avg[a][0]/c, avg[a][1]/c, avg[a][2]/c, avg[a][4]/c))
        elif x == 5:
            outf.write(" & %.2Le & %.2Le" % (avg[a][3]/c, avg[a][4]/c))
    
    outf.write("\\\\")
    outf.close()
    


#The main module, in case this program was called as the main program
if __name__ == '__main__':
    #receive and prepare the arguments
    parser = __prepareargs__()
    args = __getargs__(parser)
    
    #read parameters
    dirname  = args['d'][0]
    outfname = args['o'][0]
    exp      = int(args['x'][0])
    rfext    = args['e'][0]
    
    if exp == 1:
        __proc_dir_heap__(dirname, outfname, rfext)    
    elif exp == 2:
        __proc_dir_graph_scale__(dirname, outfname, rfext)
    elif exp == 3 or exp == 4 or exp == 5:
        __proc_dir_table_scale__(dirname, outfname, rfext, exp)
#    elif exp == 5:
#        __proc_exp55__(dirname, outfname, rfext)
#    elif exp == 11:
#        __proc_exp11__(dirname, outfname, rfext)

    
   
    

    
    
                
                
