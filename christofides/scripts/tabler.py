import sys, os, csv, argparse;
import math;
from operator import itemgetter

#Prepare the arguments the program shall receive
def __prepareargs__():
    parser = argparse.ArgumentParser(description='Creates result tables for Fattest Path Max-FLow')
    parser.add_argument('-d', nargs=1, type=str, help='directory with results', required=True)
    parser.add_argument('-o', nargs=1, type=str, help='output file name', required=True)
    parser.add_argument('-x', nargs=1, type=int, help='experiment identifier (<graphics approx. files> = 1, <tables approx.> = 2)', required=True)
    parser.add_argument('-e', nargs=1, type=str, help='result files extension (default = \'.dat\')', required=False, default = ['.dat'])

        
    return parser

#Parse the input arguments and returns a dictionary with them
def __getargs__(parser):
    args = vars(parser.parse_args())
    return args

 
def __proc_data_file__(filename):
    l = []
    with open(filename, 'rb') as cfile:
        cdata = csv.reader(cfile, delimiter=",")

        n = 0
        name = ""
        opmat = 0
        value = 0
        bkv = 0
        dev = 0.0
        time = 0.0 
        nexp = 0
                
        for row in cdata:
            name = row[0]
            opmat = int(row[2])
            n = int(row[3])
            time += float(row[4])
            value = int(row[5])
            bkv = int(row[6])
            dev = int(row[7])
            nexp += 1
                                        
            if dev > 0.5:
                print "Warning: deviation > 0.5 in instance %s" % (row[0])               
                                    
            time_avg = float(time/nexp)
                                      
            l = [name, opmat, n, time_avg, value, bkv, dev]
 
    return l


def __proc_dir_average__(dirname, outfname, rfext):
    outf = open(outfname, "w")
    print("reading files")
    
    lr = [] 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print("Reading file "+file)        
        lf = __proc_data_file__(dirname+file)        
        lr.append(lf)
  
    # Generate graph file       
	lr = sorted(lr, key = lambda x: (x[1])) #sort by number of nodes

    for l in lr:
        # name opmat n time value bkv dev
        outf.write("%s,%u,%u,%.2Le,%u,%u,%.5f\n" % (l[0], l[1], l[2], l[3], l[4], l[5], l[6]))
        
    outf.close()


def __proc_table_file__(dirname, outfname, rfext):
    outf = open(outfname, "w")
    
    lr = [] 
    for file in [f for f in os.listdir(dirname) if f.endswith(rfext)]:
        print("Reading file "+dirname+file)
        with open(dirname+file, 'rb') as cfile:
            cdata = csv.reader(cfile, delimiter=",")            

            for row in cdata:
                # name optmat n time value bkv dev
                l = [row[0], int(row[1]), int(row[2]), float(row[3]), int(row[4]), int(row[5]), float(row[6])]  
                lr.append(l)    
        
    lr = sorted(lr, key = lambda x: (x[2], x[1])) #sort by number of nodes and algorithm
    
    c = 0
    avn = 0
    avv = 0
    bavv = 0
    bavd = 0.0
    bavt = 0.0
    gavv = 0
    gavd = 0.0
    gavt = 0.0
    i = 0
    
    while i < len(lr):
        c += 1
        k = 1
        #id name bkv          
        outf.write("\n%u & %s & %u & %u & " % (c, lr[i][0], lr[i][2], lr[i][5]))
        avn += lr[i][2]
        avv += lr[i][5]
        
        #print Blossom complete
        outf.write("%u & %.2f & %.2Le & " % (lr[i][4], lr[i][6], lr[i][3]))
        bavv += lr[i][4]
        bavd += lr[i][6]
        bavt += lr[i][3]        
        
        if(lr[i][1] == 2):
            #print Blossom solve
            i+=1
            outf.write("%u & %.2f & %.2Le & " % (lr[i][4], lr[i][6], lr[i][3]))
            gavv += lr[i][4]
            gavd += lr[i][6]
            gavt += lr[i][3]    
        else:
            outf.write(" - & - & - & " % (lr[i][4], lr[i][6], lr[i][3]))
            
        #print Greedy
        i+=1
        outf.write("%u & %.2f & %.2Le \\\\" % (lr[i][4], lr[i][6], lr[i][3]))
        gavv += lr[i][4]
        gavd += lr[i][6]
        gavt += lr[i][3]
            
        i += 2
            
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
        __proc_table_file__(dirname, outfname, rfext)
    
    
                
                
