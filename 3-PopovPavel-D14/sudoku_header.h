#pragma once
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
#define FALSE 0
#define TRUE 1
int** MatrixInit(int dimension);
int ParseMatrix(FILE* f, int** matrix, int dimension);
void MatrixDelete(int** matrix, int dimension);
void PrintMatrix(FILE* out, int** matrix, int dimension);
int IsPossibleToAdd(int** sudoku, int str, int col, int num, int dimension, int small_dimension);
int Solve(int** sudoku, int dimension, int small_dimension, int s_cur);
int SudokuSolver(int** matrix, int dimension, int small_dimension, int s_cur);