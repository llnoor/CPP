#ifndef CONTAINERS_SRC_TREE_TREE_H_
#define CONTAINERS_SRC_TREE_TREE_H_

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace  {

template <typename TTree>
class TreeConstIterator;

template <typename TTree>
class TreeIterator;

template <typename TKey>
class TreeNode;

template <typename TKey>
class Tree {
 public:
  using tree_type = Tree<TKey>;
  using node_type = TreeNode<TKey>;

  using key_type = TKey;
  using reference = TKey &;
  using const_reference = const TKey &;
  using size_type = size_t;

  using iterator = TreeIterator<tree_type>;
  using const_iterator = TreeConstIterator<tree_type>;

  Tree() : header_(nullptr) {}

  ~Tree() {
    ClearTree(header_);
    num_nodes_ = 0;
  }

  void ClearTree(node_type *node) {
    if (node != nullptr) {
      ClearTree(node->left);
      ClearTree(node->right);
      delete node;
      node = nullptr;
    }
  }

  Tree(const Tree &second) {
    if (this->header_ != second.header_) {
      ClearTree(this->header_);

      if (second.header_ != nullptr) {
        this->header_ = new node_type(second.header_);
        CopyWithoutBalancing(second.header_, this->header_);
      }

      this->num_nodes_ = second.num_nodes_;
    }
  }

  Tree(Tree &&second) { MoveConstructor(std::move(second)); }

  Tree &operator=(Tree &&second) {
    MoveConstructor(std::move(second));
    return *this;
  }

  void MoveConstructor(Tree &&second) {
    std::swap(header_, second.header_);
    std::swap(num_nodes_, second.num_nodes_);
  }

  void swap(Tree &second) {
    std::swap(header_, second.header_);
    std::swap(num_nodes_, second.num_nodes_);
  }

  void clean(node_type *node) {
    node->left = nullptr;
    node->right = nullptr;
    node->red = true;
    node->parent = nullptr;
  }

  void merge(tree_type &second) {
    if (second.header_ != nullptr && this->header_ != nullptr) {
      node_type *thisNode = nullptr;
      node_type *secondNode = nullptr;
      for (const_iterator iterator_second_tree = second.begin();
           iterator_second_tree != second.end();) {
        secondNode = (iterator_second_tree++).node_;
        thisNode = second.DeleteNode(secondNode);
        clean(thisNode);
        if (!InsertNode(thisNode)) second.InsertNode(thisNode);
      }
    }
  }

  void clear() {
    if (header_ != nullptr) {
      ClearTree(header_);
      header_ = nullptr;
      num_nodes_ = 0;
    }
  }

  virtual bool contains(const TKey &key) { return (FindNode(key) != nullptr); }

  std::pair<iterator, bool> insert(const TKey &key) {
    node_type *node = nullptr;
    bool temp_bool = false;

    if (!IsMultiset()) node = FindNode(key);

    if (node == nullptr) {
      node = new node_type(key);
      temp_bool = InsertNode(node);
    }
    return std::pair<iterator, bool>(node, temp_bool);
  }

  iterator find(const TKey &key) { return iterator(FindNode(key)); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::initializer_list<key_type> items = {args...};
    std::vector<std::pair<iterator, bool>> temp_vector;

    for (const TKey &item : items) {
      std::pair<node_type *, bool> temp_insert = tree_type::InsertKey(item);
      temp_vector.push_back(std::pair<iterator, bool>(
          iterator(temp_insert.first), temp_insert.second));
    }
    return temp_vector;
  }

  const_iterator begin() const { return iterator(MinNode(header_)); }
  const_iterator rbegin() const { return iterator(MaxNode(header_)); }
  const_iterator end() const { return iterator(nullptr); }

  iterator begin() { return iterator(MinNode(header_)); }
  iterator rbegin() { return iterator(MaxNode(header_)); }
  iterator end() { return iterator(nullptr); }

  node_type *root() { return header_; }
  bool empty() { return (header_ == nullptr); }
  size_type size() const { return num_nodes_; }
  size_type max_size() {
    std::allocator<key_type> size;
    return size.max_size();
  }

  void erase(TKey key) {
    node_type *node = FindNode(key);
    if (node != nullptr) {
      node = DeleteNode(node);
      delete node;
    }
  }

  void erase(iterator it) {
    node_type *node = it.node_;
    if (node != nullptr) {
      node = DeleteNode(node);
      delete node;
    }
  }

  virtual bool IsMultiset() const { return false; }

  virtual int CompareNode(node_type *x, node_type *y) {
    int i = -1;
    if (x->key < y->key)
      i = -1;
    else if (x->key > y->key)
      i = 1;
    else
      i = 0;
    return i;
  }

  virtual int CompareNode(TKey key, node_type *y) {
    int i = -1;
    if (key < y->key)
      i = -1;
    else if (key > y->key)
      i = 1;
    else
      i = 0;
    return i;
  }

  node_type *FindNode(TKey key) {
    node_type *node = header_;
    if (node == nullptr) return nullptr;

    while (node != nullptr && 0 != CompareNode(key, node)) {
      if (CompareNode(key, node) > 0)
        node = node->right;
      else if (CompareNode(key, node) < 0)
        node = node->left;
    }
    return node;
  }

  // Проверка возможности поворота
  int Rotation() {
    int flag = 0;
    node_type *p_parent_temp = new node_type();
    node_type *uncleNode = Uncle(p_parent_temp);
    node_type *grandparent = Grandpa(p_parent_temp);
    node_type *parent_temp = new node_type();
    node_type *left_temp = new node_type();
    node_type *left_right_temp = new node_type();
    node_type *right_temp = new node_type();
    p_parent_temp->left = parent_temp;
    parent_temp->parent = p_parent_temp;
    parent_temp->left = left_temp;
    parent_temp->right = right_temp;
    left_temp->parent = parent_temp;
    left_temp->right = left_right_temp;
    left_right_temp->parent = left_temp;
    left_right_temp->red = true;
    right_temp->parent = parent_temp;
    left_temp->red = false;
    LowerNeighbor(right_temp);
    ClearTree(p_parent_temp);
    if (grandparent == nullptr && uncleNode == nullptr) flag = 1;
    return flag;
  }

  // Функция для добавления новый ноды без балансировки
  // Если ключ ноды меньше ключа рассмаотриваемого узла то добавляем как левый
  // сын Если больше то как правый сын Если равны, то не добавляем (для set)
  bool InsertNode(node_type *node) {
    if (header_ == nullptr) {
      header_ = node;
    } else {
      node_type *parentNode = header_;
      node_type *currentNode = header_;
      while (currentNode != nullptr) {
        if (CompareNode(node, parentNode) < 0)
          currentNode = parentNode->left;
        else
          currentNode = parentNode->right;
        if (0 == CompareNode(node, parentNode) && !IsMultiset()) return false;
        if (currentNode != nullptr) parentNode = currentNode;
      }
      node->red = (node == header_) ? false : true;

      if (CompareNode(node, parentNode) < 0)
        parentNode->left = node;
      else
        parentNode->right = node;
      node->parent = parentNode;

      TreeBalancing(node);
    }
    num_nodes_ += 1;
    return true;
  }

  static node_type *MaxNode(node_type *node) {
    if (node == nullptr) return nullptr;
    while (node->right != nullptr) node = node->right;
    return node;
  }

  static node_type *MinNode(node_type *node) {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) node = node->left;
    return node;
  }

 private:
  std::pair<node_type *, bool> InsertKey(const TKey &key) {
    node_type *node = nullptr;
    bool temp_bool = false;

    if (!IsMultiset()) node = FindNode(key);

    if (node == nullptr) {
      node = new node_type(key);
      temp_bool = InsertNode(node);
    }
    return std::pair<node_type *, bool>(node, temp_bool);
  }

  node_type *Grandpa(node_type *node) {
    if (node->parent != nullptr && node->parent->parent != nullptr)
      return node->parent->parent;
    return nullptr;
  }

  node_type *Uncle(node_type *node) {
    node_type *grandparent = Grandpa(node);
    if (grandparent == nullptr)
      return nullptr;
    else if (grandparent->left == node->parent)
      return grandparent->right;
    else
      return grandparent->left;
  }

  node_type *Neighbour(node_type *node) {
    if (node == node->parent->left)
      return node->parent->right;
    else
      return node->parent->left;
  }

  void ReplaceChildsOfParent(node_type *x, node_type *y) {
    if (x->parent != nullptr) {
      if (x == x->parent->left)
        x->parent->left = y;
      else if (x == x->parent->right)
        x->parent->right = y;
    }
  }

  void ReplaceNode(node_type *x, node_type *y) {
    ReplaceChildsOfParent(x, y);
    ReplaceChildsOfParent(y, x);

    std::swap(x->left, y->left);
    std::swap(x->right, y->right);
    std::swap(x->parent, y->parent);
    std::swap(x->red, y->red);

    if (x->left != nullptr) x->left->parent = x;
    if (x->right != nullptr) x->right->parent = x;
    if (y->left != nullptr) y->left->parent = y;
    if (y->right != nullptr) y->right->parent = y;
  }

  void CopyWithoutBalancing(node_type *from, node_type *to) {
    if (from->right != nullptr) {
      node_type *node = new node_type(from->right);
      to->right = node;
      node->parent = to;
      CopyWithoutBalancing(from->right, node);
    }

    if (from->left != nullptr) {
      node_type *node = new node_type(from->left);
      to->left = node;
      node->parent = to;
      CopyWithoutBalancing(from->left, node);
    }
  }

  // Надо удалить значение-ключ
  // Это значение хранится в узле
  // Этот узел отправляем в эту функцию чтобы выдернуть из дерева и уничтожить
  // Функцию надо сводить к удалению узла который имеет только одного сына или
  // вообще не имеет Известно что у узла слева находятся значения меньше
  // значения узла Поэтому делаем замену (узел <-> максимальный узел среди левой
  // ветки этого узла) У этого узла нет правого сына.
  node_type *DeleteNode(node_type *node) {
    if (node == nullptr) return nullptr;
    node_type *replaceableNode = node;
    if (replaceableNode->left != nullptr) {
      replaceableNode = MaxNode(replaceableNode->left);
    } else if (replaceableNode->right != nullptr) {
      replaceableNode = MinNode(replaceableNode->right);
    }
    if (replaceableNode != node) {
      ReplaceNode(replaceableNode, node);
      if (header_ == node) header_ = replaceableNode;
      replaceableNode = node;
    }

    // Если заменяемый узел черный, нельзя просто удалить узел, так как черная
    // высота меняется Поэтому
    if (replaceableNode->red == false) {
      node_type *child;
      if (replaceableNode->left != nullptr)
        child = replaceableNode->left;
      else
        child = replaceableNode->right;

      // Если есть один ребенок (а может быть только один ребенок, так как мы
      // спустились до самого нижнего узла) Тогда этого ребенка поднимаем на
      // место удаляемого узла и меняем цвет на черный
      if (child != nullptr) {
        child->parent = replaceableNode->parent;

        if (replaceableNode->parent->left == replaceableNode) {
          replaceableNode->parent->left = child;
        } else if (replaceableNode->parent->right == replaceableNode) {
          replaceableNode->parent->right = child;
        }

        child->red = false;
      } else {  //если нет детей
        DeleteNodeWithoutChild(replaceableNode);
      }
    }  // else: Если заменяемый узел красный, тогда можно просто удалить узел,
    // так как черная высота не меняется

    // Родителю сообщаем, что уходим
    if (replaceableNode->parent != nullptr) {
      if (replaceableNode->parent->left == replaceableNode) {
        replaceableNode->parent->left = nullptr;
      } else if (replaceableNode->parent->right == replaceableNode) {
        replaceableNode->parent->right = nullptr;
      }
    } else
      header_ =
          nullptr;  // Если нет родителя, то сообщаем дереву, что оно пусто

    num_nodes_ -= 1;

    return replaceableNode;
  }

  // Удаляем узла без детей
  // Если узел левый, тогда черного соседа поднимаем на место родителя
  void DeleteNodeWithoutChild(node_type *node) {
    if (node->parent != nullptr) {
      node_type *neighbor = Neighbour(node);
      if (neighbor->red == true && neighbor != nullptr) {
        node->parent->red = true;
        neighbor->red = false;
        if (node == node->parent->left)
          RotateLeft(node->parent);
        else
          RotateRight(node->parent);
      }
      ChangeNeighborToRed(node);
    }
  }

  // Если родитель черный и сосед черный, тогда поменяем цвет соседа на красный
  void ChangeNeighborToRed(node_type *node) {
    node_type *neighbor = Neighbour(node);
    if ((node->parent->red == false) && (neighbor->red == false) &&
        (neighbor->left == nullptr || neighbor->left->red == false) &&
        (neighbor->right == nullptr || neighbor->right->red == false)) {
      neighbor->red = true;
      DeleteNodeWithoutChild(node->parent);
    } else {
      ReplaceParentNeighborColor(node);
    }
  }

  // Если родитель красный и сосед черный, тогда меняем их цвета
  void ReplaceParentNeighborColor(node_type *node) {
    node_type *neighbor = Neighbour(node);
    if ((node->parent->red == true) && (neighbor->red == false) &&
        (neighbor->left == nullptr || neighbor->left->red == false) &&
        (neighbor->right == nullptr || neighbor->right->red == false)) {
      neighbor->red = true;
      node->parent->red = false;
    } else {
      LowerNeighbor(node);
      RaiseNeighbor(node);
    }
  }

  // Если сосед черный и сын соседа черный
  // тогда соседа делаем красным и меняем с сыном
  void LowerNeighbor(node_type *node) {
    node_type *neighbor = Neighbour(node);
    if (neighbor->red == false) {
      if ((node == node->parent->left) &&
          (neighbor->right == nullptr || neighbor->right->red == false) &&
          (neighbor->left != nullptr && neighbor->left->red == true)) {
        neighbor->red = true;
        neighbor->left->red = false;
        RotateRight(neighbor);
      } else if ((node == node->parent->right) &&
                 (neighbor->left == nullptr || neighbor->left->red == false) &&
                 (neighbor->right != nullptr && neighbor->right->red == true)) {
        neighbor->red = true;
        neighbor->right->red = false;
        RotateLeft(neighbor);
      }
    }
  }

  // Если отец и сосед одного цвета
  // тогда отца делаем черным, сына соседа делаем черным
  // поднимаем соседа на место отца
  void RaiseNeighbor(node_type *node) {
    node_type *neighbor = Neighbour(node);
    neighbor->red = node->parent->red;
    node->parent->red = false;
    if (node == node->parent->left) {
      neighbor->right->red = false;
      RotateLeft(node->parent);
    } else {
      neighbor->left->red = false;
      RotateRight(node->parent);
    }
  }

  // Балансировка:
  // Перекрашиваем отца в черный, дядя тоже должен быть черным, чтобы черная
  // высота у них совпадала Если дядя красный, тогда ...
  void TreeBalancing(node_type *node) {
    if (node->parent == nullptr)
      node->red = false;
    else if (node->parent->red == false)
      return;
    else
      RedUncle(node);
  }

  // Балансировка: Дядя то красный оказывается
  // Если дядя красный, тогда дядю перекрасим в черный.
  // Поскольку дядя черный, дед должен быть красным (если только не корень)
  // Поскольку дед красный, проверим отца деда, он должен быть черным
  // ->TreeBalancing Если дяди не существует тогда ...
  void RedUncle(node_type *node) {
    node_type *uncleNode = Uncle(node);
    node_type *grandparent;
    if ((uncleNode != nullptr) && (uncleNode->red == true)) {
      node->parent->red = false;
      uncleNode->red = false;
      grandparent = Grandpa(node);
      grandparent->red = true;
      TreeBalancing(grandparent);
    } else {
      Rotate(node);
    }
  }

  // Балансировка
  // Повороты
  void Rotate(node_type *node) {
    node_type *grandparent = Grandpa(node);

    // Если узел правый и отец левый, тогда правый поворот для отца
    // Если узел левый и отец правый, тогда левый поворот для отца
    if ((node == node->parent->right) && (node->parent == grandparent->left)) {
      RotateLeft(node->parent);
      node = node->left;
    } else if ((node == node->parent->left) &&
               (node->parent == grandparent->right)) {
      RotateRight(node->parent);
      node = node->right;
    }

    // Если узел левый и отец левый, тогда правый поворот для деда
    // Если узел правый и отец правый, тогда левый поворот для деда
    node->parent->red = false;
    grandparent->red = true;
    if ((node == node->parent->left) && (node->parent == grandparent->left)) {
      RotateRight(grandparent);
    } else {
      RotateLeft(grandparent);
    }
  }

  // Левый поворот
  // Правый сын узла поднимается на место узла
  // Переназначаем родителя, правого, левого сына
  void RotateLeft(node_type *node) {
    node_type *temp = node->right;
    temp->parent = node->parent;
    if (node->parent != nullptr) {
      if (node->parent->left == node)
        node->parent->left = temp;
      else
        node->parent->right = temp;
    }
    node->right = temp->left;
    if (temp->left != nullptr) temp->left->parent = node;
    node->parent = temp;
    temp->left = node;
    if (temp->parent == nullptr) header_ = temp;
  }

  // Правый поворот
  // Левый сын узла поднимается на место узла
  void RotateRight(node_type *node) {
    node_type *temp = node->left;
    temp->parent = node->parent;
    if (node->parent != nullptr) {
      if (node->parent->left == node)
        node->parent->left = temp;
      else
        node->parent->right = temp;
    }
    node->left = temp->right;
    if (temp->right != nullptr) temp->right->parent = node;
    node->parent = temp;
    temp->right = node;
    if (temp->parent == nullptr) header_ = temp;
  }

  TreeNode<TKey> *header_ = nullptr;
  size_type num_nodes_ = 0;
};

