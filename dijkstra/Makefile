
CC = g++

CFLAGS = -Wall -O3 -std=c++11 

INCLUDES = -I ./
SRCDIR = ./

LIBS = -lm

# define the C++ source files
SMAIN = $(SRCDIR)main.cpp $(SRCDIR)nheap.cpp $(SRCDIR)dgraph.cpp
SEXP = $(SRCDIR)exp.cpp  $(SRCDIR)nheap.cpp
SGEN = $(SRCDIR)gen.cpp

# define the executable file 
MAIN = main
EXP = exp
GEN = gen


.PHONY: depend clean

all:    $(MAIN) $(EXP) $(GEN)
	@echo  Main, Exp and Gen compiled

#$(OBJS) 
$(MAIN): 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(SMAIN) $(LIBS)
	
$(EXP): 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXP) $(SEXP) $(LIBS)

$(GEN): 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(GEN) $(SGEN) $(LIBS)
	

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(SRCDIR)*.o 
	$(RM) *.bak 

depend: $(SMAIN)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
