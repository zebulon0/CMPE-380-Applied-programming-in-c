############################################################
# Lab 08 Assignment Makefile
# by Zeb Hollinger 3/31/21
############################################################

# C compile things
CC       = gcc
CFLAGS   = -Wall -std=c99 -pedantic -g -DMOVE_IO_CLOSE
TIME     = -DEN_TIME

# Valgrindy things
VAL      = valgrind
VFLAGS   = --tool=memcheck --leak-check=yes --track-origins=yes

# C source files 
SOURCE1	 = hw8c.c
SOURCE2  = hw8c_opt1.c
SOURCE3  = hw8c_opt2.c
SOURCE4  = hw8c_opt3.c

# Object .o files
OBJ1     = hw8c
OBJ2     = hw8c_opt1
OBJ3     = hw8c_opt2
OBJ4     = hw8c_opt3

# Necessary text files
OUT      = out.txt
MEM      = mem.txt
FILE     = data.txt

#Keep it from printing program execution
.SILENT:
#-------------------------------------------------------------------------

#Should make all of the object files
.PHONY: all
all: $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)

#-------------------------------------------
#
# Builds the base code for all optimizations
#
$(OBJ1): $(SOURCE1)
	@echo "Building $(SOURCE1) for all configurations"
	$(CC) $(CFLAGS) $(TIME) -O0 $(SOURCE1) -o $(OBJ1)_0
	$(CC) $(CFLAGS) $(TIME) -O1 $(SOURCE1) -o $(OBJ1)
	$(CC) $(CFLAGS) $(TIME) -O2 $(SOURCE1) -o $(OBJ1)_2
	$(CC) $(CFLAGS) $(TIME) -O3 $(SOURCE1) -o $(OBJ1)_3
	$(CC) $(CFLAGS) -O1 $(SOURCE1) -o $(OBJ1)_mem
 

#-------------------------------------------
#
# Builds the x2 memory growth and realloc to
# the base code for all optimizations
#
$(OBJ2): $(SOURCE2)
	@echo "Building $(SOURCE2) for all configurations"
	$(CC) $(CFLAGS) $(TIME) -O0 $(SOURCE2) -o $(OBJ2)_0
	$(CC) $(CFLAGS) $(TIME) -O1 $(SOURCE2) -o $(OBJ2)
	$(CC) $(CFLAGS) $(TIME) -O2 $(SOURCE2) -o $(OBJ2)_2
	$(CC) $(CFLAGS) $(TIME) -O3 $(SOURCE2) -o $(OBJ2)_3
	$(CC) $(CFLAGS) -O1 $(SOURCE2) -o $(OBJ2)_mem


#-------------------------------------------
#
# Builds the native loop unrolling code for 
# all optimizations
#
$(OBJ3): $(SOURCE3)
	@echo "Building $(SOURCE3) for all configurations"
	$(CC) $(CFLAGS) $(TIME) -O0 $(SOURCE3) -o $(OBJ3)_0
	$(CC) $(CFLAGS) $(TIME) -O1 $(SOURCE3) -o $(OBJ3)
	$(CC) $(CFLAGS) $(TIME) -O2 $(SOURCE3) -o $(OBJ3)_2
	$(CC) $(CFLAGS) $(TIME) -O3 $(SOURCE3) -o $(OBJ3)_3
	$(CC) $(CFLAGS) -O1 $(SOURCE3) -o $(OBJ3)_mem


#-------------------------------------------
#
# Builds the smarter loop unrolling code for
# all optimizations
#
$(OBJ4): $(SOURCE4)
	@echo "Building $(SOURCE4) for all configurations"
	$(CC) $(CFLAGS) $(TIME) -O0 $(SOURCE4) -o $(OBJ4)_0
	$(CC) $(CFLAGS) $(TIME) -O1 $(SOURCE4) -o $(OBJ4)
	$(CC) $(CFLAGS) $(TIME) -O2 $(SOURCE4) -o $(OBJ4)_2
	$(CC) $(CFLAGS) $(TIME) -O3 $(SOURCE4) -o $(OBJ4)_3
	$(CC) $(CFLAGS) -O1 $(SOURCE4) -o $(OBJ4)_mem


