############################################################
# Lab 06 Assignment Makefile
# by Zeb Hollinger 3/19/21
############################################################

# C compile things
CC       = gcc
CFLAGS   = -Wall -std=c99 -pedantic -O1 -DEN_TIME
CXFLAGS  = -Wall -std=c99 -pedantic -O1 -DEN_TIME -DMOVE_FOPEN

# C++ compile things
CPP	 = g++
CPPFLAGS = -Wall -pedantic -std=c++98 -O1 -DEN_TIME

# C source files 
CSOURCE  = $(SOURCE1) $(SOURCE2)
SOURCE1	 = hw6c.c        # C code
SOURCE2  = hw6c_2.c      # C code with 2X the loop count of 1

# C++ source files
CPPSOURCE= $(SOURCE3) $(SOURCE4)
SOURCE3  = hw6cpp.cpp    # CPP code
SOURCE4  = hw6cpp_2.cpp  # CPP code with 2X the loop count of 3

#Program .o files
PROG     = $(PROGCNO) $(PROGCYES) $(PROGCPP)
PROGCNO  = $(PROG1) $(PROG2)
PROGCYES = $(PROG3) $(PROG4)
PROGCPP  = $(PROG5) $(PROG6)

PROG1    = hw6c_1# C code
PROG2    = hw6c_2# C code with 2x the loop count
PROG3    = hw6c_f1# C code with MOVE_FOPEN option
PROG4    = hw6c_f2# C code with 2x the loop count AND MOVE_FOPEN option
PROG5    = hw6cpp_1# CPP code
PROG6    = hw6cpp_2# CPP code with 2x the loop count

# Necessary text files
OUT      = out.txt
FILE     = data.txt

#Keep it from printing program execution
.SILENT:

#Should build all your timing enabled code (hw6c & hw6_cpp)
.PHONY: all
all: $(PROG)

.PHONY: $(PROG1)
$(PROG1): $(SOURCE1)
	@echo "Compiling $?"
	$(CC) $(CFLAGS) $(SOURCE1) -o $(PROG1)

.PHONY: $(PROG2)
$(PROG2): $(SOURCE2)
	@echo "Compiling $?"
	$(CC) $(CFLAGS) $(SOURCE2) -o $(PROG2)

.PHONY: $(PROG3)
$(PROG3): $(SOURCE1)
	@echo "Compiling $?"
	$(CC) $(CXFLAGS) $(SOURCE1) -o $(PROG3)

.PHONY: $(PROG4)
$(PROG4): $(SOURCE2)
	@echo "Compiling $?"
	$(CC) $(CXFLAGS) $(SOURCE2) -o $(PROG4)

.PHONY: $(PROG5)
$(PROG5): $(SOURCE3)
	@echo "Compiling $?"
	$(CPP) $(CPPFLAGS) $(SOURCE3) -o $(PROG5)

.PHONY: $(PROG6)
$(PROG6): $(SOURCE4)
	@echo "Compiling $?"
	$(CPP) $(CPPFLAGS) $(SOURCE4) -o $(PROG6)


#Should run hw6c and hw6cpp, each. Redirect all output to out.txt
#
#A line of the execution command that is being ran should be included
#in out.txt prior to the execution run
.PHONY: test
test: $(PROG)
	@echo "-------------- $(PROG1) X1, no move fopen" >> $(OUT)
	./$(PROG1) $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "-------------- $(PROG2) X2, no move fopen" >> $(OUT)
	./$(PROG2) $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "-------------- $(PROG3) X1, yes move fopen" >> $(OUT)
	./$(PROG3) $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "-------------- $(PROG4) X1, yes move fopen" >> $(OUT)
	./$(PROG4) $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "-------------- $(PROG5) X1" >> $(OUT)
	./$(PROG5) $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "-------------- $(PROG6) X1" >> $(OUT)
	./$(PROG6) $(FILE) >> $(OUT)
	@echo " " >> $(OUT)

#does the normal things
.PHONY: help
help:
	@echo "all   - builds timing enabled code"
	@echo "test  - runs  tests and redirects output to $(OUT)"
	@echo "help  - lists possible commands"
	@echo "clean - cleans the .o files and .txt files from the working directory"

#does the normal things
.PHONY: clean
clean:
	@echo "Tidying up the directory!"
	-rm -f *.o $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5) $(PROG6)
	-rm -f $(OUT)
