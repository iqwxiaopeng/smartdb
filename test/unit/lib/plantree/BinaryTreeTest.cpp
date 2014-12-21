#include <vector>
#include "SmartdbTest.h"
#include "plantree/BinaryTree.h"

using namespace Smartdb;

class BinaryTreeTest : public SmartdbTest {
protected:
  BinaryTreeTest() {}

  virtual void SetUp() {}
};

//      0
//      |
//   |--+-------|
//   1          3
//    \      |--+---|
//     2     4      8
//          / \    /
//         5   7  9
//        /
//       6
class InbalancedTreeTest : public BinaryTreeTest {
public:
  static int nodes[10];

protected:
  BinaryTree<int> tree;

  InbalancedTreeTest()
  : tree(&nodes[0])
  {
    tree.add_left_child_of(&nodes[0], &nodes[1]);
    tree.add_right_child_of(&nodes[0], &nodes[3]);
    tree.add_right_child_of(&nodes[1], &nodes[2]);
    tree.add_left_child_of(&nodes[3], &nodes[4]);
    tree.add_right_child_of(&nodes[3], &nodes[8]);
    tree.add_left_child_of(&nodes[4], &nodes[5]);
    tree.add_right_child_of(&nodes[4], &nodes[7]);
    tree.add_left_child_of(&nodes[5], &nodes[6]);
    tree.add_left_child_of(&nodes[8], &nodes[9]);
  }
};
int InbalancedTreeTest::nodes[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };


TEST_F(BinaryTreeTest, construct_tree_with_only_root) {
  char root_node[] = "root node";
  BinaryTree<char> tree(root_node);
  EXPECT_EQ(root_node, tree.get_root());
}

TEST_F(BinaryTreeTest, leaves_iterator_when_only_root_exists) {
  char root_node[] = "root node";
  BinaryTree<char> tree(root_node);

  auto it = tree.leaves_begin();
  EXPECT_EQ(root_node, *it);
  EXPECT_EQ(tree.leaves_end(), ++it);
}

TEST_F(BinaryTreeTest, returned_object_can_be_modified_using_const_cast) {
  int root = 777;
  BinaryTree<int> tree(&root);
  int * p_root = tree.get_root();
  EXPECT_EQ(777, *p_root);
  *p_root = 333;
  EXPECT_EQ(333, *p_root);
}

TEST_F(BinaryTreeTest, construct_tree_with_only_left_child) {
  char root_node[] = "root node";
  char child_node[] = "child node";

  BinaryTree<char> tree(root_node);
  tree.add_left_child_of(root_node, child_node);

  EXPECT_EQ(root_node, tree.get_root());

  auto it = tree.leaves_begin();
  EXPECT_EQ(child_node, *it);
  EXPECT_EQ(tree.leaves_end(), ++it);
}

TEST_F(BinaryTreeTest, construct_tree_with_only_right_child) {
  char root_node[] = "root node";
  char child_node[] = "child node";

  BinaryTree<char> tree(root_node);
  tree.add_right_child_of(root_node, child_node);

  EXPECT_EQ(root_node, tree.get_root());

  auto it = tree.leaves_begin();
  EXPECT_EQ(child_node, *it);
  EXPECT_EQ(tree.leaves_end(), ++it);
}

TEST_F(BinaryTreeTest, construct_tree_with_left_and_right_children) {
  char root_node[] = "root node";
  char left_child_node[] = "left child node";
  char right_child_node[] = "right child node";

  BinaryTree<char> tree(root_node);
  tree.add_left_child_of(root_node, left_child_node);
  tree.add_right_child_of(root_node, right_child_node);

  EXPECT_EQ(root_node, tree.get_root());

  auto it = tree.leaves_begin();
  EXPECT_EQ(left_child_node, *it);
  EXPECT_EQ(right_child_node, *(++it));
  EXPECT_EQ(tree.leaves_end(), ++it);
}

TEST_F(BinaryTreeTest, construct_tree_with_right_and_left_children) {
  char root_node[] = "root node";
  char left_child_node[] = "left child node";
  char right_child_node[] = "right child node";

  BinaryTree<char> tree(root_node);
  tree.add_right_child_of(root_node, right_child_node);
  tree.add_left_child_of(root_node, left_child_node);

  EXPECT_EQ(root_node, tree.get_root());

  auto it = tree.leaves_begin();
  EXPECT_EQ(left_child_node, *it);
  EXPECT_EQ(right_child_node, *(++it));
  EXPECT_EQ(tree.leaves_end(), ++it);
}

TEST_F(InbalancedTreeTest, leaves_of_inbalanced_tree) {
  auto it = tree.leaves_begin();
  EXPECT_EQ(&nodes[2], *it);
  EXPECT_EQ(&nodes[6], *(++it));
  EXPECT_EQ(&nodes[7], *(++it));
  EXPECT_EQ(&nodes[9], *(++it));
  EXPECT_EQ(tree.leaves_end(), ++it);
}

TEST_F(InbalancedTreeTest, lookup_node) {
  BinaryTree<int>::node_t node4 = tree[&nodes[4]];
  EXPECT_EQ(&nodes[3], node4.parent);
  EXPECT_EQ(&nodes[5], node4.left_child);
  EXPECT_EQ(&nodes[7], node4.right_child);
}

// Error cases

TEST_F(BinaryTreeTest, error_on_duplicate_child_addition) {
  char root_node[] = "root node";
  char child_node[] = "child node";

  BinaryTree<char> tree(root_node);
  tree.add_left_child_of(root_node, child_node);
  ASSERT_THROW(tree.add_left_child_of(root_node, child_node);, SmartdbAssertionFailed);
}

TEST_F(BinaryTreeTest, error_on_circular_nodes) {
  char root_node[] = "root node";
  char child_node[] = "child node";

  BinaryTree<char> tree(root_node);
  tree.add_left_child_of(root_node, child_node);
  ASSERT_THROW(tree.add_left_child_of(child_node, root_node), SmartdbAssertionFailed);
}
