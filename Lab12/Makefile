############################################################
# Lab 12 Assignment Makefile
# by Zeb Hollinger 4/28/21
############################################################

# C compile things
CC     	= gcc
CFLAGS  = -g -Wall -std=c99 -pedantic -O1 -lm

# Valgrindy things
VAL     = valgrind
VFLAGS  = --tool=memcheck --leak-check=yes --track-origins=yes

# C source files 
SOURCE1	= hw12.c

# Program .o files
PROG1   = hw12

# Necessary output files
MEM     = mem.txt
OUT	= out.txt
RAND	= rand.txt


#Keep it from printing program execution
.SILENT:
#-------------------------------------------------------------------------

# should make hw12
#
#
#-------------------------------------------------------------------------
.PHONY: all
all: $(PROG1)

$(PROG1): $(SOURCE1) $(SOURCE2)
	$(CC) $(CFLAGS) -lgsl -lgslcblas $(SOURCE1) -o $(PROG1)
	@echo "Making $(PROG1)"


# should use run all geX.txt files and redirect the output to out.txt
#
#	ge0.txt - ge12.txt
#
#
#-------------------------------------------------------------------------
.PHONY: tests
tests: $(PROG1)
	@echo "Running TESTS"
	@echo "------------------------------------------------------" > $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge0.txt" >> $(OUT)
	-./$(PROG1) -i ge0.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge1.txt" >> $(OUT)
	-./$(PROG1) -i ge1.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge2.txt" >> $(OUT)
	-./$(PROG1) -i ge2.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge3.txt" >> $(OUT)
	-./$(PROG1) -i ge3.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge4.txt" >> $(OUT)
	-./$(PROG1) -i ge4.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge5.txt" >> $(OUT)
	-./$(PROG1) -i ge5.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge6.txt" >> $(OUT)
	-./$(PROG1) -i ge6.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge7.txt" >> $(OUT)
	-./$(PROG1) -i ge7.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge8.txt" >> $(OUT)
	-./$(PROG1) -i ge8.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge9.txt" >> $(OUT)
	-./$(PROG1) -i ge9.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge10.txt" >> $(OUT)
	-./$(PROG1) -i ge10.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge11.txt" >> $(OUT)
	-./$(PROG1) -i ge11.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	@echo " " >> $(OUT)
	@echo "./$(PROG1) -i ge12.txt" >> $(OUT)
	-./$(PROG1) -i ge12.txt >>  $(OUT) 2>&1
	@echo " " >> $(OUT)
	@echo "------------------------------------------------------" >> $(OUT)
	cat $(OUT)



#Should run valgrind
#
#	-send output to mem.txt
#	./hw12 -i rand.txt
#
#
#-------------------------------------------------------------------------
.PHONY: mem
mem: $(PROG1)
	@echo "Running valgrind for $(PROG1)"
	chmod +x genRand
	./genRand > $(RAND)
	$(VAL) $(VFLAGS) ./$(PROG1) -i $(RAND) > $(MEM) 2>&1
	@echo "Finished with memory analysis.."
	@echo "Results are below"
	@echo " "
	cat $(MEM)


#does the normal things
.PHONY: help
help:
	@echo " "
	@echo "-----------------------------------------------------------"
	@echo "all    	- makes hw12"
	@echo "tests	- runs all geX.txt cases and sends output to out.txt"	
	@echo "mem    	- runs valgrind for hw12 with rand.txt and output to mem.txt"
	@echo "help   	- lists possible commands"
	@echo "clean  	- cleans the .o files and .txt files from the working directory"
	@echo "-----------------------------------------------------------"
	@echo " "


#does the normal things
.PHONY: clean
clean:
	@echo "Tidying up the directory!"
	-rm -f *.o $(PROG1)
	-rm -f $(MEM) $(OUT) $(RAND)
