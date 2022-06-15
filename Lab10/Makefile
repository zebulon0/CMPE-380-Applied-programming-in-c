############################################################
# Lab 10 Assignment Makefile
# by Zeb Hollinger 4/12/21
############################################################

# C compile things
CC     	= gcc
CFLAGS  = -g -Wall -std=c99 -pedantic -O2 -lm
TIME    = -DEN_TIME
VERB	= -DVERBOSE

# Valgrindy things
VAL     = valgrind
VFLAGS  = --tool=memcheck --leak-check=yes --track-origins=yes

# C source files 
SOURCE1	= intTest.c
SOURCE2 = rootfinding.c

# Program .o files
PROG1   = intTest
PROG2   = intTest_mem
PROG3	= intTest_time

# Necessary text files
OUT     = out.txt
MEM     = mem.txt

#Keep it from printing program execution
.SILENT:
#-------------------------------------------------------------------------

#Should make intTest with timing enabled and intTest_mem with
#timing disabled
#
#	PROG1 = timing enabled
#	PROG2 = timing disabled
#
#-------------------------------------------------------------------------
.PHONY: all
all: $(PROG1) $(PROG2) $(PROG3)

$(PROG1): $(SOURCE1)
	$(CC) $(CFLAGS) $(TIME) $(SOURCE1) $(SOURCE2) -o $(PROG1)
	@echo "Making $(PROG1)"

$(PROG2): $(SOURCE1)
	$(CC) $(CFLAGS) $(VERB) $(SOURCE1) $(SOURCE2) -o $(PROG2)
	@echo "Making $(PROG2)"

$(PROG3): $(SOURCE1)
	$(CC) -g -Wall -std=c99 -pedantic -O3 -lm  $(TIME) $(SOURCE1) $(SOURCE2) -o $(PROG3)
	@echo "Making $(PROG3)"

#Should run tests
#
#	-timing enabled
#	-output to out.txt
#
#-------------------------------------------------------------------------
.PHONY: test
test: $(PROG1)
	@echo "Running tests..."
	./$(PROG1) > $(OUT) 2>&1
	@echo "Testing complete."
	cat $(OUT)

#Helps with timing
#
#-------------------------------------------------------------------------
.PHONY: time
time: $(PROG3)
	@echo "Running $(PROG3)"
	@echo " "
	./$(PROG3) 2>&1



#Should run valgrind
#
#	-timing disabled
#	-output to mem.txt
#
#-------------------------------------------------------------------------
.PHONY: mem
mem: $(PROG2)
	@echo "Running valgrind for $(PROG2)"
	$(VAL) $(VFLAGS) ./$(PROG2) > $(MEM) 2>&1
	@echo "Finished with memory analysis.."
	@echo "Results are below"
	@echo " "
	cat $(MEM)
		
		


#does the normal things
.PHONY: help
help:
	@echo "all    - makes intTest and intTest_mem"
	@echo "test   - runs application with timing enabled and redirects output to $(OUT)"
	@echo "mem    - runs valgrind with timing disabled and sends output to $(MEM)"
	@echo "help   - lists possible commands"
	@echo "clean  - cleans the .o files and .txt files from the working directory"


#does the normal things
.PHONY: clean
clean:
	ls
	@echo "Tidying up the directory!"
	-rm -f *.o $(PROG1) $(PROG2) $(PROG3)
	-rm -f $(OUT) $(MEM) 
	ls
