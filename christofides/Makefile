
CC = g++

CFLAGS = -Wall -O3 -std=c++11

INCLUDES = -I include/
SRCDIR = src/
BLOSSRC = blossomv/
TRISRC = $(BLOSSRC)triangle/

LIBS = -lm -lrt

# define the C++ source files
SMAIN = $(SRCDIR)main.cpp $(SRCDIR)chrisgraph.cpp 

#$(BLOSSRC)PMinterface.cpp $(BLOSSRC)PMmain.cpp $(BLOSSRC)PMinit.cpp $(BLOSSRC)PMexpand.cpp $(BLOSSRC)PMshrink.cpp $(BLOSSRC)PMduals.cpp $(BLOSSRC)PMrepair.cpp $(BLOSSRC)misc.cpp $(BLOSSRC)MinCost/MinCost.cpp $(BLOSSRC)GEOM/GPMmain.cpp $(BLOSSRC)GEOM/GPMinterface.cpp $(BLOSSRC)GEOM/GPMinit.cpp $(BLOSSRC)GEOM/GPMkdtree.cpp 
SEXP =  $(SRCDIR)exp.cpp $(SRCDIR)chrisgraph.cpp 

#$(BLOSSRC)PMinterface.cpp $(BLOSSRC)PMmain.cpp $(BLOSSRC)PMinit.cpp $(BLOSSRC)PMexpand.cpp $(BLOSSRC)PMshrink.cpp $(BLOSSRC)PMduals.cpp $(BLOSSRC)PMrepair.cpp $(BLOSSRC)misc.cpp $(BLOSSRC)MinCost/MinCost.cpp $(BLOSSRC)GEOM/GPMmain.cpp $(BLOSSRC)GEOM/GPMinterface.cpp $(BLOSSRC)GEOM/GPMinit.cpp $(BLOSSRC)GEOM/GPMkdtree.cpp
#SGEN = $(SRCDIR)gen.cpp
#STST = $(SRCDIR)tester.cpp

OMAIN = $(SMAIN:.cpp=.o) $(BLOSSRC)PMinterface.o $(BLOSSRC)PMmain.o $(BLOSSRC)PMinit.o $(BLOSSRC)PMexpand.o $(BLOSSRC)PMshrink.o $(BLOSSRC)PMduals.o $(BLOSSRC)PMrepair.o $(BLOSSRC)misc.o $(BLOSSRC)MinCost/MinCost.o $(BLOSSRC)GEOM/GPMmain.o $(BLOSSRC)GEOM/GPMinterface.o $(BLOSSRC)GEOM/GPMinit.o $(BLOSSRC)GEOM/GPMkdtree.o
OEXP = $(SEXP:.cpp=.o) $(BLOSSRC)PMinterface.o $(BLOSSRC)PMmain.o $(BLOSSRC)PMinit.o $(BLOSSRC)PMexpand.o $(BLOSSRC)PMshrink.o $(BLOSSRC)PMduals.o $(BLOSSRC)PMrepair.o $(BLOSSRC)misc.o $(BLOSSRC)MinCost/MinCost.o $(BLOSSRC)GEOM/GPMmain.o $(BLOSSRC)GEOM/GPMinterface.o $(BLOSSRC)GEOM/GPMinit.o $(BLOSSRC)GEOM/GPMkdtree.o

# define the executable file 
MAIN = main
EXP = exp

.PHONY: depend clean

all:    $(MAIN) $(EXP)
	@echo  main and exp compiled

#$(OBJS) 
$(MAIN):lib-blossom $(OMAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OMAIN) $(LIBS)

$(EXP):lib-blossom $(OEXP)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXP) $(OEXP) $(LIBS)

lib-blossom:
	cd $(BLOSSRC) && make
	
#lib-tri:
#	cd $(TRISRC) && make trilibrary
	
.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(SRCDIR)*.o $(BLOSSRC)*.o $(BLOSSRC)MinCost/*.o $(BLOSSRC)GEOM/*.o $(BLOSSRC)triangle/*.o 
	$(RM) *.bak 

depend: $(SMAIN)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