template <typename TTree>
class TreeConstIterator {
 public:
  using tree_type = TTree;
  using node_type = typename TTree::node_type;
  using key_type = typename TTree::key_type;
  using const_reference = const key_type &;

  template <typename TKey>
  friend class Tree;

  TreeConstIterator(node_type *node) : node_(node) {}

  bool operator==(const TreeConstIterator &second) const {
    return node_ == second.node_;
  }

  bool operator!=(const TreeConstIterator &second) const {
    return node_ != second.node_;
  }

  TreeConstIterator operator++(int) {
    TreeConstIterator temp(*this);
    ++(*this);
    return temp;
  }

  TreeConstIterator &operator++() {
    if (node_ != nullptr) {
      if (node_->right != nullptr) {
        node_ = tree_type::MinNode(node_->right);
      } else {
        while (node_->parent != nullptr && node_ == node_->parent->right) {
          node_ = node_->parent;
        }
        node_ = node_->parent;
      }
    }
    return *this;
  }

  TreeConstIterator operator--(int) {
    TreeConstIterator temp(*this);
    --(*this);
    return temp;
  }

  TreeConstIterator &operator--() {
    if (node_ != nullptr) {
      if (node_->left != nullptr) {
        node_ = tree_type::MaxNode(node_->left);
      } else {
        while (node_->parent != nullptr && node_ == node_->parent->left) {
          node_ = node_->parent;
        }
        node_ = node_->parent;
      }
    }
    return *this;
  }

