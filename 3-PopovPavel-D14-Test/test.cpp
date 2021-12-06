#include "pch.h"
#include "D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\sudoku_header.h"
#include "D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\lab_sudoku.c"
/*
 * OS: Windows 10 Pro 21H1 19043.1348
 * PC configuration:
 *      CPU: AMD Ryzen 7 PRO 2700 Eight-Core Processor 3.20 GHz
 *      RAM: 16 GB
 *      SSD: 480 GB
 *		HDD: 596 GB
 */

 /*
  * load test results (visual studio 2019 release):
  * Time: 51876 ms total
  * RAM:  up to 903 KB
  */
TEST(SudokuSolverTest, StressTest) {
	FILE* in = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuIn.txt", "r");
	//FILE* in = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\StressTestIn.txt", "r");
	FILE* out = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuOut.txt", "w");
	if (!in) {
		perror("");
		FAIL();
	}
	if (!out) {
		perror("");
		fclose(in);
		FAIL();
	}
	int small_dimension = 0;
	int checkin = fscanf(in, "%d", &small_dimension);
	int dimension = small_dimension * small_dimension;
	int** sudoku = MatrixInit(dimension);
	int parsecheck = ParseMatrix(in, sudoku, dimension);
	if (!parsecheck) {
		fclose(in);
		fclose(out);
		MatrixDelete(sudoku, dimension);
		FAIL();
	}
	int str_cur = 0;
	if (SudokuSolver(sudoku, dimension, small_dimension, str_cur)) {
		PrintMatrix(out, sudoku, dimension);
	}
	else {
		printf("0\n");
	}
	MatrixDelete(sudoku, dimension);
	fclose(in);
	fclose(out);
}
TEST(MatrixInitTest, FunctionalTestIncorrectDimension) {
	FILE* in = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuInFuncFirst.txt", "r");
	if (!in) {
		perror("");
		FAIL();
	}
	int small_dimension = 0;
	int checkin = fscanf(in, "%d", &small_dimension);
	int dimension = small_dimension * small_dimension;
	int** sudoku = MatrixInit(dimension);
	ASSERT_EQ(sudoku, nullptr);
	MatrixDelete(sudoku, dimension);
	fclose(in);
}
TEST(SudokuSolverTest, FunctionalTestNoSolutions) {
	FILE* in = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuInFuncFirst.txt", "r");
	if (!in) {
		perror("");
		FAIL();
	}
	int small_dimension = 0;
	int checkin = fscanf(in, "%d", &small_dimension);
	int dimension = small_dimension * small_dimension;
	int** sudoku = MatrixInit(dimension);
	int parsecheck = ParseMatrix(in, sudoku, dimension);
	if (parsecheck) {
		fclose(in);
		MatrixDelete(sudoku, dimension);
		FAIL();
	}
	int str_cur = 0;
	int check = -1;
	check = SudokuSolver(sudoku, dimension, small_dimension, str_cur);
	EXPECT_EQ(check, 0);
	MatrixDelete(sudoku, dimension);
	fclose(in);
}

TEST(SudokuSolverTest, FunctionalTestSolutionFound) {
	FILE* in = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuIn.txt", "r");
	FILE* out = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuOutFuncSecond.txt", "w");
	if (!in) {
		perror("");
		FAIL();
	}
	if (!out) {
		perror("");
		fclose(in);
		FAIL();
	}
	int small_dimension = 0;
	int checkin = fscanf(in, "%d", &small_dimension);
	int dimension = small_dimension * small_dimension;
	int** sudoku = MatrixInit(dimension);
	int parsecheck = ParseMatrix(in, sudoku, dimension);
	if (!parsecheck) {
		fclose(in);
		fclose(out);
		MatrixDelete(sudoku, dimension);
		FAIL();
	}
	int str_cur = 0;
	int check = -1;
	check = SudokuSolver(sudoku, dimension, small_dimension, str_cur);
	EXPECT_EQ(check, 1);
	PrintMatrix(out, sudoku, dimension);
	MatrixDelete(sudoku, dimension);
	fclose(in);
	fclose(out);
}
