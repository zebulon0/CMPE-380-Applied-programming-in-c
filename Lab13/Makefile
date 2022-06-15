############################################################
# Lab 13 Assignment Makefile
# by Zeb Hollinger 5/3/21
############################################################

# C compile things
CC     	= gcc
CFLAGS  = -g -O0 -std=c99 -lpthread -Wall -pedantic

# Valgrindy things
VAL     = valgrind
VFLAGS  = --tool=memcheck --leak-check=yes --track-origins=yes

# C source files 
SOURCE1	= hw13.c

# Program .o files
PROG1   = hw13

# Necessary output files
MEM     = mem.txt
OUT	= out.txt


#Keep it from printing program execution
.SILENT:


# should make hw13
#
#
#-------------------------------------------------------------------------
.PHONY: all
all: $(PROG1)

$(PROG1): $(SOURCE1) $(SOURCE2)
	$(CC) $(CFLAGS) $(SOURCE1) -o $(PROG1)
	@echo "Making $(PROG1)"


# should use run all hw13 test cases and redirect the output to out.txt
#
#	./hw13 -t 1 -s -v
#	./hw13 -t 5 -s
#	./hw13 -t 8 -v **this case in results.txt was ran with status=1
#	./hw13 -t 0
#	./hw13 -t 9
#	***extra 8 thread test added to match results.txt
#
#-------------------------------------------------------------------------
.PHONY: tests
tests: $(PROG1)
	@echo "Running TESTS"
	@echo "------------------------------------------------------" > $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -t 1 -s -v"  >> $(OUT)
	./$(PROG1) -t 1 -s -v >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -t 5 -s"  >> $(OUT)
	./$(PROG1) -t 5 -s >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -t 8 -v"  >> $(OUT)
	./$(PROG1) -t 8 -v >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -t 8 -v -s **to match the results.txt"  >> $(OUT)
	./$(PROG1) -t 8 -v -s >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -t 0"  >> $(OUT)
	-./$(PROG1) -t 0 >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -t 9"  >> $(OUT)
	-./$(PROG1) -t 9 >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	cat $(OUT)



#Should run valgrind
#
#	-send output to mem.txt
#	./hw13 -f -t 8 -v
#
#-------------------------------------------------------------------------
.PHONY: mem
mem: $(PROG1)
	@echo "Running valgrind for $(PROG1)"
	-$(VAL) $(VFLAGS) ./$(PROG1) -f -t 8 -v > $(MEM) 2>&1
	@echo "Finished with memory analysis.."
	@echo "Results are below"
	@echo " "
	cat $(MEM)


#does the normal things
.PHONY: help
help:
	@echo " "
	@echo "-----------------------------------------------------------"
	@echo "all    	- makes hw13"
	@echo "tests	- runs all test cases and sends output to out.txt"	
	@echo "mem    	- runs valgrind for hw13 and sends output to mem.txt"
	@echo "help   	- lists possible commands"
	@echo "clean  	- cleans the .o files and .txt files from the working directory"
	@echo "-----------------------------------------------------------"
	@echo " "


#does the normal things
.PHONY: clean
clean:
	@echo "Tidying up the directory!"
	-rm -f *.o $(PROG1)
	-rm -f $(MEM) $(OUT)
