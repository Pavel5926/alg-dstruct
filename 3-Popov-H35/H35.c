#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#pragma warning (disable:4996)

typedef struct treap {
	int key;
	int priority;
	int count;
	struct treap* left;
	struct treap* right;
}treap_t;

int Hash(int key) {
	srand(key);
	return rand();
}

treap_t* treapCreate(int key) {
	treap_t* tree = (treap_t*)malloc(sizeof(treap_t));
	if (!tree) {
		return NULL;
	}
	tree->left = NULL;
	tree->right = NULL;
	tree->key = key;
	tree->priority = Hash(key);
	tree->count = 1;
	return tree;
}

void treapDestroy(treap_t* tree) {
	if (tree) {
		treapDestroy(tree->left);
		treapDestroy(tree->right);
		free(tree);
	}
	return;
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
	treap_t* result = NULL;
	if (!left) {
		return right;
	}
	else if (!right) {
		return left;
	}
	else if (left->priority > right->priority) {
		left->right = Merge(left->right, right);

		return left;
	}
	else {
		right->left = Merge(left, right->left);
		return right;
	}
}

void Split(treap_t* tree, int key, treap_t** left, treap_t** right) {
	treap_t* tmp = NULL;
	if (!tree) {
		*left = NULL;
		*right = NULL;
		return;
	}
	if (tree->key <= key) {
		Split(tree->right, key, &tmp, right);
		tree->right = tmp;
		*left = tree;
	}
	else {
		Split(tree->left, key, left, &tmp);
		tree->left = tmp;
		*right = tree;
	}
	return;
}

treap_t* Insert(treap_t* tree, int key) {
	treap_t* left = NULL;
	treap_t* right = NULL;
	if (tree) {
		Split(tree, key, &left, &right);
	}
	treap_t* mer = treapCreate(key);
	return Merge(Merge(left, mer), right);
}

treap_t* Remove(treap_t* tree, int key) {
	treap_t* left = NULL;
	treap_t* right = NULL;
	treap_t* mer = NULL;
	Split(tree, key - 1, &left, &right);
	Split(right, key, &mer, &tree);
	treapDestroy(mer);
	return Merge(left, tree);
}

treap_t* Find(treap_t* tree, int key) {
	treap_t* result = NULL;
	while (tree) {
		if (tree->key == key) {
			result = tree;
			break;
		}
		if (tree->key > key) {
			tree = tree->left;
		}
		else {
			tree = tree->right;
		}
	}
	return result;
}

int main() {
	srand(time(0));
	char command = 0;
	int data = 0;
	treap_t* tree = NULL;
	//FILE* f = fopen("test.txt", "r");
	while (fscanf(stdin, "%c %d\n", &command, &data) != EOF) {
		if (command == 'a') {
			if (tree == NULL)
				tree = treapCreate(data);
			else
				tree = Insert(tree, data);
		}
		else if (command == 'r')
			tree = Remove(tree, data);
		else if (command == 'f') {
			if (Find(tree, data))
				fprintf(stdout, "yes\n");
			else
				fprintf(stdout, "no\n");
		}
	}
	return 0;
}