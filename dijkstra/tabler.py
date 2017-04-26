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
            k = int(row[1])
            nswaps = int(row[2])
            time = float(row[4])
            tpe = float(row[5])             
            l = [i, k, nswaps, time, tpe]           
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
        lf = sorted(lf, key = lambda x: (x[0])) #sort by experiment
        gfname = "G"+file.split(".")[0]+".dat"
        outg = open(dirname+gfname, "w")
        for l in lf:
            outg.write("%i %i %i %Le %Le\n" % (l[0], l[1], l[2], l[3], l[4]))
        
        outg.close()
        
        
    # Generate table file       
	lr = sorted(lr, key = lambda x: (x[0], x[1])) #sort by experiment and k
	avg = dict({})
	for l in lr:
	    avg[l[1]] = [0,0.0,0]
	    
	ne = -1
    for l in lr:
        if ne != l[0]:
            if ne != -1:
                 outf.write("\\\\")
            outf.write("\n%i " % (l[0]))
            ne = l[0]
                        
        outf.write(" & %i & %.2Le " % (l[2], l[3]))
        avg[l[1]] = [avg[l[1]][0]+l[2], avg[l[1]][1]+l[3], avg[l[1]][2]+1]

    outf.write("\\\\\n\\textbf{Average} ")
    for a in avg:
        outf.write(" & %.2f & %.2Le " % (float(avg[a][0]/avg[a][2]), avg[a][1]/avg[a][2]))
    
    outf.write("\\\\")
    outf.close()


   
def __proc_file_scale__(filename, op):
    l = []
    with open(filename, 'rb') as cfile:
            if op == "gr":
                cdata = csv.reader(cfile, delimiter=",")
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
                    k = int(row[9])
                    n = int(row[1])
                    m = int(row[2])
                    nins += int(row[3])
                    ndel += int(row[4])
                    nupd += int(row[5])
                    mem  += int(row[6])
                    time += float(row[7])
                    nexp += 1
                    
                    if int(row[4]) > n:
                        print "Error on I row "+str(row[0])
                    if int(row[5]) > n:
                        print "Error on D row "+str(row[0])
                    if int(row[6]) > m:
                        print "Error on U row "+str(row[0])
                               
                nins_avg = float(nins/nexp)
                ndel_avg = float(ndel/nexp)
                nupd_avg = float(nupd/nexp)
                mem_avg  = float(mem/nexp)
                time_avg = float(time/nexp)
                       
                l = [k, n, m, nins_avg, ndel_avg, nupd_avg, mem_avg, time_avg]
            else:
                cdata = csv.reader(cfile, delimiter=" ")

                k = 0
                n = 0
                m = 0
                mem = 0
                time = 0.0              
                    
                for row in cdata:
                    k = int(row[0])
                    n = int(row[2])
                    m = int(row[3])
                    mem  = float(row[10])
                    time = float(row[11])
                        
                    lt = [k, n, m, mem, time]
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
	lr = sorted(lr, key = lambda x: (x[1])) #sort by number of vertices

    for l in lr:
        # k log2(n) n m I D U pI pD pU mem t t/O
        outf.write("%i %u %u %u %u %u %u %f %f %f %f %Le %Le\n" % (l[0], math.log(l[1], 2), l[1], l[2], l[3], l[4], l[5], float(l[3]/l[1]), float(l[4]/l[1]), float(l[5]/l[2]), float(l[6]/(1024*1024)), l[7], l[7]/((l[2]+l[1])*math.log(l[1]))))
        
    outf.close()


def __proc_dir_table_scale__(dirname, outfname, rfext):
    outf = open(outfname, "w")
    
    print("reading files")
    
    lr = [] 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print("Reading file "+file)
        
        lf = __proc_file_scale__(dirname+file, "tb")
        for l in lf:        
            lr.append(l)
    
      
    # Generate table file       
	lr = sorted(lr, key = lambda x: (x[1], x[0])) #sort by number of vertices and k
    avg = dict({})
    for l in lr:
        avg[l[0]] = 0.0
    
    nn = -1
    c=0
    mavg = 0
    navg = 0
    memavg = 0
    
    for l in lr:
        if nn != l[1]:
            if nn != -1:
                outf.write("\\\\")
            c += 1
            navg += l[1]
            mavg += l[2]
            memavg += l[3]
            outf.write("\n%u & %u & %u & %.2f " % (c, l[1], l[2], l[3]))
            #outf.write("\n%u & %u & %u " % (c, l[1], l[2]))
            nn = l[1]
        
        outf.write("& %.2Le " % (l[4]))
        avg[l[0]] += l[4]
        
    outf.write("\\\\\n\\textbf{Average} & %.2f & %.2f & %.2f " % (navg/c, mavg/c, memavg/c))
    #outf.write("\\\\\n\\textbf{Average} & %.2f & %.2f " % (navg/c, mavg/c))
    for a in avg:
        outf.write(" & %.2Le" % (avg[a]/c))
    
    outf.write("\\\\")
    outf.close()
    







def __proc_exp1__(dirname, outfname, rfext):
    
    outf = open(outfname, "w")
    print("reading files") 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        lr = []
        print("Reading file "+file)
        with open(dirname+file, 'rb') as csvfile:
            csvdata = csv.reader(csvfile, delimiter=' ')

            for row in csvdata:
                i = int(row[0])
                nswaps = int(row[1])
                time = float(row[3])
                tpe = float(row[4])  
                
                l = [i, nswaps, time, tpe]           
                lr.append(l)

	
	    lr = sorted(lr, key=itemgetter(0))
	    outf.write("----"+dirname+file+"----\n")    
        for l in lr:
            #outf.write("%i %Le\n" % (l[0], l[3]))
            outf.write("%i & %i & %.2Le\n" % (l[0], l[1], l[2]))
        outf.write("------------------------\n")



