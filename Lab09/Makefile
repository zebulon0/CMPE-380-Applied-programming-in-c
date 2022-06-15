############################################################
# Lab 09 Assignment Makefile
# by Zeb Hollinger 4/5/21
############################################################

# C compile things
CC       = gcc
CFLAGS   = -Wall -std=c99 -pedantic -O1 -lm
TIME     = -DEN_TIME

# Valgrindy things
VAL      = valgrind
VFLAGS   = --tool=memcheck --leak-check=yes --track-origins=yes

# C source files 
SOURCE1	 = quadTest.c

# Program .o files
PROG1    = quadTest
PROG2    = quadTest_mem

# Necessary text files
OUT      = out.txt
MEM      = mem.txt

#Keep it from printing program execution
.SILENT:
#-------------------------------------------------------------------------

#Should make quadTest with timing enabled and quadTest_mem with
#timing disabled
#
#	PROG1 = timing enabled
#	PROG2 = timing disabled
#
#-------------------------------------------------------------------------
.PHONY: all
all: $(PROG1) $(PROG2)

$(PROG1): $(SOURCE1)
	$(CC) $(CFLAGS) $(TIME) $(SOURCE1) -o $(PROG1)
	@echo "Making $(PROG1)"

$(PROG2): $(SOURCE1)
	$(CC) $(CFLAGS) $(SOURCE1) -o $(PROG2)
	@echo "Making $(PROG2)"


#Should run all 3 specified test cases, then send all results to out.txt
#
#	./quadTest -a 0 -b 0 -c 1
#	./quadTest -a 1 -b 0
#	./quadTest -a 1 -b 0 -c 1
#
#
#-------------------------------------------------------------------------
.PHONY: test
test: $(PROG1)
	@echo "Running tests..."
	@echo "------Test1: ./quadTest -a 0 -b 0 -c 1" > $(OUT)
	./$(PROG1) -a 0 -b 0 -c 1 >> $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------Test2: ./quadTest -a 1 -b 0" >> $(OUT)
	./$(PROG1) -a 1 -b 0 >> $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------Test1: ./quadTest -a 1 -b 0 -c 1" >> $(OUT)
	./$(PROG1) -a 1 -b 0 -c 1 >> $(OUT) 2>&1
	@echo "Testing complete."
	cat $(OUT)

.PHONY: run
run: $(PROG1)
	@echo "--------------------------------------------"
	@echo "./quadTest -a 1 -b 0 -c 1"
	@echo "--------------------------------------------"
	./$(PROG1) -a 1 -b 0 -c 1




#Should run valgrind for quadTest w/ good data redirecting output to mem.txt
#
#	./quadTest_mem -a 1 -b 0 -c 1
#	./quadTest_mem -a 2 -b 3 -c 4
#	./quadTest_mem -a 3 -b 4 -c 5 
#
#-------------------------------------------------------------------------
.PHONY: mem
mem: $(PROG2)
	@echo "Running 3 tests for valgrind"
	@echo "Test1: ./quadTest_mem -a 1 -b 0 -c 1" > $(MEM)
	$(VAL) $(VFLAGS) ./$(PROG2) -a 1 -b 0 -c 1 >> $(MEM) 2>&1
	@echo " " >> $(MEM)
	@echo "Test2: ./quadTest_mem -a 2 -b 3 -c 4" >> $(MEM)
	$(VAL) $(VFLAGS) ./$(PROG2) -a 2 -b 3 -c 4 >> $(MEM) 2>&1
	@echo " " >> $(MEM)
	@echo "Test3: ./quadTest_mem -a 3 -b 4 -c 5" >> $(MEM)
	$(VAL) $(VFLAGS) ./$(PROG2) -a 3 -b 4 -c 5 >> $(MEM) 2>&1
	@echo "Finihed with memory analysis.."
	@echo "Results are below"
	@echo " "
	cat $(MEM)
		
		


#does the normal things
.PHONY: help
help:
	@echo "all    - makes quadTest and quadTest_mem"
	@echo "test   - runs all tests and redirects output to $(OUT)"
	@echo "mem    - runs valgrind with good data and sends output to $(MEM)"
	@echo "help   - lists possible commands"
	@echo "clean  - cleans the .o files and .txt files from the working directory"


#does the normal things
.PHONY: clean
clean:
	@echo "Tidying up the directory!"
	-rm -f *.o $(PROG1) $(PROG2)
	-rm -f $(OUT) $(MEM) 
