
CC = g++

CFLAGS = -Wall -O3 -std=c++11

INCLUDES = -I include/
SRCDIR = src/

LIBS = -lm

# define the C++ source files
SMAIN = $(SRCDIR)main.cpp $(SRCDIR)ffgraph.cpp
STEST = $(SRCDIR)tester.cpp
#SEXP = $(SRCDIR)exp.cpp  $(SRCDIR)nheap.cpp $(SRCDIR)dgraph.cpp

OMAIN = $(SMAIN:.cpp=.o)
OTEST = $(STEST:.cpp=.o)
#OEXP = $(SEXP:.cpp=.o)

# define the executable file 
MAIN = fat
TEST = tester
#EXP = exp


.PHONY: depend clean

all:    $(MAIN) $(TEST)
	@echo  Fattest and Tester compiled

#$(OBJS) 
$(MAIN): $(OMAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OMAIN) $(LIBS)
	
#$(EXP): $(OEXP)
#	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXP) $(OEXP) $(LIBS)

$(TEST): $(OTEST)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST) $(OTEST) $(LIBS)
	
.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(SRCDIR)*.o
	$(RM) *.bak 

depend: $(SMAIN)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
