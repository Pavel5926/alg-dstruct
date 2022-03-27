#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#pragma warning (disable:4996)

typedef struct treap {
	int value;
	int priority;
	int count;
	struct treap* left;
	struct treap* right;
}treap_t;

int hash(int value) {
	return abs((int)(pow(value, 5) - 7.2 * pow(value, 3) + 9.5 * pow(value, 2) - 7 * value + 2.5) % (101));
}

treap_t* treapCreate(int value, int prior) {
	treap_t* tree = (treap_t*)malloc(sizeof(treap_t));
	if (!tree) {
		return NULL;
	}
	tree->left = NULL;
	tree->right = NULL;
	tree->value = value;
	tree->priority = prior;
	tree->count = 1;
	return tree;
}

void treapDestroy(treap_t* tree) {
	if (tree) {
		treapDestroy(tree->left);
		treapDestroy(tree->right);
		free(tree);
	}
}

int getTreeSize(treap_t* tree) {
	if (!tree) {
		return 0;
	}
	else {
		return tree->count;
	}
}

void Recount(treap_t* tree) {
	if (tree) {
		tree->count = getTreeSize(tree->left) + getTreeSize(tree->right) + 1;
	}
	return;
}

treap_t* Merge(treap_t* left, treap_t* right) {
	if (!left) {
		return right;
	}
	else if (!right) {
		return left;
	}
	else if (left->priority > right->priority) {
		left->right = Merge(left->right, right);
		Recount(left);
		return left;
	}
	else {
		right->left = Merge(left, right->left);
		Recount(right);
		return right;
	}
}

void Split(treap_t* tree, int k, treap_t** left, treap_t** right) {
	int current_key = 0;
	if (tree == NULL) {
		*left = NULL;
		*right = NULL;
		return;
	}
	if (getTreeSize(tree->left) <= k) {
		Split(tree->right, k - getTreeSize(tree->left) - 1, &(tree->right), right);
		*left = tree;
	}
	else {
		Split(tree->left, k, left, &(tree->left));
		*right = tree;
	}
	Recount(tree);
}

treap_t* Insert(treap_t* tree, int pos, int value) {
	treap_t* left = NULL;
	treap_t* right = NULL;
	if (tree) {
		Split(tree, pos, &left, &right);
	}
	treap_t* mer = treapCreate(value, hash(value));
	return Merge(Merge(left, mer), right);
}

treap_t* Remove(treap_t* tree, int pos) {
	treap_t* left = NULL;
	treap_t* right = NULL;
	treap_t* mer = NULL;
	treap_t* tmp = NULL;
	Split(tree, pos - 1, &left, &right);
	Split(right, 0, &mer, &tmp);
	tree = Merge(left, tmp);
	treapDestroy(mer);
	return tree;
}

int FindByPosition(treap_t* tree, int pos) {
	int index = getTreeSize(tree->left);
	if (pos < index) {
		return FindByPosition(tree->left, pos);
	}
	if (pos == index) {
		return tree->value;
	}
	else {
		return FindByPosition(tree->right, pos - index - 1);
	}
}

// returns 1-based index of value
int Find(treap_t* tree, int value, int cur_pos) {
	if (tree) {
		// index of value in treap
		int ind = cur_pos + getTreeSize(tree->left) + 1;
		// if found, return it
		if (tree->value == value) {
			return ind;
		}
		//look left
		int ret = Find(tree->left, value, cur_pos);
		if (ret) {
			return ret;
		}
		//look right
		return Find(tree->right, value, ind);
	}
	return 0;
}

treap_t* RemoveValue(treap_t* tree, int value) {
	int pos = Find(tree, value, 0);
	// if element in tree
	if (pos) {
		//remove by position
		return Remove(tree, pos - 1);
	}
	else {
		// do nothing
		return tree;
	}
}

int main() {
	char command = 0;
	int data = 0;
	treap_t* tree = NULL;
	FILE* f = fopen("test.txt", "r");
	while (fscanf(f, "%c %d \n", &command, &data) != EOF) {
		if (command == 'a') {
			if (!Find(tree, data, 0)) {
				tree = Insert(tree, getTreeSize(tree), data);
			}
		}
		else if (command == 'r') {
			tree = RemoveValue(tree, data);
		}
		else if (command == 'f') {
			printf("%s\n", Find(tree, data, 0) ? "yes" : "no");
		}
	}
	return 0;
}
