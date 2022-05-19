#pragma once
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct tree {
    int size;
    int key[3];
    struct tree* left;
    struct tree* mid;
    struct tree* right;
    struct tree* temp;
    struct tree* prev;
} tree;

char Find(int value, int* key, int size);

void Swap(int* x, int* y);

void Sort2(int* x, int* y);

void Sort3(int* x, int* y, int* z);

void SortKeys(int size, int* key);

tree* CreateNode(int value);

tree* CreateNode2(int value, tree* left, tree* mid, tree* right, tree* temp, tree* prev);

void AddKey(int value, tree* node);

void RemoveKey(int value, tree* node);

void BeNode2(int value, int* key, tree* node, tree* left, tree* mid);

char IsLeaf(tree* node);

tree* Split(tree* item);

tree* AddNode(tree* node, int value);

tree* Search(tree* node, int value);

tree* FindMin(tree* node);

tree* Merge(tree* leaf);

tree* Redistribute(tree* leaf);

tree* Fix(tree* leaf);

tree* DeleteNode(tree* node, int value);

void DestroyNode(tree* t);

void PrintNode(tree* node, int n);
