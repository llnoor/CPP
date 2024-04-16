#ifndef CONTAINERS_SRC_SET_SET_H_
#define CONTAINERS_SRC_SET_SET_H_

#include <assert.h>

#include <stdexcept>
#include <utility>

#include "../tree/tree.h"

namespace  {

template <typename TKey>
class set : public Tree<TKey> {
 public:
  using key_type = TKey;
  using tree_type = Tree<key_type>;
  using node_type = TreeNode<key_type>;

  using typename tree_type::const_iterator;
  using typename tree_type::const_reference;
  using typename tree_type::iterator;
  using typename tree_type::reference;
  using typename tree_type::size_type;

  set() : tree_type() {}

  set(std::initializer_list<key_type> const &items) {
    for (const_reference item : items) {
      node_type *node = new node_type(item);
      if (!tree_type::InsertNode(node)) delete node;
    }
  }
};

}  // namespace 

#endif /* CONTAINERS_SRC_SET_SET_H_ */
