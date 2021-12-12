#include "pch.h"
#include "sudoku_header.h"
#include "lab_sudoku.c"
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

void testResult(FILE* out, FILE* expected) {
	if (!out) {
		perror("");
		return;
	}
	if (!expected) {
		perror("");
		return;
	}
	fseek(out, 0, SEEK_END);
	fseek(expected, 0, SEEK_END);
	fseek(out, 0, SEEK_SET);
	fseek(expected, 0, SEEK_SET);
	if (ftell(out) != ftell(expected)) {
		fclose(out);
		fclose(expected);
		FAIL();
	}
	int val = -1;
	int exp = -1;
	while ((fscanf(out, "%d ", &val) > 0) && (fscanf(expected, "%d ", &exp) > 0)) {
		if (val != exp) {
			fclose(out);
			fclose(expected);
			FAIL();
		}
	}
	return;
}

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
	int checkcorrect = SudokuSolverFile(in, out);
	EXPECT_EQ(checkcorrect, 1);
	fclose(in);
	fclose(out);
}

TEST(MatrixInitTest, FunctionalTestIncorrectDimension) {
	FILE* in = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuIncorrectDim.txt", "r");
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
	FILE* in = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuInNoSolution.txt", "r");
	FILE* out = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuOutFuncFirst.txt", "w");
	FILE* expected = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuExpectedNull.txt", "r");
	if (!in) {
		perror("");
		FAIL();
	}
	if (!out) {
		perror("");
		fclose(in);
		FAIL();
	}
	if (!expected) {
		perror("");
		fclose(in);
		fclose(out);
		FAIL();
	}
	int checkcorrect = SudokuSolverFile(in, out);
	EXPECT_EQ(checkcorrect, 1);
	fclose(out);
	FILE* outcheck = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuOutFuncFirst.txt", "r");
	if (!outcheck) {
		perror("");
		fclose(in);
		fclose(expected);
		FAIL();
	}
	testResult(outcheck, expected);
	fclose(in);
	fclose(outcheck);
	fclose(expected);
}

TEST(SudokuSolverTest, FunctionalTestSolutionFound) {
	FILE* in = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuIn.txt", "r");
	FILE* out = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuOutFuncSecond.txt", "w");
	FILE* expected = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuExpected.txt", "r");
	if (!in) {
		perror("");
		FAIL();
	}
	if (!out) {
		perror("");
		fclose(in);
		FAIL();
	}
	if (!expected) {
		perror("");
		fclose(in);
		fclose(out);
		FAIL();
	}
	int checkcorrect = SudokuSolverFile(in, out);
	EXPECT_EQ(checkcorrect, 1);
	fclose(out);
	FILE* outcheck = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-D14\\SudokuOutFuncSecond.txt", "r");
	if (!outcheck) {
		perror("");
		fclose(in);
		fclose(expected);
		FAIL();
	}
	testResult(outcheck, expected);
	fclose(in);
	fclose(outcheck);
	fclose(expected);
}
