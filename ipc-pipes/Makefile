# Makefile for "TwoPipesTwoChildren", "TwoPipesThreeChildren", "DynPipe" C++ Application
# author: Bo Seong Kim
# date: 11/12/2025

CC = g++
CPPFLAGS = -g -Wall

PROG1 = TwoPipesTwoChildren
PROG2 = TwoPipesThreeChildren
PROG3 = dynpipe

SRC1 = TwoPipesTwoChildren.cpp
SRC2 = TwoPipesThreeChildren.cpp
SRC3 = DynPipe.cpp

OBJ1 = TwoPipesTwoChildren.o
OBJ2 = TwoPipesThreeChildren.o
OBJ3 = DynPipe.o

# Default target: build all
all: $(PROG1) $(PROG2) $(PROG3)

# Part 1 Version 1 build
$(PROG1): $(OBJ1)
	$(CC) -o $(PROG1) $(OBJ1)

$(OBJ1): $(SRC1)
	$(CC) $(CPPFLAGS) -c $(SRC1)

# Part 1 Version 2 build
$(PROG2): $(OBJ2)
	$(CC) -o $(PROG2) $(OBJ2)

$(OBJ2): $(SRC2)
	$(CC) $(CPPFLAGS) -c $(SRC2)

# Part 2 build
$(PROG3): $(OBJ3)
	$(CC) -o $(PROG3) $(OBJ3)

$(OBJ3): $(SRC3)
	$(CC) $(CPPFLAGS) -c $(SRC3)

# clean all object and executable files
clean:
	rm -f core $(PROG1) $(PROG2) $(PROG3) $(OBJ1) $(OBJ2) $(OBJ3)
