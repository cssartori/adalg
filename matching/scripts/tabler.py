import sys, os, csv, argparse;
import math;
from operator import itemgetter

#Prepare the arguments the program shall receive
def __prepareargs__():
    parser = argparse.ArgumentParser(description='Creates result tables for Fattest Path Max-FLow')
    parser.add_argument('-d', nargs=1, type=str, help='directory with results', required=True)
    parser.add_argument('-o', nargs=1, type=str, help='output file name', required=True)
    parser.add_argument('-x', nargs=1, type=int, help='experiment identifier (<graphics matching files> = 1, <graphics flow files> = 2)', required=True)
    parser.add_argument('-e', nargs=1, type=str, help='result files extension (default = \'.dat\')', required=False, default = ['.dat'])

        
    return parser

#Parse the input arguments and returns a dictionary with them
def __getargs__(parser):
    args = vars(parser.parse_args())
    return args


 
def __proc_data_file__(filename, op):
    l = []
    with open(filename, 'rb') as cfile:
            if op == "avgmat": #generate average file for matching
                cdata = csv.reader(cfile, delimiter=",")

                n = 0
                m = 0
                phases = 0
                ndfsi = 0
                mem = 0
                time = 0.0 
                mat = 0
                max_phases = 0.0
                max_dfsi = 0.0
                nexp = 0
                
                for row in cdata:
                    n = int(row[1])
                    m = int(row[2])
                    phases = int(row[3])
                    ndfsi = int(row[4])
                    mem += int(row[5])
                    time += float(row[6])
                    mat = int(row[7])
                    nexp += 1
                    
                    max_phases = math.sqrt(n)
                    max_dfsi = n+m
                    
                    if max_phases < phases:
                        print "Error at %i (%s): number of phases is bigger than maximum allowed" % (int(row[0]), filename)
                    
                    if max_dfsi < ndfsi:
                        print "Error at %i (%s): number of DFS iterations is bigger than maximum allowed" % (int(row[0]), filename)
                    
                    if mat > n/2:
                        print "Error at %i (%s): matching cardinality is bigger than maximum allowed" % (int(row[0]), filename)
                
                                    
                mem_avg  = float(mem/nexp)
                time_avg = float(time/nexp)
                
                comp = max_phases*max_dfsi
                      
                l = [n, m, phases, max_phases, ndfsi, max_dfsi, comp, mem_avg, time_avg, float(phases/max_phases), float(float(ndfsi)/float(max_dfsi)), float((phases*ndfsi)/comp), time_avg/comp, mat]
            else: #generate average file for flow
                cdata = csv.reader(cfile, delimiter=",")

                n = 0
                m = 0
                mem = 0
                time = 0.0 
                mat = 0
                nexp = 0
                
                for row in cdata:
                    n = int(row[1])
                    m = int(row[2])
                    mem += int(row[5])
                    time += float(row[6])
                    mat = int(row[7])
                    nexp += 1
                    
                    if mat > n/2:
                        print "Error at %i (%s): matching cardinality is bigger than maximum allowed" % (int(row[0]), filename)
                
                                    
                mem_avg  = float(mem/nexp)
                time_avg = float(time/nexp)
                
                comp = n*m
                       
                l = [n, m, 0, 0, 0, 0, comp, mem_avg, time_avg, 0, 0, 0, time_avg/comp, mat]
    return l


def __proc_dir_average__(dirname, op, outfname, rfext):
    outf = open(outfname, "w")
    print("reading files")
    
    lr = [] 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print("Reading file "+file)        
        lf = __proc_data_file__(dirname+file, op)        
        lr.append(lf)
  
    # Generate graph file       
	lr = sorted(lr, key = lambda x: (x[0])) #sort by number of nodes

    for l in lr:
        # n m phases max_phases ndfsi max_dfsi comp mem time phases/max_phases ndfsi/max_dfsi pd/comp time/comp
        outf.write("%u,%u,%u,%.2f,%u,%.2f,%.2f,%.2f,%.2Le,%.2Le,%.2Le,%.2Le,%.2Le,%u\n" % (l[0], l[1], l[2], l[3], l[4], l[5], l[6], l[7]/(1024*1024), l[8], l[9], l[10], l[11], l[12],l[13]))
        
    outf.close()


def __proc_table_file__(dirname, outfname, rfext):
    outf = open(outfname, "w")
    
    lr = [] 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print("Reading file "+dirname+file)
        with open(dirname+file, 'rb') as cfile:
            cdata = csv.reader(cfile, delimiter=",")
            op = 1
            #print "file[1:3] = "+file[1:3]
            if file[1:4] == "mat":
                op = 1
            elif file[1:4] == "flo":
                op = 2
            elif file[1:4] == "fat":
                op = 3
            
            #lf = []
            for row in cdata:
                # op n m phases ndfsi mem time mat
                l = [op, int(row[0]), int(row[1]), int(row[2]), int(row[4]), float(row[7]), float(row[8]), int(row[13])]  
                lr.append(l)    
        
    lr = sorted(lr, key = lambda x: (x[1], x[0])) #sort by number of nodes and type
    
    nn = -1
    c=0
    o=1
    i = 0

    while i < len(lr):
        c += 1
        k = 1          
        outf.write("\n%u & %u & %u & %u & %u & %u & %.2Le & " % (c, lr[i][1], lr[i][2], lr[i][7], lr[i][3], lr[i][4], lr[i][6]))
        
        if i+1 < len(lr) and lr[i+1][0] == o+1:
            outf.write("%.2Le & " % (lr[i+1][6]))
            k += 1
        else:
            outf.write("- & ")
            
        if i+2 < len(lr) and lr[i+2][0] == o+2:
            outf.write("%.2Le \\\\" % (lr[i+2][6]))
            k += 1
        else:
            outf.write("- \\\\")
            
        i += k         
            
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
        __proc_dir_average__(dirname, "avgmat", outfname, rfext)    
    elif exp == 2:
        __proc_dir_average__(dirname, "avgflow", outfname, rfext)
    elif exp == 3:
        __proc_table_file__(dirname, outfname, rfext)
        #__proc_dir_table__(dirname, outfname, rfext)
    
   
    

    
    
                
                
