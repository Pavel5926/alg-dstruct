#include"TreeHeader.h"

tree_t* AddTree(tree_t* tree, int low, int high) {
	if (tree == NULL) {
		tree = (tree_t*)malloc(sizeof(tree_t));
		if (tree == NULL) {
			return NULL;
		}
		tree->high = high;
		tree->low = low;
		tree->max = high;
		tree->left = NULL;
		tree->right = NULL;
	}
	else {
		if (low < tree->low) {
			tree->left = AddTree(tree->left, low, high);
			if (tree->left != NULL) {
				if (tree->max < high) {
					tree->max = high;
				}
			}
		}

		if (low > tree->low) {
			tree->right = AddTree(tree->right, low, high);
		}
		if (low == tree->low) {
			printf("Tree already has an equal key \n.");
		}

	}

	return tree;
}
static tree_t* MinimumTree(tree_t* tree) {
	if (tree->left == NULL) {
		return tree;
	}
	return MinimumTree(tree->left);
}
static int FindMaxArray(int array[N]) {
	int max = array[0];
	int i;
	for (i = 0; i < N; i++) {
		if (array[i] > max) {
			max = array[i];
		}
	}
	return max;
}
static void MaxOfSubtree(tree_t* tree, int* res) {
	int i = 0;
	static int max[N];
	for (int j = 0; j < N; j++) {
		max[j] = SMALLNUMBER;
	}

	if (tree != NULL && (tree->left != NULL || tree->right != NULL)) {
		//memset(max, -2147483647, sizeof(-2147483647));
		if (tree->left != NULL) {
			MaxOfSubtree(tree->left, res);
			max[i++] = tree->left->high;
		}
		if (tree->right != NULL) {
			MaxOfSubtree(tree->right, res);
			max[i++] = tree->right->high;
		}
		max[i++] = tree->high;
		*res = FindMaxArray(max);
	}
	if ((tree != NULL) && (tree->high >= *res)) {
		*res = tree->high;
	}
	if (i == N - 1) {
		printf("Too much vertices");
		return;
	}
}
static tree_t* FixTree(tree_t* tree) {
	int res = 0;
	if (tree != NULL) {
		MaxOfSubtree(tree, &res);
		tree->max = res;
		tree->left = FixTree(tree->left);
		tree->right = FixTree(tree->right);
	}
	return tree;
}
tree_t* DelTree(tree_t* tree, int low, int high) {
	if (tree == NULL) {
		return tree;
	}
	if (low < tree->low) {
		tree->left = DelTree(tree->left, low, high);
	}
	else {
		if (low > tree->low || high != tree->high) {
			tree->right = DelTree(tree->right, low, high);
		}
		else {
			if (tree->left != NULL && tree->right != NULL) {
				tree_t* max = MinimumTree(tree->right);
				tree->low = max->low;
				tree->high = max->high;
				tree->max = max->max;
				tree->right = DelTree(tree->right, max->low, max->high);
				tree = FixTree(tree);
			}
			else {
				if (tree->left != NULL) {
					tree_t* tmp = tree;
					tree = tree->left;
					tree = FixTree(tree);
					free(tmp);
				}
				else
					if (tree->right != NULL) {
						tree_t* tmp = tree;
						tree = tree->right;
						tree = FixTree(tree);
						free(tmp);
					}
					else {
						tree_t* tmp = tree;
						tree = NULL;
						tree = FixTree(tree);
						free(tmp);
					}
			}
		}
	}
	return tree;
}
int FindTree(tree_t* tree, int low, int high) {
	tree_t* tmp = tree;
	while (tmp != NULL) {
		if (tmp->low == low && tmp->high == high) {
			return FOUND;
		}
		else
			if (low < tmp->low) {
				tmp = tmp->left;
			}
			else
				if (low > tmp->low || high != tmp->high) {
					tmp = tmp->right;
				}
	}
	return NOTFOUND;
}
void Intersect(tree_t* tree, int low, int high) {
	if (tree == NULL) {
		return;
	}
	if (!((tree->low > high) || (tree->high < low))) {
		printf("Interval [%i,%i] intersects with [%i,%i]\n", low, high, tree->low, tree->high);
	}
	if ((tree->left != NULL) && (tree->left->max >= low)) {
		Intersect(tree->left, low, high);
	}
	Intersect(tree->right, low, high);
}
void PrintTree(tree_t* tree, int index) {
	if (tree != NULL) {
		printf("level:%i low:%i high:%i max:%i\n", index, tree->low, tree->high, tree->max);
		PrintTree(tree->left, index + 1);
		PrintTree(tree->right, index + 1);
	}
}
void FreeTree(tree_t* tree) {
	if (tree != NULL) {
		FreeTree(tree->right);
		FreeTree(tree->left);
		free(tree);
	}
}

//int main() {
//    return 0;
//}