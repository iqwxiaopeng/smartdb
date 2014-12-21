/*
 * BinaryTree.h
 *
 *  Created on: 2014/12/21
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_PLANTREE_BINARYTREE_H_
#define INCLUDE_PLANTREE_BINARYTREE_H_

#include <list>
#include <unordered_map>
#include <algorithm>
#include "hack/Class.h"
#include "hack/Assert.h"

namespace Smartdb {

template <typename T>
class BinaryTree {

public:
  typedef struct node_t {
    T* left_child;
    T* right_child;
    T* parent;
  } node_t;

  typedef std::list<T*> leaves_t;

  BinaryTree(T* const root)
  : root(NULL), leaves(0)
  {
    nodes_map[root] = { NULL, NULL, NULL };

    // cache
    this->root = root;
    leaves.push_back(root);
  }
  ~BinaryTree() {}

  T* get_root() const {
    return const_cast<T*>(root);
  }

  node_t & operator[] (T* node) {
    return nodes_map[node];
  }

  /**
   * Returns iterator of leaves.  Leaves are ordered from left to right.
   * @example
   *   int root = 777;
   *   BinaryTree<int> tree(&root);
   *   // ...
   *   for (auto it = tree.leaves_begin(); it != tree.leaves_end(); ++it) {
   *     // ...
   *   }
   */
  typename leaves_t::iterator leaves_begin() {
    return leaves.begin();
  }
  typename leaves_t::iterator leaves_end() {
    return leaves.end();
  }

  void add_left_child_of(T* const parent, T* const child) {
    node_t & parent_node = nodes_map[parent];
    ASSERT(!parent_node.left_child);
    _add_child_of(parent, child);
    parent_node.left_child = child;
  }
  void add_right_child_of(T* const parent, T* const child) {
    node_t & parent_node = nodes_map[parent];
    _add_child_of(parent, child);
    ASSERT(!parent_node.right_child);
    parent_node.right_child = child;
  }

private:
  // Cache to return important nodes fast.
  T* root;
  leaves_t leaves;

  // Represents tree structure.
  // It is designed to lookup any node from the tree fast.
  std::unordered_map<T*, node_t> nodes_map;

  /**
   * Find leaf from leaves cache.
   * @param leaf Pointer to find from leaves cache.
   * @return Iterator pointing at the leaf.  leaves.cend() is returned if leaf is not found.
   */
  typename leaves_t::iterator find_leaf_iter(T* leaf) {
    return std::find(leaves.begin(), leaves.end(), leaf);
  }

  void _add_child_of(T* const parent, T* const child) {
    node_t & parent_node = nodes_map[parent];
    ASSERT(!parent_node.left_child || !parent_node.right_child);

    // create child info
    nodes_map[child] = { NULL, NULL, parent };

    // update leaves cache
    if (!parent_node.left_child && !parent_node.right_child) {
      // parent becomes non-leaf, instead child becomes leaf.
      auto it = find_leaf_iter(parent);
      ASSERT(it != leaves_end());
      *it = child;
    } else if (parent_node.left_child && !parent_node.right_child) {
      // `child` is next leaf of left child
      auto it = find_leaf_iter(parent_node.left_child);
      leaves.insert(++it, child);
    } else if (!parent_node.left_child && parent_node.right_child) {
      // `child` is previous leaf of right child
      auto it = find_leaf_iter(parent_node.right_child);
      leaves.insert(it, child);
    }
  }

  PREVENT_COPY_CONSTRUCTOR(BinaryTree);
  PREVENT_OBJECT_ASSIGNMENT(BinaryTree);
};

} /* namespace Smartdb */

#endif /* INCLUDE_PLANTREE_BINARYTREE_H_ */
