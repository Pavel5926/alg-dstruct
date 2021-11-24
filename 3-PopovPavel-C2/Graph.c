#include "Graph_header.h"
stack_t* StackCreate() {
	stack_t* stack = (stack_t*)malloc(sizeof(stack));
	if (!stack) {
		return NULL;
	}
	stack->top = NULL;
	return stack;
}

int IsEmpty(stack_t* stack) {
	if (!stack->top) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int Push(stack_t* stack, int vert) {
	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	if (!tmp) {
		return FALSE;
	}
	tmp->vert = vert;
	tmp->next = stack->top;
	stack->top = tmp;
	return TRUE;
}

int Pop(stack_t* stack) {
	node_t* tmp = NULL;
	int vert = 0;
	if (IsEmpty(stack) != TRUE) {
		tmp = stack->top;
		vert = tmp->vert;
		stack->top = stack->top->next;
		free(tmp);
		return vert;
	}
	return EMPTY_STACK;
}

void StackDelete(stack_t* stack) {
	node_t* tmp = stack->top;
	while (tmp) {
		node_t* node_free = tmp;
		tmp = tmp->next;
		free(node_free);
	}
	free(stack);
}

int Peek(stack_t* stack) {
	return stack->top->vert;
}

int** MatrixCreate(int vert_num) {
	if (vert_num < 1) {
		return NULL;
	}
	int** matrix = (int**)malloc(sizeof(int*) * vert_num);
	if (!matrix) {
		return NULL;
	}
	for (int i = 0; i < vert_num; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * vert_num);
		if (!matrix[i]) {
			for (int j = 0; j < i; j++) {
				free(matrix[j]);
			}
			free(matrix);
			return NULL;
		}
	}
	return matrix;
}

void MatrixDelete(int** matrix, int vert_num) {
	for (int i = 0; i < vert_num; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

int ReadGraph(FILE* f, int** matrix) {
	if (!f) {
		perror("");
		return 0;
	}
	int check = 0;
	int vert1, vert2;
	while (feof(f) == 0) {
		check = fscanf(f, "%d %d\n", &vert1, &vert2);
		matrix[vert1][vert2] = 1;
		matrix[vert2][vert1] = 1;
	}
	return 1;
}

int GetAdjUnvisitedVertex(int** matrix, int* visited, int vert, int vert_num) {
	for (int i = 0; i < vert_num; i++) {
		if (matrix[vert][i] == 1 && visited[i] == 0) {
			return i;
		}
	}
	return -1;
}

int DFS(int** matrix, int vert_num, FILE* out) {
	if (vert_num < 1) {
		return 0;
	}
	int* visited = (int*)malloc(sizeof(int) * vert_num);
	if (!visited) {
		perror("");
		return -1;
	}
	for (int i = 0; i < vert_num; i++) {
		visited[i] = 0;
	}
	stack_t* stack = StackCreate();
	if (!stack) {
		perror("");
		free(visited);
		return -1;
	}
	int start = 0;
	visited[0] = 1;
	if (!Push(stack, start)) {
		StackDelete(stack);
		free(visited);
		return -1;
	}
	fprintf(out, "%d ", Peek(stack));
	while (!IsEmpty(stack)) {
		int cur_vert = -1;
		cur_vert = GetAdjUnvisitedVertex(matrix, visited, Peek(stack), vert_num);
		if (cur_vert == -1) {
			Pop(stack);
			if (Peek(stack) == 0) {
				//StackDelete(stack);
				//free(visited);
				break;
			}
		}
		else {
			visited[cur_vert] = 1;
			fprintf(out, "%d ", cur_vert);
			if (!Push(stack, cur_vert)) {
				StackDelete(stack);
				free(visited);
				return -1;
			}
		}
	}
	StackDelete(stack);
	free(visited);
	return 1;
}

void FillZero(int** matrix, int n) {
	if (n < 1) {
		return;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}
}

void PrintMatrix(int** mass, int size) {
	printf("\n");
	for (int str = 0; str < size; str++) {
		for (int col = 0; col < size; col++) {
			printf("%d ", mass[str][col]);
		}
		printf("\n");
	}
}
//
//int main(void) {
//	FILE* in = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-C2\\For_Lab_C.txt", "r");
//	//FILE* in = stdin;
//	//FILE* out = stdout;
//	FILE* out = fopen("D:\\repos\\alg-dstruct\\3-PopovPavel-C2\\For_Lab_C_out.txt", "w");
//	if (!in) {
//		perror("");
//		return -1;
//	}
//	if (!out) {
//		perror("");
//		fclose(in);
//		return -1;
//	}
//	int check = 0;
//	int vert_num = 0;
//	check = fscanf(in, "%d", &vert_num);
//	if (vert_num == 1) {
//		fprintf(out, "0");
//	}
//	else {
//		int** matrix = MatrixCreate(vert_num);
//		if (!matrix) {
//			perror("");
//			fclose(in);
//			fclose(out);
//			return -1;
//		}
//		FillZero(matrix, vert_num);
//		ReadGraph(in, matrix);
//		//PrintMatrix(matrix, vert_num);
//		DFS(matrix, vert_num, out);
//		MatrixDelete(matrix, vert_num);
//	}
//	fclose(in);
//	fclose(out);
//	return 0;
//}
