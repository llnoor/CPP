#ifndef CONTAINERS_SRC_MULTISET_MULTISET_H_
#define CONTAINERS_SRC_MULTISET_MULTISET_H_

#include <assert.h>

#include <stdexcept>
#include <utility>

#include "../tree/tree.h"

namespace  {

template <typename TKey>
class multiset : public Tree<TKey> {
 public:
  using key_type = TKey;

  using tree_type = Tree<key_type>;
  using node_type = TreeNode<key_type>;

  using typename tree_type::const_iterator;
  using typename tree_type::const_reference;
  using typename tree_type::iterator;
  using typename tree_type::reference;
  using typename tree_type::size_type;

  bool IsMultiset() const override { return true; }

  multiset() : tree_type() {}

  multiset(std::initializer_list<key_type> const &items) {
    for (const_reference item : items) {
      node_type *node = new node_type(item);
      if (!tree_type::InsertNode(node)) delete node;
    }
  }

  std::pair<iterator, iterator> equal_range(const key_type &key) {
    node_type *node = tree_type::root();
    node_type *lowerNode = nullptr;
    node_type *upperNode = nullptr;

    while (node != nullptr) {
      if (tree_type::CompareNode(key, node) > 0) {
        node = node->right;
      } else {
        if (upperNode == nullptr && (tree_type::CompareNode(key, node) < 0))
          upperNode = node;
        lowerNode = node;
        node = node->left;
      }
    }
    if (upperNode == nullptr)
      node = tree_type::root();
    else
      node = upperNode->left;

    while (node != nullptr) {
      if (tree_type::CompareNode(key, node) < 0) {
        upperNode = node;
        node = node->left;
      } else
        node = node->right;
    }
    return std::pair<iterator, iterator>(iterator(lowerNode),
                                         iterator(upperNode));
  }

  size_t count(const key_type &key) {
    size_t n = 0;
    std::pair<iterator, iterator> range = equal_range(key);
    for (iterator &it = range.first; it != range.second; ++it, ++n) {
    }
    return n;
  }

  iterator lower_bound(const key_type &key) { return equal_range(key).first; }

  iterator upper_bound(const key_type &key) { return equal_range(key).second; }
};

}  // namespace 

#endif /* CONTAINERS_SRC_MULTISET_MULTISET_H_ */
