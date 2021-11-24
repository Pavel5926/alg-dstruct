#include "pch.h"
#include "Graph_header.h"
#include "Graph.c"

/*
 * OS: Windows 10 Pro 21H1 19043.1348
 * PC configuration:
 *      CPU: AMD Ryzen 7 PRO 2700 Eight-Core Processor 3.20 GHz
 *      RAM: 16 GB
 *      SSD: 480 GB
 */

 /*
  * load test results (cmake build type release):
  * Time: 2885 ms total
  * RAM:  up to 1.7 GB
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

class LoadTestMemory : public TestMemory {};

const char* filename_in = "TestData.txt";
const int verticesCount = (int)20000;

TEST_F(LoadTestMemory, graphGeneration) {
	const int maxNeighbourDelta = verticesCount / 5;
	FILE* in = fopen(filename_in, "w");
	if (!in) {
		perror("");
		FAIL();
	}
	fprintf(in, "%d\n", verticesCount);
	for (int i = 0; i < verticesCount; i++) {
		for (int neighbour = i + rand() % (maxNeighbourDelta - 1) + 1; neighbour < verticesCount;
			neighbour += rand() % (maxNeighbourDelta - 1) + 1) {
			fprintf(in, "%d %d\n", i, neighbour);
		}
	}
	fclose(in);
}

TEST_F(LoadTestMemory, graphReadAndBFS) {
	const char* filename_out = "D:\\repos\\alg-dstruct\\3-PopovPavel-C2\\For_Lab_C_Out.txt";
	FILE* in = fopen(filename_in, "r");
	if (!in) {
		perror("");
		FAIL();

	}
	int vert_num = 0;
	int check = fscanf(in, "%d", &vert_num);
	//if (vert_num < 1) {
	//	fclose(in);
	//	FAIL();
	//}
	int** matrix = MatrixCreate(vert_num);
	if (!matrix) {
		fclose(in);
		FAIL();
	}

	ReadGraph(in, matrix);
	FILE* out = fopen(filename_out, "w");
	if (!out) {
		fclose(in);
		MatrixDelete(matrix, vert_num);
		perror("");
		FAIL();
	}
	int check_DFS = DFS(matrix, vert_num, out);
	ASSERT_EQ(check_DFS, 1);
	MatrixDelete(matrix, vert_num);
	fclose(in);
	fclose(out);
}