#include "sudoku_header.h"

int** MatrixInit(int dimension) {
	if ((dimension < 9) || (dimension > 81)) {
		printf("Incorrect size of sudoku matrix, according to the task\n");
		return NULL;
	}
	int** matrix = (int**)malloc(sizeof(int*) * dimension);
	if (!matrix) {
		return NULL;
	}
	for (int i = 0; i < dimension; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * dimension);
		if (!matrix[i]) {
			for (int j = 0; j < i; j++) {
				free(matrix[j]);
			}
			return NULL;
		}
	}
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

int ParseMatrix(FILE* f, int** matrix, int dimension) {
	if (!f) {
		perror("");
		return FALSE;
	}
	if (!matrix) {
		fclose(f);
		return FALSE;
	}
	int control = -1;
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			control = fscanf(f, "%d", &matrix[i][j]);
		}
	}
	return TRUE;
}

void MatrixDelete(int** matrix, int dimension) {
	if (!matrix) {
		return;
	}
	for (int j = 0; j < dimension; j++) {
		free(matrix[j]);
	}
	free(matrix);
}

void PrintMatrix(FILE* out, int** matrix, int dimension) {
	if (!out) {
		return;
	}
	if (!matrix) {
		return;
	}
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			fprintf(out, "%d ", matrix[i][j]);
		}
		fprintf(out, "\n");
	}
	return;
}

int IsPossibleToAdd(int** sudoku, int str, int col, int num, int dimension, int small_dimension) {
	for (int i = 0; i < dimension; i++) {
		if (sudoku[str][i] == num) {
			return FALSE;
		}
	}
	for (int j = 0; j < dimension; j++) {
		if (sudoku[j][col] == num) {
			return FALSE;
		}
	}
	int str_sq = (str / small_dimension) * small_dimension;
	int col_sq = (col / small_dimension) * small_dimension;
	for (int i = 0; i < small_dimension; i++) {
		for (int j = 0; j < small_dimension; j++) {
			if (sudoku[str_sq + i][col_sq + j] == num) {
				return FALSE;
			}
		}
	}
	return TRUE;
}

int SudokuSolver(int** matrix, int dimension, int small_dimension, int s_cur) {
	if (!matrix) {
		return FALSE;
	}
	if ((small_dimension < 3) || (small_dimension > 9)) {
		printf("Incorrect dimension according to the task\n");
		return FALSE;
	}
	return Solve(matrix, dimension, small_dimension, s_cur);
}

int Solve(int** sudoku, int dimension, int small_dimension, int s_cur) {
	for (; s_cur < dimension; s_cur++) {
		for (int c_cur = 0; c_cur < dimension; c_cur++) {
			if (sudoku[s_cur][c_cur] == 0) {
				for (int num = 1; num < dimension + 1; num++) {
					if (IsPossibleToAdd(sudoku, s_cur, c_cur, num, dimension, small_dimension)) {
						sudoku[s_cur][c_cur] = num;
						if (Solve(sudoku, dimension, small_dimension, s_cur))
							return TRUE;
						sudoku[s_cur][c_cur] = 0;
					}
				}
				return FALSE;
			}
		}
	}
	return TRUE;
}

