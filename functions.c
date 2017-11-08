#ifndef _FUNCTIONS
#define _FUNCTIONS

#include "functions.h"

void free_matrix_memory(void **matrix, int row){
	for (int i = 0; i < row; i++){
		free(matrix[i]);
	}
	free(matrix);
}

void **allocate_memory(int row, int col){
	TYPE **matrix = (TYPE **)malloc(sizeof(double *) * row);

	if (matrix == NULL){
		perror("Error:can`t allocate memory!\n");
		fprintf(stderr, strerror(errno));
		return NULL;
	}

	for (int i = 0; i < row; i++){
		matrix[i] = (double*)malloc(sizeof(double)*col);

		if (matrix[i] == NULL){
			perror("Error:can`t allocate memory!\n");
			fprintf(stderr, strerror(errno));
			free_matrix_memory((void **)matrix, i);
			return NULL;
		}
	}

	return (void **)matrix;
}

void get_head_of_file(FILE *InputFile, int *row, int *col, int *not_null){
	int number_of_read = fscanf(InputFile, " %d  %d  %d ", row, col, not_null);
// #define PARAMS_COUNT
	if (number_of_read != 3){
		perror("Error:not enough parameters!\n");
		fclose(InputFile);
		exit(NOT_ENOUGH_PARAMETERS);
	}

	if ((*not_null < 0) || (*row <= 0) || (*col <= 0))
	{
		perror("Error:wrong parameter value!\n");
		fclose(InputFile);
		exit(NEGATIVE_PARAMETER_VALUE);

	}
	if ((*not_null) > (*row) * (*col))
	{
		perror("Error:count of non-null mebers more then count of matrix elements!\n");
		fclose(InputFile);
		exit(NULL_MEMBERS_MORE_THEN_ANOTHER);
	}
}

void init(void **matr, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			((TYPE**)matr)[i][j] = 0;
	}
}

void set_elem(void **matr, int row, int col, double elem)
{
	((TYPE **)matr)[row][col] = elem;
}

double get_elem(void **matr, int row, int col)
{
	return (((TYPE **)matr)[row][col]);
}
// const 
void set_matrix(FILE *InputFile, void **matrix,int not_null,int row,int col){
	int row_n = 0;
	int col_n = 0;
	double res = 0;
	int count = 0;
// so long
	while ((fscanf(InputFile, " %d %d %lf ", &row_n, &col_n, &res) == 3) && (count < not_null))
	{
		if (row_n < 0 || col_n < 0 || row_n > row || col_n > col)
		{
			perror("Error:wrong index-parameter value!\n");
			fclose(InputFile);
			free_matrix_memory(matrix, row);
			exit(NEGATIVE_PARAMETER_VALUE);
		}

		set_elem(matrix, row_n, col_n, res);
		count++;
	}

	if (count != not_null)
	{
		perror("Error:insufficient non-null parameters!\n");
		free_matrix_memory(matrix, row);
		fclose(InputFile);
		exit(NOT_ENOUGH_PARAMETERS);
	}
}

1 2 3 
4 5 6  -> 1 4, 2 5, 3 6

1 2     1 3
3 4 ->  2 4
void **transponate(void **matrix, int *row, int *col){
	if (*row == *col){
		TYPE buf = 0;
		for (int i = 0; i < *row; i++)
		{
			for (int j = *col - 1; j >= i; j--)
			{
// a =a +b b = a -b ... ?
				buf = ((TYPE**)matrix)[i][j];
				((TYPE**)matrix)[i][j] = ((TYPE**)matrix)[j][i];
				((TYPE**)matrix)[j][i] = buf;
			}
		}
		return matrix;
	}
	else {
		TYPE **buf = (TYPE **)allocate_memory(*col, *row);

		for (int z = 0; z < *row; z++)
		{
			for (int j = 0; j < *col; j++)
			{
				buf[j][z] = ((TYPE **)matrix)[z][j];
			}
		}

		free_matrix_memory(matrix, *row);

		int buffer = *row;
		*row = *col;
		*col = buffer;		
		
		return (void **)buf;
	}
}

void display_matrix(void **matrix,int row,int col){
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf(" %lf ", get_elem((void**)matrix, i, j));
		}
		printf("\n");
	}
}
#endif
