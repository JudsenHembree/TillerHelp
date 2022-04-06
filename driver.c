/********************************
 *Cameron Tillirson, Ethan Ellis*
 *CPSC2311 Sp22 Section 003     *
 *ctillir@clemson.edu           *
 ********************************/
 
#include "functions.h"
/*
typedef struct {
	int rows;
	int cols;
	int filterWidth;
	int** mtx;
	int** filter;
}MATRIX;
*/



int main(int argc, char* argv[]){
	if(argc != 3){
		fprintf(stderr, "Proper use: driver.c <input file> <output file>\n");
		return 1;
	}
 
	MATRIX matrix1;		
	readInput(argv[1], matrix1);
	setFilter(matrix1);
	applyFilter(argv[1], matrix1);
	deallocateMemory(matrix1);
	return 0;
}


