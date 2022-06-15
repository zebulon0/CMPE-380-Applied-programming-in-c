############################################################
# Lab 05 Assignment Makefile
# by Zeb Hollinger 3/12/21
############################################################

# C compile things
CC       = gcc
CFLAGS   = -O1 -g -Wall -std=c99 -pedantic

# Valgrindy things
V        = valgrind
VFLAGS   =  --tool=memcheck --leak-check=yes --track-origins=yes

# Source .c files
SOURCE   = $(SOURCE1) $(SOURCE2) $(SOURCE3)
SOURCE1	 = DynamicArrays.c
SOURCE2  = LinkedLists.c
SOURCE3  = TestSearch.c

#Program .o files
PROG    = TestSearch

# Necessary text files
OUT      = out.txt
MEM      = mem.txt

# Test text file
FILE     = engWords.txt

# Word to search for
SEARCHWORD = space

#Keep it from printing program execution
.SILENT:

#Should make TestSearch
.PHONY: all
all: $(PROG)

.PHONY: $(PROG)
$(PROG): $(SOURCE)
	@echo "Compiling $?"
	$(CC) $(CFLAGS) $(SOURCE) -o $@


#should run TestSearch twice, once with a make macro variable
#of SEARCHWORD, the word should be "space" and then with the invalid value of "xyzzy"
#output is redirected to out.txt
.PHONY: test
test: $(PROG)
	@echo "Testing $<.."
	./$(PROG) $(FILE) $(SEARCHWORD) >> $(OUT)
	./$(PROG) $(FILE) xyzzy >> $(OUT)
	cat $(OUT)


#should run using the macro SEARCHWORD with valgrind
#redirect this to mem.txt
.PHONY: mem
mem: $(PROG) 
	$(V) $(VFLAGS) ./$(PROG) $(FILE) $(SEARCHWORD) >> $(MEM) 2>&1
	cat $(MEM)


#does the normal things
.PHONY: help
help:
	@echo "all   - make TestSearch"
	@echo "test  - runs TestSearch twice with different inputs puts output in $(OUT)"
	@echo "mem   - runs valgrind, puts output in $(MEM)"
	@echo "help  - lists possible commands"
	@echo "clean - cleans the .o files and .txt files from the working directory"

#does the normal things
.PHONY: clean
clean:
	@echo "Tidying up the directory!"
	-rm -f *.o $(PROG) 
	-rm -f $(OUT) $(MEM)
