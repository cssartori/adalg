import sys, os, csv, argparse;
import math;
from operator import itemgetter

#Prepare the arguments the program shall receive
def __prepareargs__():
    parser = argparse.ArgumentParser(description='Creates result tables for Fattest Path Max-FLow')
    parser.add_argument('-d', nargs=1, type=str, help='directory with results', required=True)
    parser.add_argument('-o', nargs=1, type=str, help='output file name', required=True)
    parser.add_argument('-x', nargs=1, type=int, help='experiment identifier (<generate average files> = 1, <generate tables> = 2)', required=True)
    parser.add_argument('-e', nargs=1, type=str, help='result files extension (default = \'.dat\')', required=False, default = ['.dat'])

        
    return parser

#Parse the input arguments and returns a dictionary with them
def __getargs__(parser):
    args = vars(parser.parse_args())
    return args


 
def __proc_data_file__(filename, op):
    l = []
    with open(filename, 'rb') as cfile:
            if op == "avg": #generate average file
                cdata = csv.reader(cfile, delimiter=",")
                k = 0
                n = 0
                m = 0
                ndij = 0
                nins = 0
                ndel = 0
                nupd = 0
                nswp = 0
                nitr = 0
                mem = 0
                time = 0.0 
                flow = 0
                seed = 0
                nlog = 0.0             
                nexp = 0
                
                for row in cdata:
                    k = int(row[1])
                    n = int(row[2])
                    m = int(row[3])
                    ndij += int(row[4])
                    nins += int(row[5])
                    ndel += int(row[6])
                    nupd += int(row[7])
                    nswp += int(row[8])
                    nitr += int(row[9])
                    mem  += int(row[10])
                    time += float(row[11])
                    flow = int(row[12])
                    seed = int(row[13])
                    nexp += 1
                    log = 2*m*math.log(flow)+1
                    nlog += log
                    if int(row[9]) > math.log:
                        print "Error at %i (%s): number of iterations bigger than maximum allowed" % (int(row[0], filename))  
                
                               
                ndij_avg = float(ndij/nexp)
                nins_avg = float(nins/nexp)
                ndel_avg = float(ndel/nexp)
                nupd_avg = float(nupd/nexp)
                nswp_avg = float(nswp/nexp)
                nitr_avg = float(nitr/nexp)
                nlog_avg = float(nlog/nexp)
                mem_avg  = float(mem/nexp)
                time_avg = float(time/nexp)
                
                comp = (n*math.log10(n)+m)*m*math.log10(flow)
                       
                l = [k, n, m, ndij_avg, nins_avg, ndel_avg, nupd_avg, nswp_avg, nitr_avg, nlog_avg, nitr_avg/nlog_avg, mem_avg, time_avg, time_avg/comp]
            else: #generate tables
                cdata = csv.reader(cfile, delimiter=" ")
                
                k = 0
                n = 0
                m = 0
                dij = 0
                ins = 0
                des = 0
                upd = 0
                swp = 0
                itr = 0
                ilg = 0.0                
                mem = 0
                time = 0.0
                tO = 0.0              
                    
                for row in cdata:
                    n = int(row[0])
                    m = int(row[1])
                    k = int(row[2])
                    dij = float(row[3])
                    ins = float(row[4])
                    des = float(row[5])
                    upd = float(row[6])
                    swp = float(row[7])
                    itr = float(row[8])
                    ilg = float(row[10])
                    mem  = float(row[11])
                    time = float(row[12])
                    tO = float(row[13])
                        
                    lt = [n, m, k, dij, ins, des, upd, swp, itr, ilg, mem, time, tO]
                    l.append(lt)

    return l

def __proc_dir_average__(dirname, outfname, rfext):
    outf = open(outfname, "w")
    
    print("reading files")
    
    lr = [] 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print("Reading file "+file)
        
        lf = __proc_data_file__(dirname+file, "avg")        
        lr.append(lf)
  
    # Generate graph file       
	lr = sorted(lr, key = lambda x: (x[2])) #sort by number of edgess

    for l in lr:
        # n m k dij I D U swp itr log itr/log mem t t/O
        outf.write("%u,%u,%u,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%f,%f,%f,%Le,%Le\n" % (l[1], l[2], l[0], l[3], l[4], l[5], l[6], l[7], l[8], l[9], l[10], float(l[11]/(1024*1024)), l[12], l[13]))
        
    outf.close()


def __proc_dir_table__(dirname, outfname, rfext):
    outf = open(outfname, "w")
    
    print("reading files")
    
    lr = [] 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print("Reading file "+file)
        
        lf = __proc_data_file__(dirname+file, "table")
        for l in lf:        
            lr.append(l)
 
    
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
        __proc_dir_average__(dirname, outfname, rfext)    
    elif exp == 2:
        __proc_dir_table__(dirname, outfname, rfext)
    
   
    

    
    
                
                
