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

class TestMemory : public ::testing::Test {
protected:
	_CrtMemState s1, s2, s3;

	void SetUp() {
		_CrtMemCheckpoint(&s1);
	}

	void TearDown() {
		_CrtMemCheckpoint(&s2);
		if (_CrtMemDifference(&s3, &s1, &s2)) {
			_CrtMemDumpStatistics(&s3);
			FAIL();
		}
	}
};

class SudokuSolverMemory : public TestMemory {};
class MatrixInitMemory : public TestMemory {};

void TestResult(char const* name_out, char const* name_expected) {
	FILE* out = fopen(name_out, "r");
	if (!out) {
		perror("");
		return;
	}
	FILE* expected = fopen(name_expected, "r");
	if (!expected) {
		perror("");
		fclose(out);
		return;
	}
	fseek(out, 0, SEEK_END);
	fseek(expected, 0, SEEK_END);
	if (ftell(out) != ftell(expected)) {
		fclose(out);
		fclose(expected);
		FAIL();
	}
	fseek(out, 0, SEEK_SET);
	fseek(expected, 0, SEEK_SET);
	int val = -1;
	int exp = -1;
	while ((fscanf(out, "%d ", &val) > 0) && (fscanf(expected, "%d ", &exp) > 0)) {
		if (val != exp) {
			fclose(out);
			fclose(expected);
			FAIL();
		}
	}
	fclose(out);
	fclose(expected);
	return;
}

TEST_F(SudokuSolverMemory, StressTest) {
	char const* name_in = "SudokuIn.txt";
	//char const* name_in = "StressTestIn.txt";
	char const* name_out = "SudokuOut.txt";
	int checkcorrect = SudokuSolverFile(name_in, name_out);
	EXPECT_EQ(checkcorrect, 1);
}

TEST_F(MatrixInitMemory, FunctionalTestIncorrectDimension) {
	FILE* in = fopen("SudokuIncorrectDim.txt", "r");
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

TEST_F(SudokuSolverMemory, FunctionalTestNoSolutions) {
	char const* name_in = "SudokuInNoSolution.txt";
	char const* name_out = "SudokuOutFuncFirst.txt";
	char const* name_expected = "SudokuExpectedNull.txt";
	int checkcorrect = SudokuSolverFile(name_in, name_out);
	EXPECT_EQ(checkcorrect, 1);
	TestResult(name_out, name_expected);
}

TEST_F(SudokuSolverMemory, FunctionalTestSolutionFound) {
	char const* name_in = "SudokuIn.txt";
	char const* name_out = "SudokuOutFuncSecond.txt";
	char const* name_expected = "SudokuExpected.txt";
	int checkcorrect = SudokuSolverFile(name_in, name_out);
	EXPECT_EQ(checkcorrect, 1);
	TestResult(name_out, name_expected);

}

