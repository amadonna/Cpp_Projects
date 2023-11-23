#include "red_black_tree.h"

namespace s21 {
template <typename Key, typename Value, typename Compare>
std::unique_ptr<typename RedBlackTree<Key, Value, Compare>::Node>
    RedBlackTree<Key, Value, Compare>::nil_ = std::make_unique<Node>();

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::Node *
RedBlackTree<Key, Value, Compare>::MinValue(Node *node) {
  if (node == nil_.get()) return node;
  while (node->left_ != nil_.get()) {
    node = node->left_;
  }
  return node;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::Node *
RedBlackTree<Key, Value, Compare>::MaxValue(Node *node) {
  if (node == nil_.get()) return node;
  while (node->right_ != nil_.get()) {
    node = node->right_;
  }
  return node;
}

template <class Key, class Value, class Compare>
bool RedBlackTree<Key, Value, Compare>::ConstIterator::operator!=(
    const ConstIterator &other) const {
  return node_ != other.node_;
}

template <class Key, class Value, class Compare>
bool RedBlackTree<Key, Value, Compare>::ConstIterator::operator==(
    const ConstIterator &other) const {
  return node_ == other.node_;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::ConstIterator &
RedBlackTree<Key, Value, Compare>::ConstIterator::operator++() {
  if (node_ == nil_.get() && past_node_ != nil_.get()) {
    std::swap(node_, past_node_);
  } else {
    past_node_ = node_;
    node_ = NextValue();
  }
  return *this;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::ConstIterator
RedBlackTree<Key, Value, Compare>::ConstIterator::operator++(int) {
  ConstIterator iter = *this;
  ++(*this);
  return iter;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::ConstIterator &
RedBlackTree<Key, Value, Compare>::ConstIterator::operator--() {
  if (node_ == nil_.get() && past_node_ != nil_.get()) {
    std::swap(node_, past_node_);
  } else {
    past_node_ = node_;
    node_ = PrevValue();
  }
  return *this;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::ConstIterator
RedBlackTree<Key, Value, Compare>::ConstIterator::operator--(int) {
  ConstIterator iter = *this;
  --(*this);
  return iter;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::const_reference
RedBlackTree<Key, Value, Compare>::ConstIterator::operator*() {
  return node_->value_;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::Node *
RedBlackTree<Key, Value, Compare>::ConstIterator::NextValue() {
  Node *node = node_;
  if (node->right_ != nil_.get()) return MinValue(node->right_);
  Node *temp = node->parent_;
  while (temp != nil_.get() && node == temp->right_) {
    node = temp;
    temp = temp->parent_;
  }
  return temp;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::Node *
RedBlackTree<Key, Value, Compare>::ConstIterator::PrevValue() {
  Node *node = node_;
  if (node->left_ != nil_.get()) return MaxValue(node->left_);
  Node *temp = node->parent_;
  while (temp != nil_.get() && node == temp->left_) {
    node = temp;
    temp = temp->parent_;
  }
  return temp;
}

template <class Key, class Value, class Compare>
RedBlackTree<Key, Value, Compare>::RedBlackTree() {
  root_ = nil_.get();
}

template <class Key, class Value, class Compare>
RedBlackTree<Key, Value, Compare>::RedBlackTree(
    std::initializer_list<value_type> const &items) {
  root_ = nil_.get();
  for (value_type item : items) Insert(item);
}

template <class Key, class Value, class Compare>
RedBlackTree<Key, Value, Compare>::RedBlackTree(const RedBlackTree &other) {
  root_ = CopyTree(other.root_);
}

template <class Key, class Value, class Compare>
RedBlackTree<Key, Value, Compare> &RedBlackTree<Key, Value, Compare>::operator=(
    const RedBlackTree &other) {
  if (this != other) {
    root_ = CopyTree(other.root_);
  }
  return *this;
}

template <class Key, class Value, class Compare>
RedBlackTree<Key, Value, Compare>::RedBlackTree(RedBlackTree &&other) noexcept {
  root_ = nil_.get();
  Swap(other);
}

template <class Key, class Value, class Compare>
RedBlackTree<Key, Value, Compare> &RedBlackTree<Key, Value, Compare>::operator=(
    RedBlackTree &&other) noexcept {
  if (this != other) {
    Clear();
    Swap(other);
  }
  return *this;
}

template <class Key, class Value, class Compare>
RedBlackTree<Key, Value, Compare>::~RedBlackTree() {
  Clear();
  root_ = nullptr;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::Node *
RedBlackTree<Key, Value, Compare>::CopyTree(Node *node, Node *parent) {
  if (node == nil_.get()) {
    return nil_.get();
  }
  Node *new_parent = new Node(node->key_, node->value_, node->color_, parent);
  new_parent->left_ = CopyTree(node->left_, new_parent);
  new_parent->right_ = CopyTree(node->right_, new_parent);
  return new_parent;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::iterator
RedBlackTree<Key, Value, Compare>::Begin() const {
  return Iterator(MinValue(root_));
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::iterator
RedBlackTree<Key, Value, Compare>::End() const {
  if (root_ == nil_.get()) return Begin();
  Iterator iter(MaxValue(root_));
  ++iter;
  return Iterator(iter);
}

template <class Key, class Value, class Compare>
bool RedBlackTree<Key, Value, Compare>::Empty() const {
  return Size() == 0;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::size_type
RedBlackTree<Key, Value, Compare>::Size() const {
  size_type count = 0;
  iterator iter = Begin();
  iterator iter_end = End();
  while (iter != iter_end) {
    ++count;
    ++iter;
  }
  return count;
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::size_type
RedBlackTree<Key, Value, Compare>::MaxSize() const {
  return std::min<size_type>(std::allocator<Node>().max_size(),
                             std::numeric_limits<difference_type>::max());
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::Clear() {
  if (root_ != nil_.get()) {
    MakeClearTree(root_);
    root_ = nil_.get();
  }
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::MakeClearTree(Node *node) {
  if (node != nil_.get()) {
    MakeClearTree(node->left_);
    MakeClearTree(node->right_);
    delete node;
  }
}

template <class Key, class Value, class Compare>
std::pair<typename RedBlackTree<Key, Value, Compare>::Iterator, bool>
RedBlackTree<Key, Value, Compare>::Insert(const value_type &value) {
  Node *current_node = root_;
  Node *parent = nil_.get();
  while (current_node != nil_.get()) {
    parent = current_node;
    if (compare_(parent->key_, value))
      current_node = current_node->right_;
    else if (compare_(value, parent->key_))
      current_node = current_node->left_;
    else
      return std::pair<Iterator, bool>(Find(parent->key_), false);
  }
  Node *new_node = new Node(value);
  new_node->parent_ = parent;
  if (parent == nil_.get())
    root_ = new_node;
  else if (compare_(parent->key_, value))
    parent->right_ = new_node;
  else
    parent->left_ = new_node;
  BalanceAfterInsert(new_node);
  return std::pair<Iterator, bool>(Find(new_node->key_), true);
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::BalanceAfterInsert(Node *node) {
  Node *uncle;
  while (node != root_ && node->parent_->color_ == RED) {
    if (node->parent_ == node->parent_->parent_->left_) {
      uncle = node->parent_->parent_->right_;
      if (uncle->color_ == RED) {
        node->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        node = node->parent_->parent_;
      } else {
        if (node == node->parent_->right_) {
          node = node->parent_;
          LeftRotate(node);
        }
        node->parent_->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        RightRotate(node->parent_->parent_);
      }
    } else {
      uncle = node->parent_->parent_->left_;
      if (uncle->color_ == RED) {
        node->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        node = node->parent_->parent_;
      } else {
        if (node == node->parent_->left_) {
          node = node->parent_;
          RightRotate(node);
        }
        node->parent_->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        LeftRotate(node->parent_->parent_);
      }
    }
  }
  root_->color_ = BLACK;
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::Erase(iterator pos) {
  Node *data = pos.node_;
  if (data != nil_.get()) {
    Node *node;
    if (data->right_ == nil_.get() || data->left_ == nil_.get()) {
      node = data;
    } else {
      ++pos;
      node = pos.node_;
    }
    Node *child = (node->left_ != nil_.get()) ? node->left_ : node->right_;
    child->parent_ = node->parent_;
    if (node->parent_ == nil_.get()) {
      root_ = child;
    } else {
      if (node == node->parent_->left_)
        node->parent_->left_ = child;
      else
        node->parent_->right_ = child;
    }
    if (node != data) {
      data->value_ = node->value_;
      data->key_ = node->key_;
    }
    if (node->color_ == BLACK) BalanceAfterErase(child);
    delete node;
  }
  nil_->parent_ = nullptr;
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::BalanceAfterErase(Node *node) {
  while (node != root_ && node->color_ == BLACK) {
    node == node->parent_->left_ ? BalanceAfterEraseLeft(node)
                                 : BalanceAfterEraseRight(node);
  }
  node->color_ = BLACK;
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::BalanceAfterEraseLeft(Node *&node) {
  Node *brother = node->parent_->right_;
  if (brother->color_ == RED) {
    brother->color_ = BLACK;
    node->parent_->color_ = RED;
    LeftRotate(node->parent_);
    brother = node->parent_->right_;
  }
  if (brother->left_->color_ == BLACK && brother->right_->color_ == BLACK) {
    brother->color_ = RED;
    node = node->parent_;
  } else {
    if (brother->right_->color_ == BLACK) {
      brother->left_->color_ = BLACK;
      brother->color_ = RED;
      RightRotate(brother);
      brother = node->parent_->right_;
    }
    brother->color_ = node->parent_->color_;
    node->parent_->color_ = BLACK;
    brother->right_->color_ = BLACK;
    LeftRotate(node->parent_);
    node = root_;
  }
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::BalanceAfterEraseRight(Node *&node) {
  Node *brother = node->parent_->left_;
  if (brother->color_ == RED) {
    brother->color_ = BLACK;
    node->parent_->color_ = RED;
    RightRotate(node->parent_);
    brother = node->parent_->left_;
  }
  if (brother->left_->color_ == BLACK && brother->right_->color_ == BLACK) {
    brother->color_ = RED;
    node = node->parent_;
  } else {
    if (brother->left_->color_ == BLACK) {
      brother->right_->color_ = BLACK;
      brother->color_ = RED;
      LeftRotate(brother);
      brother = node->parent_->left_;
    }
    brother->color_ = node->parent_->color_;
    node->parent_->color_ = BLACK;
    brother->left_->color_ = BLACK;
    RightRotate(node->parent_);
    node = root_;
  }
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::RightRotate(Node *node) {
  Node *buffer = node->left_;
  node->left_ = buffer->right_;
  if (buffer->right_ != nil_.get()) buffer->right_->parent_ = node;
  buffer->parent_ = node->parent_;
  if (node->parent_ == nil_.get()) {
    root_ = buffer;
  } else {
    if (node == node->parent_->right_) {
      node->parent_->right_ = buffer;
    } else {
      node->parent_->left_ = buffer;
    }
  }
  buffer->right_ = node;
  node->parent_ = buffer;
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::LeftRotate(Node *node) {
  Node *buffer = node->right_;
  node->right_ = buffer->left_;
  if (buffer->left_ != nil_.get()) buffer->left_->parent_ = node;
  buffer->parent_ = node->parent_;
  if (node->parent_ == nil_.get()) {
    root_ = buffer;
  } else {
    if (node == node->parent_->left_) {
      node->parent_->left_ = buffer;
    } else {
      node->parent_->right_ = buffer;
    }
  }
  buffer->left_ = node;
  node->parent_ = buffer;
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::Swap(RedBlackTree &other) {
  std::swap(root_, other.root_);
}

template <class Key, class Value, class Compare>
void RedBlackTree<Key, Value, Compare>::Merge(RedBlackTree &other) {
  if (root_ == nil_.get())
    Swap(other);
  else {
    Iterator iter = other.Begin();
    Iterator next_iter = other.Begin();
    while (iter != other.End()) {
      ++next_iter;
      std::pair<Iterator, bool> result_insert = Insert(iter.node_->value_);
      if (result_insert.second) other.Erase(iter);
      iter = next_iter;
    }
  }
}

template <class Key, class Value, class Compare>
typename RedBlackTree<Key, Value, Compare>::iterator
RedBlackTree<Key, Value, Compare>::Find(const Key &key) const {
  Node *current_node = root_;
  while (current_node != nil_.get() && current_node->key_ != key) {
    current_node =
        (key < current_node->key_) ? current_node->left_ : current_node->right_;
  }
  return Iterator(current_node);
}

template <class Key, class Value, class Compare>
bool RedBlackTree<Key, Value, Compare>::Contains(const Key &key) const {
  return Find(key).node_ != nil_.get();
}

template <class Key, class Value, class Compare>
template <class... Args>
std::vector<
    std::pair<typename RedBlackTree<Key, Value, Compare>::iterator, bool>>
RedBlackTree<Key, Value, Compare>::InsertMany(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;
  value_type arr[] = {args...};
  for (value_type element : arr) result.push_back(Insert(element));
  return result;
}
}  // namespace s21