  const_reference operator*() const {
    if (node_ != nullptr)
      return node_->key;
    else {
      static key_type empty_key = key_type{};
      return empty_key;
    }
  }

 protected:
  node_type *node_;
};

template <typename TTree>
class TreeIterator : public TreeConstIterator<TTree> {
 public:
  using tree_type = TreeConstIterator<TTree>;
  using node_type = typename TTree::node_type;
  using key_type = typename TTree::key_type;
  using reference = key_type &;

  template <typename TKey>
  friend class Tree;

  TreeIterator(node_type *node) : tree_type(node) {}

  reference operator*() const {
    return const_cast<reference>(tree_type::operator*());
  }

  TreeIterator &operator++() {
    tree_type::operator++();
    return *this;
  }

  TreeIterator &operator--() {
    tree_type::operator--();
    return *this;
  }

  TreeIterator operator++(int) {
    tree_type::operator++();
    return *this;
  }

  TreeIterator operator--(int) {
    tree_type::operator--();
    return *this;
  }

  bool operator==(const TreeIterator &second) const {
    return tree_type::operator==(second);
  }
  bool operator!=(const TreeIterator &second) const {
    return tree_type::operator!=(second);
  }
};

template <typename TKey>
class TreeNode {
 public:
  using node_type = TreeNode<TKey>;

  node_type *left, *right, *parent;
  bool red;
  TKey key;

  TreeNode()
      : left(nullptr), right(nullptr), parent(nullptr), red(false), key(0) {}

  TreeNode(TKey key)
      : left(nullptr), right(nullptr), parent(nullptr), red(false), key(key) {}

  TreeNode(TreeNode *node)
      : left(nullptr),
        right(nullptr),
        parent(nullptr),
        red(node->red),
        key(node->key) {}
};

}  // namespace 

#endif /* CONTAINERS_SRC_TREE_TREE_H_ */
