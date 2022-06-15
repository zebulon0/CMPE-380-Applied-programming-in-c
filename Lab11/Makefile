############################################################
# Lab 11 Assignment Makefile
# by Zeb Hollinger 4/23/21
############################################################

# C compile things
CC     	= gcc
CFLAGS  = -g -Wall -std=c99 -pedantic -O1 -lm

# Valgrindy things
VAL     = valgrind
VFLAGS  = --tool=memcheck --leak-check=yes --track-origins=yes

# C source files 
SOURCE1	= hw11.c
SOURCE2 = DynamicArrays.c
SOURCE3 = correction.c

# Program .o files
PROG1   = hw11
PROG2   = correction

# Necessary output files
MEM     = mem.txt
DATA	= data.txt
ALLDATA = alldata.txt
REAL	= realdevice.txt
CORRECT = correction.txt

IMG	= correction.png




#Keep it from printing program execution
.SILENT:
#-------------------------------------------------------------------------

# should make hw11 and correction
#
#
#-------------------------------------------------------------------------
.PHONY: all
all: $(PROG1) $(PROG2)

$(PROG1): $(SOURCE1) $(SOURCE2)
	$(CC) $(CFLAGS) -DHW8 -lgsl -lgslcblas $(SOURCE1) $(SOURCE2) -o $(PROG1)
	@echo "Making $(PROG1)"
	./realDevice | ./diffVal > $(DATA)

$(PROG2): $(SOURCE3)
	$(CC) $(CFLAGS) $(SOURCE3) -o $(PROG2)
	@echo "Making $(PROG2)"


# should use pipes to calculate the error from realDevice using detError
#
#	./realDevice | ./detError
#
#
#-------------------------------------------------------------------------
.PHONY: base
base: 
	@echo "Running BASE"
	@echo "------------------------------------------------------"
	./realDevice | ./detError
	@echo " "


# should use pipes to calculate the error from correction using detError
#
#	./realDevice | ./correction | ./detError
#
#-------------------------------------------------------------------------
.PHONY: correct
correct: $(PROG2)
	@echo "Running CORRECT"
	@echo "------------------------------------------------------"
	./realDevice | ./$(PROG2) | ./detError
	@echo " "


# Creates a pretty picture of the original, corrected, and ideal lines 
# on a graph 
#
#	1) redirect output of realDevice into $(REAL)
#	./realDevice > $(REAL)
#
#	2) redirect corrected data into $(CORRECT)
#	./realDevice | ./correction > $(CORRECT)
#
#	3) paste combined files into alldata.txt
#	paste $(REAL) $(CORRECT) > $(ALLDATA)
#
#	4) create correction.png
#
#
#-------------------------------------------------------------------------
.PHONY: plot
plot: $(PROG2)
	@echo "Running PLOT"
	@echo "------------------------------------------------------"
	./realDevice > $(REAL)
	./realDevice | ./correction > $(CORRECT)
	paste $(REAL) $(CORRECT) > $(ALLDATA)
	./myplot -in $(ALLDATA) -out $(IMG)
	@echo " "


#Should run valgrind
#
#	-send output to mem.txt
#	./hw11 -order 3 -p data.txt
#
#
#-------------------------------------------------------------------------
.PHONY: mem
mem: $(PROG1)
	@echo "Running valgrind for $(PROG1)"
	$(VAL) $(VFLAGS) ./$(PROG1) -order 3 -p $(DATA) > $(MEM) 2>&1
	@echo "Finished with memory analysis.."
	@echo "Results are below"
	@echo " "
	cat $(MEM)


# should run chmod +x for the given files
#
#-------------------------------------------------------------------------
.PHONY: x
x: 
	@echo "Converting given files into executables"
	chmod +x realDevice
	chmod +x detError
	chmod +x myplot
	chmod +x diffVal
	@echo "Done"
	@echo " "


#does the normal things
.PHONY: help
help:
	@echo " "
	@echo "-----------------------------------------------------------"
	@echo "all    	- makes hw11 and correction"
	@echo "base	- use pipes to calculate the error from realDevice using detError"	
	@echo "correct	- use pipes to calculate the error from correction using detError"
	@echo "plot	- 1) redirect output of realDevice into realdevice.txt"
	@echo "-	  2) redirect 'realDevice | correction' into correction.txt"
	@echo "-	  3) paste the combined files into alldata.txt and create correction.png"
	@echo "mem    	- runs valgrind for hw11 with a order 3 polynomial"
	@echo "x	- should run chmod +x for realDevice, detError, myplot, and diffval"
	@echo "help   	- lists possible commands"
	@echo "clean  	- cleans the .o files and .txt files from the working directory"
	@echo "-----------------------------------------------------------"
	@echo " "


#does the normal things
.PHONY: clean
clean:
	@echo "Tidying up the directory!"
	-rm -f *.o $(PROG1) $(PROG2)
	-rm -f $(MEM) $(DATA) $(ALLDATA) $(REAL) $(CORRECT)
	-rm -f $(IMG)
	ls -l
