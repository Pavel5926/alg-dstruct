#include"TreeHeader.h"

tree_t* AddTree(tree_t* tree, int low, int high) {
	if (tree == NULL) {
		tree = (tree_t*)malloc(sizeof(tree_t));
		if (tree == NULL)
			return NULL;
		tree->high = high;
		tree->low = low;
		tree->max = high;
		tree->left = NULL;
		tree->right = NULL;
	}
	else {
		if (low < tree->low)
			tree->left = AddTree(tree->left, low, high);
		else {
			if (low > tree->low)
				tree->right = AddTree(tree->right, low, high);
		}
	}
	if (tree->max < high)
		tree->max = high;
	return tree;
}
static tree_t* MinimumTree(tree_t* tree) {
	if (tree->left == NULL)
		return tree;
	return MinimumTree(tree->left);
}
static int FindMaxArray(int array[N]) {
	int max = array[0];
	int i;
	for (i = 0; i < N; i++) {
		if (array[i] > max)
			max = array[i];
	}
	return max;
}
static void MaxOfSubtree(tree_t* tree, int* res) {
	int i = 0;
	int max[N];
	if (tree != NULL && (tree->left != NULL || tree->right != NULL)) {
		memset(max, SMALLNUMBER, sizeof(int));
		if (tree->left != NULL) {
			MaxOfSubtree(tree->left, res);
			max[i++] = tree->left->high;
		}
		if (tree->right != NULL) {
			MaxOfSubtree(tree->right, res);
			max[i++] = tree->right->high;
		}
		max[i] = tree->high;
		*res = FindMaxArray(max);
	}
	if (tree != NULL) {
		*res = tree->high;
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
	if (tree == NULL)
		return tree;
	if (low < tree->low)
		tree->left = DelTree(tree->left, low, high);
	else {
		if (low > tree->low || high != tree->high)
			tree->right = DelTree(tree->right, low, high);
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
		if (tmp->low == low && tmp->high == high)
			return FOUND;
		else
			if (low < tmp->low)
				tmp = tmp->left;
			else
				if (low > tmp->low || high != tmp->high)
					tmp = tmp->right;
	}
	return NOTFOUND;
}
void Intersect(tree_t* tree, int low, int high) {
	if (tree == NULL)
		return;
	if (!((tree->low > high) || (tree->high < low)))
		printf("Interval [%i,%i] intersects with [%i,%i]\n", low, high, tree->low, tree->high);
	if (tree->left != NULL && tree->left->max >= low)
		Intersect(tree->left, low, high);
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
//Function for tests
tree_t* CreateModelTree(tree_t* tree) {
	tree = (tree_t*)malloc(sizeof(tree_t));
	if (tree == NULL)
		return NULL;
	tree->low = 15;
	tree->high = 20;
	tree->max = 30;
	tree->left = NULL;
	tree->right = NULL;
	tree->left = (tree_t*)malloc(sizeof(tree_t));
	if (tree->left == NULL)
		return NULL;
	tree->right = (tree_t*)malloc(sizeof(tree_t));
	if (tree->right == NULL)
		return NULL;
	tree->left->low = 10;
	tree->left->high = 30;
	tree->left->max = 30;
	tree->right->low = 17;
	tree->right->high = 19;
	tree->right->max = 19;
	tree->left->left = NULL;
	tree->left->right = NULL;
	tree->right->left = NULL;
	tree->right->right = NULL;
	return tree;
	//       [15, 20]
	//          30
	//  [10, 30]    [17, 19]
	//     30          19
}
//int main() {
//    return 0;
//}