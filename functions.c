/********************************
 *Cameron Tillirson, Ethan Ellis*
 *CPSC2311 Sp22 Section 003     *
 *ctillir@clemson.edu           *
 ********************************/
 
 #include "functions.h"

/* Parameters: matrix - MATRIX struct that has values in rows and cols
 *             
 * Return:        void
 * This function dynamically allocates memory for the int** mtx inside matrix using 
 * rows and cols
 */
void allocateMemory(MATRIX matrix){
	matrix.mtx = (int**)malloc(sizeof(int*) * matrix.rows);
	for(int i = 0; i < matrix.rows; i++){
		matrix.mtx[i] = (int*)malloc(sizeof(int) * matrix.cols);
	}
}

/* Parameters: matrix - MATRIX struct that has had memory allocated
 *               
 * Return:        void
 * This function deallocates the dynamic memory for mtx inside matrix
 */
void deallocateMemory(MATRIX matrix){
	for(int i = 0; i < matrix.rows; i++){
		free(matrix.mtx[i]);
	}
	free(matrix.mtx);

}

/* Parameters: input - char array that holds the name of a file
 *             matrix - MATRIX struct that will hold data from input
 * Return:        void
 * This function opens a file with the name stored in input and fills out the needed data for 
 * matrix to allocate its memory and fill its mtx 2d array  
 */
void readInput(char* input, MATRIX matrix){
	int rows, cols;
	char trash;
	FILE* dev = fopen(input, "r");
	fscanf(dev, "%d", &rows);
	fscanf(dev, "%d", &cols);
	matrix.rows = rows;
	matrix.cols = cols;
	allocateMemory(matrix);
	fprintf(stderr, "%d %d\n", matrix.rows, matrix.cols);
	for(int i = 0; i < matrix.rows; i++){
		for(int j = 0; j < matrix.cols; j++){
			fprintf(stderr, "here\n");
			fscanf(dev, "%d ", &(matrix.mtx[i][j]));
			fprintf(stderr, "%d ", matrix.mtx[i][j]);
			fprintf(stderr, "here2\n");
		}
		//trash catches newline character at end of each row
		trash = fgetc(dev);
	}
	fclose(dev);
} 

/* Parameters: output - char array holding the name of a file
 *             matrix - MATRIX struct holding data needed to print to array
 * Return:        void
 * This function opens up a file with the name stored in output and prints
 * the contents of mtx to it
 */
void printOutput(char* output, MATRIX matrix){
	FILE* somewhere = fopen(output, "w");
	for(int r = 0; r < matrix.rows; r++){
		for(int c = 0; c < matrix.cols; c++){
			fprintf(somewhere, "%d ", matrix.mtx[r][c]);
		}
	}
}

/* Parameters: filterWidth - int that is the width of filter being used
 *                    
 * Return:        half the filterWidth
 * This function takes in the filterWidth and divides it by two to find
 * the needed offset for using the filter
 */
int setBorderSpace(int filterWidth){
	return filterWidth / 2;
}

/* Parameters: calcResult - int that is the sum of calculateSpot
 *                    
 * Return:        the closest int in range of 0-255 to calcResult
 * This function checks if calcresult is within the range 0-255 and will return 
 * calcResult if it is, 0 if its less that 0, and 255 if its greater than 255
 */
int checkRange(int calcResult){
	if(calcResult < 0){
		return 0;
	}
	else if(calcResult > 255){
		return 255;
	}
	else{
		return calcResult;
	}
}

//Makes sure matrix dimensions allow for makeChange to work
int checkChange(MATRIX matrix){
	if(matrix.filterWidth > matrix.rows){
		return 0;
	}
	else if(matrix.filterWidth > matrix.cols){
		return 0;
	}
	else{
		return 1;
	}
}

//Looks at surronding spots and manipulates them, then adds the values together
int calculateSpot(MATRIX matrix){
	int newSpot = 0;
	for(int fr = 0; fr < matrix.filterWidth; fr++){
		for(int fc = 0; fc < matrix.filterWidth; fc++){
			newSpot += matrix.mtx[fr][fc] * matrix.filter[fr][fc];
		}
	}
	return newSpot;
}

//This function goes through the given matrix if the matrix is compatable and then calls
//calculateSpot on each spot, calls checkRange to make sure result is within range, 
//and adds the spot to a new int** which will be printed out once it is filled out.
int** makeChange(MATRIX matrix, int offset){
	if(checkChange(matrix)){
		int temp;
		int** output;
		//allocate memory for output to pursist
		output = (int**)malloc(sizeof(int*) * matrix.rows);
   	for(int i = 0; i < matrix.rows; i++){
      	matrix.mtx[i] = (int*)malloc(sizeof(int) * matrix.cols);
   	}


		for(int r = 0; r < (matrix.rows - matrix.filterWidth); r++){
			for(int c = 0; c < (matrix.cols - matrix.filterWidth); c++){
				temp = calculateSpot(matrix);
				temp = checkRange(temp);
				output[r][c] = temp;
			}
		}
		return output;
	}
}

//Calls other functions to apply filter
void applyFilter(char* target, MATRIX matrix){
	int borderSpace = setBorderSpace(matrix.filterWidth);
	//A new matrix is created with the same values of rows, cols, and filterWidth as given matrix
	MATRIX newMatrix;
	newMatrix.rows = matrix.rows;
	newMatrix.cols = matrix.cols;
	allocateMemory(newMatrix);
	newMatrix.filterWidth = matrix.filterWidth;
	newMatrix.mtx = makeChange(matrix, borderSpace);
	printOutput(target, newMatrix);
}

//
void setFilter(MATRIX matrix){
	char temp[] = "";
	fprintf(stdout, "Please enter the filter you would like to use 3x3 or 5x5:\n");
   fscanf(stdin, "%s", temp);
   if(strcmp(temp, "3x3") == 0){
      matrix.filterWidth = 3;

      for(int i = 0; i < 3; i++){
         if(i == 1){
           matrix.filter[i][0] = -1;
           matrix.filter[i][1] = 5;
           matrix.filter[i][2] = -1;
         }
         else{
            matrix.filter[i][0] = 0;
            matrix.filter[i][1] = -1;
            matrix.filter[i][2] = 0;
         }
      }
   }
   else if(strcmp(temp, "5x5") == 0){
      matrix.filterWidth = 5;
      for(int i = 0; i < 5; i++){
         if(i == 2){
            matrix.filter[i][0] = -1;
            matrix.filter[i][1] = -1;
            matrix.filter[i][2] = 9;
            matrix.filter[i][3] = -1;
            matrix.filter[i][4] = -1;
         }
         else{
            matrix.filter[i][0] = 0;
            matrix.filter[i][1] = 0;
            matrix.filter[i][2] = -1;
            matrix.filter[i][3] = 0;
            matrix.filter[i][4] = 0;
         }
      }
   }
   else{
      fprintf(stderr, "Invalid filter used. Must be either 3x3 or 5x5");
      return;
   }
}
