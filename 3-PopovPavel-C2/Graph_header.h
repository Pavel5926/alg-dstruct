#pragma once
#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
#define EMPTY_STACK -1
#define EMPTY_LIST -1

typedef struct node {
	int vert;
	struct node* next;
}node_t;

typedef struct stack {
	node_t* top;
}stack_t;

stack_t* StackCreate();
int IsEmpty(stack_t* stack);
stack_t* Push(stack_t* stack, int vert);
int Pop(stack_t* stack);
void StackDelete(stack_t* stack);
int Peek(stack_t* stack);
int** MatrixCreate(int vert_num);
void MatrixDelete(int** matrix, int vert_num);
int** ReadGraph(FILE* f, int** matrix);
int GetAdjUnvisitedVertex(int** matrix, int* visited, int vert, int vert_num);
int DFS(int** matrix, int vert_num, FILE* out);
void FillZero(int** matrix, int n);
void PrintMatrix(int** mass, int size);