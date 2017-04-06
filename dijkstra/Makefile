
CC = g++

CFLAGS = -Wall -O3 -std=c++11 

INCLUDES = -I ./
SRCDIR = ./

LIBS = -lm

# define the C++ source files
SMAIN = $(SRCDIR)main.cpp $(SRCDIR)nheap.cpp $(SRCDIR)dgraph.cpp
SEXP = $(SRCDIR)exp.cpp  $(SRCDIR)nheap.cpp
SGEN = $(SRCDIR)gen.cpp

OMAIN = $(SMAIN:.cpp=.o)
OEXP = $(SEXP:.cpp=.o)
OGEN = $(SGEN:.cpp=.o)

# define the executable file 
MAIN = main
EXP = exp
GEN = gen


.PHONY: depend clean

all:    $(MAIN) $(EXP) $(GEN)
	@echo  Main, Exp and Gen compiled

#$(OBJS) 
$(MAIN): $(OMAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OMAIN) $(LIBS)
	
$(EXP): $(OEXP)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXP) $(OEXP) $(LIBS)

$(GEN): $(OGEN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(GEN) $(OGEN) $(LIBS)
	
.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(MAIN) $(EXP) $(GEN) 
	$(RM) *.bak 

depend: $(SMAIN)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
