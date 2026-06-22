# Makefile for CS3377 Assignment 6
# Author: Bo Seong Kim
# Date: 12/05/2025
# Purpose: Build and clean matrix multiplication project

PROG = matrix_product
CC = g++
FLAGS = -g -Wall -pthread
SRC = main.cpp
OBJ = main.o

$(PROG): $(OBJ)
	$(CC) $(FLAGS) -o $(PROG) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(FLAGS) -c $(SRC)

clean:
	rm -f core $(PROG) $(OBJ)
