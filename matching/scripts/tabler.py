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
                      
                l = [n, m, phases, max_phases, ndfsi, max_dfsi, comp, mem_avg, time_avg, float(phases/max_phases), float(float(ndfsi)/float(max_dfsi)), float((phases*ndfsi)/comp), time_avg/comp]
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
                       
                l = [n, m, 0, 0, 0, 0, comp, mem_avg, time_avg, 0, 0, 0, time_avg/comp]
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
        outf.write("%u,%u,%u,%.2f,%u,%.2f,%.2f,%.2f,%.2Le,%.2Le,%.2Le,%.2Le,%.2Le\n" % (l[0], l[1], l[2], l[3], l[4], l[5], l[6], l[7]/(1024*1024), l[8], l[9], l[10], l[11], l[12]))
        
    outf.close()


#def __proc_dir_table__(dirname, outfname, rfext, exp=2):
#    outf = open(outfname, "w")
#    
#    print("reading files")
#    
#    lr = [] 
#    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
#        print("Reading file "+file)
#        lf = __proc_data_file__(dirname+file, "table")
#        C = 0
#        if exp == 2:
#            ind = file.find("k")
#            if ind > 0:
#                ind += 1
#                str = ""
#                while file[ind] != '.':
#                    str += file[ind]
#                    ind += 1
#            
#                C = int(str)
#            
#        for l in lf:    
#            l.append(C)    
#            lr.append(l)
# 
#    
#    #print ("vr = " % (vr))
#    # Generate table file       
#    lr = sorted(lr, key = lambda x: (x[1], x[-1])) #sort by number of edges and capacity
#	
#    avg = dict({})
#    for l in lr:
#        # iter time flow
#        avg[l[-1]] = [0.0,0.0,0.0]
#    
#    nn = -1
#    c=0
#    mavg = 0
#    navg = 0
#    memavg = 0
#   
#    for l in lr:
#        if nn != l[1]:
#            if nn != -1:
#                outf.write("\\\\")
#            c += 1
#            navg += l[0]
#            mavg += l[1]
#            memavg += l[10]
#                      
#            outf.write("\n%u & %u & %u & %.2f" % (c, l[0], l[1], l[10]))            
#            nn = l[1]
#        
#        outf.write(" & %u & %.2Le & %u" % (l[8], l[11], l[13]))            
#            
#        avg[l[-1]][0] += l[8]
#        avg[l[-1]][1] += l[11]
#        avg[l[-1]][2] += l[13]
#        
#        
#        
#    outf.write("\\\\\n\\textbf{Media} & %.2f & %.2f & %.2f" % (navg/c, mavg/c, memavg/c))
#    
#    for a in sorted(avg.iterkeys()):
#        outf.write(" & %.2f & %.2Le & %.2f" % (avg[a][0]/c, avg[a][1]/c, avg[a][2]/c))


#    outf.write("\\\\")
#    outf.close()
    


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
        #__proc_dir_table__(dirname, outfname, rfext)
    
   
    

    
    
                
                
