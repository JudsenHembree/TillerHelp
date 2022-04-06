#ifndef FUNCTION_H
#define FUNCTION_H
/********************************
 *Cameron Tillirson, Ethan Ellis*
 *CPSC2311 Sp22 Section 003     *
 *ctillir@clemson.edu           *
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   int rows;
   int cols;
   int filterWidth;
   int** mtx;
   int** filter;
}MATRIX;


void allocateMemory(MATRIX);
void deallocateMemory(MATRIX);
void readInput(char*, MATRIX);
void printOutput(char*, MATRIX);
int setBorderSpace(int);
int checkRange(int);
int checkChange(MATRIX);
int calculateSpot(MATRIX);
int** makeChange(MATRIX, int);
void applyFilter(char*, MATRIX);
void setFilter(MATRIX);

#endif
