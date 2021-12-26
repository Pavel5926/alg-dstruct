#include "pch.h"
#include "Tree.c"
#include "TreeHeader.h"

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

class AddTreeMemory : public TestMemory {};
class DelTreeMemory : public TestMemory {};
class FindTreeMemory : public TestMemory {};
class IntersectionTreeMemory : public TestMemory {};

//Function for tests
tree_t* CreateModelTree(tree_t* tree) {
	//Creation ONLY for head of the tree == NULL
	if (tree == NULL) {
		tree = (tree_t*)malloc(sizeof(tree_t));
		if (tree == NULL) {
			return CREATION_FAILED;
		}
		tree->low = 15;
		tree->high = 20;
		tree->max = 30;
		tree->left = NULL;
		tree->right = NULL;
		tree->left = (tree_t*)malloc(sizeof(tree_t));
		if (tree->left == NULL) {
			free(tree);
			return CREATION_FAILED;
		}
		tree->right = (tree_t*)malloc(sizeof(tree_t));
		if (tree->right == NULL) {
			free(tree->left);
			free(tree);
			return CREATION_FAILED;
		}
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
	}
	else {
		printf("Test tree root is not NULL");
		return CREATION_FAILED;
	}
	return tree;
	//       [15, 20]
	//          30
	//  [10, 30]    [17, 19]
	//     30          19
}
TEST_F(AddTreeMemory, TreeNullPtr_returnCorrectTree) {
	tree_t* tree = NULL;
	tree = AddTree(tree, 1, 2);
	ASSERT_TRUE(tree != NULL);
	ASSERT_EQ(tree->low, 1);
	ASSERT_EQ(tree->high, 2);
	ASSERT_EQ(tree->max, 2);
	ASSERT_TRUE(tree->right == NULL);
	ASSERT_TRUE(tree->left == NULL);
	FreeTree(tree);
}
TEST_F(AddTreeMemory, TreeAddingNewInterval_returnCorrectTree) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	tree = AddTree(tree, 30, 40);
	ASSERT_EQ(tree->max, 30);
	ASSERT_EQ(tree->right->max, 19);
	ASSERT_TRUE(tree->right->right != NULL);
	ASSERT_EQ(tree->right->right->low, 30);
	ASSERT_EQ(tree->right->right->high, 40);
	ASSERT_EQ(tree->right->right->max, 40);
	ASSERT_TRUE(tree->right->right->right == NULL);
	ASSERT_TRUE(tree->right->right->left == NULL);
	FreeTree(tree);
}
TEST_F(AddTreeMemory, TreeAddingSameInterval_notChangeTree) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	tree = AddTree(tree, 17, 19);
	//compare to model tree
	ASSERT_TRUE(tree != NULL);
	ASSERT_EQ(tree->low, 15);
	ASSERT_EQ(tree->high, 20);
	ASSERT_EQ(tree->max, 30);
	ASSERT_TRUE(tree->left != NULL);
	ASSERT_EQ(tree->left->low, 10);
	ASSERT_EQ(tree->left->high, 30);
	ASSERT_EQ(tree->left->max, 30);
	ASSERT_TRUE(tree->left->left == NULL);
	ASSERT_TRUE(tree->left->right == NULL);
	ASSERT_TRUE(tree->right != NULL);
	ASSERT_EQ(tree->right->low, 17);
	ASSERT_EQ(tree->right->high, 19);
	ASSERT_EQ(tree->right->max, 19);
	ASSERT_TRUE(tree->right->left == NULL);
	ASSERT_TRUE(tree->right->right == NULL);
	FreeTree(tree);
}
TEST_F(DelTreeMemory, DeleteIntervalNoSubtrees_returnCorrectTree) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	tree = DelTree(tree, 17, 19);
	ASSERT_TRUE(tree->right == NULL);
	FreeTree(tree);
}
TEST_F(DelTreeMemory, DeleteIntervalWithTwoSubtrees_returnsCorrectTree) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	tree = DelTree(tree, 15, 20);
	ASSERT_TRUE(tree != NULL);
	ASSERT_EQ(tree->low, 17);
	ASSERT_EQ(tree->high, 19);
	ASSERT_EQ(tree->max, 30);
	ASSERT_TRUE(tree->left != NULL);
	ASSERT_EQ(tree->left->low, 10);
	ASSERT_EQ(tree->left->high, 30);
	ASSERT_EQ(tree->left->max, 30);
	ASSERT_TRUE(tree->left->left == NULL);
	ASSERT_TRUE(tree->left->right == NULL);
	ASSERT_TRUE(tree->right == NULL);
	FreeTree(tree);
}
TEST_F(DelTreeMemory, DeleteLeftIntervalWithLeftSubtree) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	tree = DelTree(tree, 15, 20); 
	//Using the results of previous test, we delete [17,19] segment now
	tree = DelTree(tree, 17, 19);
	ASSERT_TRUE(tree != NULL);
	ASSERT_EQ(tree->low, 10);
	ASSERT_EQ(tree->high, 30);
	ASSERT_EQ(tree->max, 30);
	ASSERT_TRUE(tree->left == NULL);
	ASSERT_TRUE(tree->left == NULL);
	FreeTree(tree);
}
TEST_F(DelTreeMemory, DeleteLeftIntervalWithRightSubtree) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	tree = AddTree(tree, 30, 40);
	//Usint the results of test "TreeAddingNewInterval_returnCorrectTree", we add and delete the [30,40] segment now
	tree = DelTree(tree, 30, 40);
	ASSERT_TRUE(tree != NULL);
	ASSERT_EQ(tree->low, 15);
	ASSERT_EQ(tree->high, 20);
	ASSERT_EQ(tree->max, 30);
	ASSERT_TRUE(tree->left != NULL);
	ASSERT_EQ(tree->left->low, 10);
	ASSERT_EQ(tree->left->high, 30);
	ASSERT_EQ(tree->left->max, 30);
	ASSERT_TRUE(tree->left->left == NULL);
	ASSERT_TRUE(tree->left->right == NULL);
	ASSERT_TRUE(tree->right != NULL);
	ASSERT_EQ(tree->right->low, 17);
	ASSERT_EQ(tree->right->high, 19);
	ASSERT_EQ(tree->right->max, 19);
	ASSERT_TRUE(tree->right->left == NULL);
	ASSERT_TRUE(tree->right->right == NULL);
	FreeTree(tree);
}
TEST_F(DelTreeMemory, DeleteIntervalThatDoesNotExist_returnCorrectTree) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	tree = DelTree(tree, 1, 2);
	//compare to model tree 
	ASSERT_TRUE(tree != NULL);
	ASSERT_EQ(tree->low, 15);
	ASSERT_EQ(tree->high, 20);
	ASSERT_EQ(tree->max, 30);
	ASSERT_TRUE(tree->left != NULL);
	ASSERT_EQ(tree->left->low, 10);
	ASSERT_EQ(tree->left->high, 30);
	ASSERT_EQ(tree->left->max, 30);
	ASSERT_TRUE(tree->left->left == NULL);
	ASSERT_TRUE(tree->left->right == NULL);
	ASSERT_TRUE(tree->right != NULL);
	ASSERT_EQ(tree->right->low, 17);
	ASSERT_EQ(tree->right->high, 19);
	ASSERT_EQ(tree->right->max, 19);
	ASSERT_TRUE(tree->right->left == NULL);
	ASSERT_TRUE(tree->right->right == NULL);
	FreeTree(tree);
}
TEST(DelTreeTest, DeleteNullPtr_returnNull) {
	tree_t* tree = NULL;
	tree = DelTree(tree, 1, 2);
	ASSERT_TRUE(tree == NULL);
}
TEST(FindTreeTest, NullTree_returnNotFound) {
	tree_t* tree = NULL;
	ASSERT_EQ(FindTree(tree, 1, 2), NOTFOUND);
}
TEST_F(FindTreeMemory, IntervalThatExist_returnFound) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	ASSERT_EQ(FindTree(tree, 17, 19), FOUND);
	FreeTree(tree);
}
TEST_F(FindTreeMemory, NodeThatExist_returnNotFound) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	ASSERT_EQ(FindTree(tree, 1, 2), NOTFOUND);
	FreeTree(tree);
}
TEST_F(IntersectionTreeMemory, OneIntersection) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	Intersect(tree, 5, 12);
	FreeTree(tree);
}
TEST_F(IntersectionTreeMemory, MoreThanOneIntersection) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	Intersect(tree, 5, 40);
	FreeTree(tree);
}
TEST_F(IntersectionTreeMemory, NoIntersection) {
	tree_t* tree = NULL;
	tree = CreateModelTree(tree);
	Intersect(tree, 1, 3);
	FreeTree(tree);
}