# Should run each performance test target with data.txt and redirect
# all output to out.txt. A line indicating which commmand is being
# executed must be included before the actual execution of that command
#
#-------------------------------------------------------------------------
.PHONY: test
test: $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)
	@echo "Running tests for all hw8c files at every optimization"
	@echo "Testing $(OBJ1)_0:" > $(OUT)
	./$(OBJ1)_0 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ1):" >> $(OUT)
	./$(OBJ1) $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ1)_2:" >> $(OUT)
	./$(OBJ1)_2 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ1)_3:" >> $(OUT)
	./$(OBJ1)_3 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ2)_0:" >> $(OUT)
	./$(OBJ2)_0 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ2):" >> $(OUT)
	./$(OBJ2) $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ2)_2:" >> $(OUT)
	./$(OBJ2)_2 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ2)_3:" >> $(OUT)
	./$(OBJ2)_3 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ3)_0:" >> $(OUT)
	./$(OBJ3)_0 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ3):" >> $(OUT)
	./$(OBJ3) $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ3)_2:" >> $(OUT)
	./$(OBJ3)_2 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ3)_3:" >> $(OUT)
	./$(OBJ3)_3 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ4)_0:" >> $(OUT)
	./$(OBJ4)_0 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ4):" >> $(OUT)
	./$(OBJ4) $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ4)_2:" >> $(OUT)
	./$(OBJ4)_2 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	@echo "Testing $(OBJ4)_3:" >> $(OUT)
	./$(OBJ4)_3 $(FILE) >> $(OUT)
	@echo " " >> $(OUT)
	cat $(OUT)


# Should run valgrind for each C file compiled at -O1 
# optimization with timing disabled.
#
#-------------------------------------------------------------------------
.PHONY: mem
mem: $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)
	@echo "Running valgrind for all hw8c files"
	@echo "Testing $(OBJ1)_mem:" > $(MEM)
	$(VAL) $(VFLAGS) ./$(OBJ1)_mem $(FILE) >> $(MEM) 2>&1
	@echo " " >> $(MEM)
	@echo "Testing $(OBJ2)_mem:" >> $(MEM)
	$(VAL) $(VFLAGS) ./$(OBJ2)_mem $(FILE) >> $(MEM) 2>&1
	@echo " " >> $(MEM)
	@echo "Testing $(OBJ3)_mem:" >> $(MEM)
	$(VAL) $(VFLAGS) ./$(OBJ3)_mem $(FILE) >> $(MEM) 2>&1
	@echo " " >> $(MEM)
	@echo "Testing $(OBJ4)_mem:" >> $(MEM)
	$(VAL) $(VFLAGS) ./$(OBJ4)_mem $(FILE) >> $(MEM) 2>&1
	@echo " " >> $(MEM)
	cat $(MEM)
	

#does the normal things
.PHONY: help
help:
	@echo "all    - builds literally everything"
	@echo "test   - runs all tests and redirects output to $(OUT)"
	@echo "mem    - run valgrind for each version at -O1 performance, timing disabled"
	@echo "help   - lists possible commands"
	@echo "clean  - remove ALL build files"


#does the normal things
.PHONY: clean
clean:
	@echo "Tidying up the directory!"
	-rm -f *.o $(OBJ1)_0 $(OBJ1) $(OBJ1)_2 $(OBJ1)_3 $(OBJ1)_mem
	-rm -f *.o $(OBJ2)_0 $(OBJ2) $(OBJ2)_2 $(OBJ2)_3 $(OBJ2)_mem
	-rm -f *.o $(OBJ3)_0 $(OBJ3) $(OBJ3)_2 $(OBJ3)_3 $(OBJ3)_mem
	-rm -f *.o $(OBJ4)_0 $(OBJ4) $(OBJ4)_2 $(OBJ4)_3 $(OBJ4)_mem
	-rm -f $(OUT) $(MEM) 
