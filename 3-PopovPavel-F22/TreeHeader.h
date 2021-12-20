#ifndef F22_H_INCLUDED__
#define F22_H_INCLUDED__
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include <Windows.h>

#define N 100
#define SMALLNUMBER -9999999
#define FOUND 1
#define NOTFOUND -1

typedef struct tree {
	int low;
	int high;
	int max;
	struct tree* left;
	struct tree* right;
} tree_t;

tree_t* AddTree(tree_t* tree, int low, int high);
tree_t* DelTree(tree_t* tree, int low, int high);
int FindTree(tree_t* tree, int low, int high);
void Intersect(tree_t* tree, int low, int high);
void PrintTree(tree_t* tree, int index);
void FreeTree(tree_t* tree);
tree_t* CreateModelTree(tree_t* tree);
#endif
