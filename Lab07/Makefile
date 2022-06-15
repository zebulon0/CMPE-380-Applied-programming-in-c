############################################################
# Lab 07 Assignment Makefile
# by Zeb Hollinger 3/23/21
############################################################

# C compile things
CC       = gcc
CFLAGS   = -Wall -std=c99 -pedantic -O1 -lm

# Valgrindy things
VAL      = valgrind
VFLAGS   = --tool=memcheck --leak-check=yes --track-origins=yes

# C source files 
SOURCE1	 = rootfinding.c
SOURCE2  = hw7.c
SOURCE3  = eqn2solve.c

# Object .o files
OBJ1     = $(patsubst %.c,%.o, $(SOURCE1))
OBJ2     = $(patsubst %.c,%.o, $(SOURCE2))
OBJ3     = $(patsubst %.c,%.o, $(SOURCE3))

# Program .o files
PROG     = hw7

# Necessary text files
OUT      = out.txt
MEM      = mem.txt

#Keep it from printing program execution
.SILENT:
#-------------------------------------------------------------------------

#Should make hw7
.PHONY: all
all: $(PROG)

$(PROG): $(OBJ1) $(OBJ2) $(OBJ3)
	$(CC) $(CFLAGS) $(OBJ1) $(OBJ2) $(OBJ3) -o $(PROG)

$(OBJ1): $(SOURCE1)
	$(CC) $(CFLAGS) $(SOURCE1) -c 

$(OBJ2): $(SOURCE2)
	$(CC) $(CFLAGS) $(SOURCE2) -c

$(OBJ3): $(SOURCE3)
	$(CC) $(CFLAGS) $(SOURCE3) -c


#Should run all 5 specified test cases, then send all results to OUT.txt
#
# Bisection: use interval [-2.5, 2.5]
#
# Newton: use 2 different initial guesses -1.5 and 1.5
#
# Secant: use same initial guesses, -1.5 and 1.5 for one point and
#         pick a reasonable second point for both tests 
#-------------------------------------------------------------------------
.PHONY: test
test: $(PROG)
	@echo "Bisection: Test 1 --------------------------------" > $(OUT)
	./$(PROG) -b -t 1E-6 -ga -2.5 -gb 2.5 -v >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Newton: Test 1 ----------------------------------" >> $(OUT)
	./$(PROG) -n -t 1E-6 -ba -1.5 -v >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Newton: Test 2 ----------------------------------" >> $(OUT)
	./$(PROG) -n -t 1E-6 -ba 1.5 -v >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Secant: Test 1 ----------------------------------" >> $(OUT)
	./$(PROG) -s -t 1E-6 -ba -1.5 -bb -1.6 -v >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Secant: Test 2 ----------------------------------" >> $(OUT)
	./$(PROG) -s -t 1E-6 -ba 1.5 -bb 1.6 -v >> $(OUT)
	cat $(OUT)


#Should run 3 bisection tests, then send all results to OUT.txt
#
#	./hw7 -b -tol 1E-6 -ga -2 -gb 3 -verb
#
#	./hw7 -b -t 1E-6 -g -2 -u 3 -v
#
#	./hw7 -b -t 1E-6 -ba -2 -bb 3 -v
#-------------------------------------------------------------------------
.PHONY: opts
opts: $(PROG)
	@echo "Bisection Test 1 --------------------------------" > $(OUT)
	./$(PROG) -b -tol 1E-6 -ga -2 -gb 3 -verb >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Bisection Test 2 --------------------------------" >> $(OUT)
	./$(PROG) -b -t 1E-6 -g -2 -u 3 -v >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Bisection Test 3 --------------------------------" >> $(OUT)
	./$(PROG) -b -t 1E-6 -ba -2 -bb 3 -v >> $(OUT)
	cat $(OUT)


#Should run valgrind for all 3 modes of the hw7 w/ good data redirecting
#
#	bisection [-2.5, 2.5]
#
#	secant [-1.5, -1.6]
#
#	newton [-1.5]
#
#-------------------------------------------------------------------------
.PHONY: mem
mem: $(PROG)
	@echo "Running bisection [-2.5, 2.5]" > $(MEM)
	$(VAL) $(VFLAGS) ./$(PROG) -b -t 1E-6 -ga -2.5 -gb 2.5 -v >> $(MEM) 2>&1
	@echo " "
	@echo "Running secant [-1.5, -1.6]" >> $(MEM)
	$(VAL) $(VFLAGS) ./$(PROG) -s -t 1E-6 -ga -1.5 -gb -1.6 -v >> $(MEM) 2>&1
	@echo " "
	@echo "Running newton [-1.5]" >> $(MEM)
	$(VAL) $(VFLAGS) ./$(PROG) -n -t 1E-6 -ba -1.5 -v >> $(MEM) 2>&1
	cat $(MEM)
	

#does the normal things
.PHONY: help
help:
	@echo "all    - makes hw7"
	@echo "test   - runs all tests and redirects output to $(OUT)"
	@echo "opts   - should run the bisection tests with output sent to $(OUT)"
	@echo "mem    - runs valgrind for all 3 modes with output sent to $(MEM)"
	@echo "help   - lists possible commands"
	@echo "clean  - cleans the .o files and .txt files from the working directory"


#does the normal things
.PHONY: clean
clean:
	@echo "Tidying up the directory!"
	-rm -f *.o $(PROG)
	-rm -f $(OUT) $(MEM) 
