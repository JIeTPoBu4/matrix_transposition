#include "functions.h"

/*

        InputFile - input file descriptor
        matrix - matrix
        row - number of rows in matrix
        col - number of collumns in matrix
        not_null - number of non-null elements in matrix
        get_head_of_file() - functionn,read first 3 strings in InputFile, that stores number of rows,columns and non-null elements in matrix
        init() - function, initialize matrix zeros
        get_elem() - function, return element(member) of matrix
        set_elem() - function, set element(member) in matrix
        set_matrix() - function, set not-null elements from InputFile in matrix
        display_matrix() - function, display matrix
        transponate() - function, transponate input matrix and return pointer to result matrix
        free_matrix_memory() - function, free memory, that has been allocated for matrix
*/

int main(int argc, char *argv[]){
	if (argc != 2){
		perror("Error:Wrong number of input parameters!\n");
		return CAN_NOT_OPEN_FILE;
	}

	FILE *InputFile = NULL;
	if ((InputFile = fopen(argv[1], "r")) == NULL){
		perror("Error:can`t open file\n");
		fprintf(stderr, strerror(errno));
                perror("\n");
		return CAN_NOT_OPEN_FILE;
	}

	int row = 0;
	int col = 0;
	int not_null = 0;
	get_head_of_file(InputFile, &row, &col, &not_null);

	TYPE **matrix = NULL;
	if ((matrix = (TYPE **)allocate_memory(row, col)) == NULL){
		perror("Error:can`t allocate memory!\n");
		fprintf(stderr, strerror(errno));
                perror("\n");
		fclose(InputFile);
		return CAN_NOT_ALLOCATE_MEMORY;
	}

	init((void **)matrix, row, col);
	set_matrix(InputFile, (void **)matrix, not_null, row, col);

	if ((matrix = (TYPE **)transponate((void **)matrix, &row, &col)) == NULL){
		perror("Error:can`t allocate memory!\n");
		fprintf(stderr, strerror(errno));
                perror("\n");
		fclose(InputFile);
		return CAN_NOT_ALLOCATE_MEMORY;
	}

	display_matrix((void **)matrix, row, col);
	free_matrix_memory((void **)matrix, row);
        fclose(InputFile);

	return NO_ERRORS;
}