def __proc_exp23__(dirname, outfname, rfext):
    lr = []
    outf = open(outfname, "w")
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        with open(dirname+file, 'rb') as csvfile:
            csvdata = csv.reader(csvfile, delimiter=',')
            fl = csvdata.next()
            n = int(fl[1])
            m = int(fl[2])
            nins = int(fl[3])
            ndel = int(fl[4])
            nupd = int(fl[5])
            mem  = int(fl[6])
            time = float(fl[7])
            
            nexp = 1
            for row in csvdata:
                nins += int(row[3])
                ndel += int(row[4])
                nupd += int(row[5])
                mem  += int(row[6])
                time += float(row[7])
                nexp += 1
           
            nins_avg = float(nins/nexp)
            ndel_avg = float(ndel/nexp)
            nupd_avg = float(nupd/nexp)
            mem_avg  = float(mem/nexp)
            time_avg = float(time/nexp)
           
            l = [n, m, nins_avg, ndel_avg, nupd_avg, mem_avg, time_avg]
            lr.append(l)     


    lr = sorted(lr, key=itemgetter(0))    
    outf = open(outfname, "w")
    
    for l in lr:
        outf.write("%i\t%i\t%f\t%f\t%f\t%f\t%Le\n" % (l[0], l[1], l[2], l[3], l[4], (l[5]/(1024*1024)), l[6]))

   
def __proc_exp11__(dirname, outfname, rfext):
    lr = []
    outf = open(outfname, "w")
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print "reading "+file
        with open(dirname+file, 'rb') as csvfile:
            csvdata = csv.reader(csvfile, delimiter=' ')
            fl = csvdata.next()
            k = int(fl[0])
            ns = 0
            e = 0
            t  = 0
            idt = 0
            
            nexp = 1
            for row in csvdata:
                idt = int(row[0])
                ns = int(row[1])
                e = int(row[2])
                t  = float(row[3])
                l = [k, idt, ns, e, t]                
                lr.append(l) 
           
            #print ("appending %i %i %i\n" % (k, n, m))
                

    
    lr = sorted(lr, key = lambda x: (x[1], x[0]))    
    outf = open(outfname, "w")
    nn = -1
    for l in lr:
        if(l[1] != nn):
            nn = l[1]
            outf.write("\n%i & " % (l[1]))
            
        outf.write(" %i & %i & %.2Le &" % (l[3], l[2], l[4]))


def __proc_exp44__(dirname, outfname, rfext):
    lr = []
    outf = open(outfname, "w")
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        with open(dirname+file, 'rb') as csvfile:
            csvdata = csv.reader(csvfile, delimiter='\t')
            fl = csvdata.next()
            k = int(fl[0])
            n = 0
            m = 0
            mem  = 0
            time = 0
            
            nexp = 1
            for row in csvdata:
                n = int(row[0])
                m = int(row[1])
                mem  = float(row[5])
                time = float(row[6])
                l = [k, n, m, mem, time]                
                lr.append(l) 
           
            #print ("appending %i %i %i\n" % (k, n, m))
                

    
    lr = sorted(lr, key = lambda x: (x[1], x[0]))    
    outf = open(outfname, "w")
    nn = 0
    for l in lr:
        if(l[1] != nn):
            nn = l[1]
            outf.write("\n%i & %i &" % (l[1], l[2]))
        outf.write(" %.2Le &" % (l[4]))
   

def __proc_exp55__(dirname, outfname, rfext):

    outf = open(outfname, "w")
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        lr = []
        with open(dirname+file, 'rb') as csvfile:
            csvdata = csv.reader(csvfile, delimiter='\t')
            print "reading "+file+"\n"
            for row in csvdata:
                n = int(row[0])
                m = int(row[1])
                I  = float(row[2])
                D = float(row[3])
                U = float(row[4])
                t = float(row[6])
                
                if I > n:
                    print "Error on I for "+file
                if D > n:
                    print "Error on D for "+file
                if U > m:
                    print "Error on U for "+file
                
                tp = (t/((m*math.log(n))+(n*math.log(n))))
                pI = I/n
                pD = D/n
                pU = U/m
                #print file+"\n"
                #print ("t = %.2Le | tp = %.2Le | (m+n)log(n) = %.2Le | log(%d) = %.2Le\n" % (t, tp, (m*math.log(n))+(n*math.log(n)), n, math.log(n)))
                
                l = [n, m, tp, t, pI, pD, pU]                
                lr.append(l) 
                   
            lr = sorted(lr, key = lambda x: (x[0]))    
            
            outf.write(file+"\n")    
            for l in lr:
                outf.write("%i %i %.2Le %.2Le %.2Le %.2Le %.2Le\n" % (l[0], l[1], l[2], l[3], l[4], l[5], l[6]))

            outf.write("--------------------------------\n")
            
            for l in lr:
                outf.write("%i & %i & %.2Le\n" % (l[0], l[1], l[3]))
                
            outf.write("================================\n")
            




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
    elif exp == 3:
        __proc_dir_table_scale__(dirname, outfname, rfext)
#    elif exp == 5:
#        __proc_exp55__(dirname, outfname, rfext)
#    elif exp == 11:
#        __proc_exp11__(dirname, outfname, rfext)

    
   
    

    
    
                
                
