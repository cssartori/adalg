
CC = g++

CFLAGS = -Wall -O3 -std=c++11

INCLUDES = -I include/
SRCDIR = src/
BLOSSRC = blossomv/

LIBS = -lm -lrt

# define the C++ source files
SMAIN = $(SRCDIR)main.cpp $(SRCDIR)chrisgraph.cpp $(BLOSSRC)PMinterface.cpp $(BLOSSRC)PMmain.cpp $(BLOSSRC)PMinit.cpp $(BLOSSRC)PMexpand.cpp $(BLOSSRC)PMshrink.cpp $(BLOSSRC)PMduals.cpp $(BLOSSRC)PMrepair.cpp $(BLOSSRC)misc.cpp $(BLOSSRC)MinCost/MinCost.cpp $(BLOSSRC)GEOM/GPMmain.cpp $(BLOSSRC)GEOM/GPMinterface.cpp $(BLOSSRC)GEOM/GPMinit.cpp $(BLOSSRC)GEOM/GPMkdtree.cpp 
SEXP =  $(SRCDIR)exp.cpp $(SRCDIR)chrisgraph.cpp $(BLOSSRC)PMinterface.cpp $(BLOSSRC)PMmain.cpp $(BLOSSRC)PMinit.cpp $(BLOSSRC)PMexpand.cpp $(BLOSSRC)PMshrink.cpp $(BLOSSRC)PMduals.cpp $(BLOSSRC)PMrepair.cpp $(BLOSSRC)misc.cpp $(BLOSSRC)MinCost/MinCost.cpp $(BLOSSRC)GEOM/GPMmain.cpp $(BLOSSRC)GEOM/GPMinterface.cpp $(BLOSSRC)GEOM/GPMinit.cpp $(BLOSSRC)GEOM/GPMkdtree.cpp
#SGEN = $(SRCDIR)gen.cpp
#STST = $(SRCDIR)tester.cpp

OMAIN = $(SMAIN:.cpp=.o)
OEXP = $(SEXP:.cpp=.o)
OGEN = $(SGEN:.cpp=.o)
OTST = $(STST:.cpp=.o)

# define the executable file 
MAIN = main
EXP = exp
GEN = gen
TEST = tester

.PHONY: depend clean

all:    $(MAIN) $(EXP)
	@echo  main and exp compiled

#$(OBJS) 
$(MAIN): $(OMAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OMAIN) $(LIBS)
	
$(EXP): $(OEXP)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXP) $(OEXP) $(LIBS)

#$(GEN): $(OGEN)
#	$(CC) $(CFLAGS) $(INCLUDES) -o $(GEN) $(OGEN) $(LIBS)

#$(TEST): $(OTST)
#	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST) $(OTST) $(LIBS)
	
.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(SRCDIR)*.o $(BLOSSRC)*.o $(BLOSSRC)MinCost/*.o $(BLOSSRC)GEOM/*.o $(BLOSSRC)triangle/*.o 
	$(RM) *.bak 

depend: $(SMAIN)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
