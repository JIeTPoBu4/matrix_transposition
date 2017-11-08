#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include "errors.c"

//#ifndef TYPE
#define TYPE double
//#endif

void **allocate_memory(int row, int col);
void free_matrix_memory(void **matrix, int row);
void get_head_of_file(FILE *InputFile, int *row, int *col, int *not_null);
void init(void **matr, int row, int col);
void set_elem(void **matr, int row, int col, double elem);
double get_elem(void **matr, int row, int col);
void set_matrix(FILE *InputFile, void **matrix, int not_null, int row, int col);
void **transponate(void **matrix, int *row, int *col);
void display_matrix(void **matrix, int row, int col);

#endif
