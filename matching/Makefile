
CC = g++

CFLAGS = -Wall -O3 -std=c++11

INCLUDES = -I include/
SRCDIR = src/

LIBS = -lm

# define the C++ source files
SMAIN = $(SRCDIR)matgraph.cpp $(SRCDIR)main.cpp
#SEXP = $(SRCDIR)exp.cpp $(SRCDIR)dgraph.cpp
SGEN = $(SRCDIR)gen.cpp
STST = $(SRCDIR)tester.cpp

OMAIN = $(SMAIN:.cpp=.o)
OEXP = $(SEXP:.cpp=.o)
OGEN = $(SGEN:.cpp=.o)
OTST = $(STST:.cpp=.o)

# define the executable file 
MAIN = mat
#EXP = exp
GEN = gen
TEST = tester

.PHONY: depend clean

all:    $(MAIN) $(GEN) $(TEST)
	@echo  Mat, Gen and Tester compiled

#$(OBJS) 
$(MAIN): $(OMAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OMAIN) $(LIBS)
	
#$(EXP): $(OEXP)
#	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXP) $(OEXP) $(LIBS)

$(GEN): $(OGEN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(GEN) $(OGEN) $(LIBS)

$(TEST): $(OTST)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST) $(OTST) $(LIBS)
.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(SRCDIR)*.o
	$(RM) *.bak 

depend: $(SMAIN)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
