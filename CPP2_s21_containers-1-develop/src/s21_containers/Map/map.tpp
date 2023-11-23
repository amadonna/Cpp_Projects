#include "map.h"

namespace s21 {

template <class Key, class T>
typename Map<Key, T>::value_type Map<Key, T>::ConstIteratorMap::operator*() {
  return std::pair<Key, T>(this->node_->key_, this->node_->value_);
}

template <class Key, class T>
Map<Key, T> &Map<Key, T>::operator=(Map &&other) noexcept {
  if (this != other) {
    this->root_ = this->nil_.get();
    swap(other);
    other.clear();
  }
  return *this;
}

template <class Key, class T>
Map<Key, T> &Map<Key, T>::operator=(const Map &other) {
  if (this != other) {
    this->clear();
    this->root_ = copyTree(other.root_);
  }
  return *this;
}

template <class Key, class T>
Map<Key, T>::Map(std::initializer_list<value_type> const &items) {
  this->root_ = this->nil_.get();
  for (value_type item : items) Insert(item.first, item.second);
}

template <class Key, class T>
T &Map<Key, T>::At(const Key &key) {
  node_type *node = Find(key).node_;
  if (node == this->nil_.get()) throw std::out_of_range("Map::at");
  return node->value_;
}

template <class Key, class T>
T &Map<Key, T>::operator[](const Key &key) {
  node_type *node = Find(key).node_;
  return node->value_;
}

template <class Key, class T>
typename Map<Key, T>::iterator Map<Key, T>::Begin() const {
  return IteratorMap(this->MinValue(this->root_));
}

template <class Key, class T>
typename Map<Key, T>::iterator Map<Key, T>::End() const {
  if (this->root_ == this->nil_.get()) return Begin();
  iterator iter(this->MaxValue(this->root_));
  ++iter;
  return IteratorMap(iter);
}

template <class Key, class T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert(
    const value_type &value) {
  return Insert(value.first, value.second);
}

template <class Key, class T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert(
    const Key &key, const T &obj) {
  node_type *current_node = this->root_;
  node_type *parent = this->nil_.get();
  while (current_node != this->nil_.get()) {
    parent = current_node;
    if (this->compare_(parent->key_, key))
      current_node = current_node->right_;
    else if (this->compare_(key, parent->key_))
      current_node = current_node->left_;
    else
      return std::pair<iterator, bool>(this->Find(parent->key_), false);
  }
  node_type *new_node = new node_type(key, obj);
  new_node->parent_ = parent;
  if (parent == this->nil_.get())
    this->root_ = new_node;
  else if (this->compare_(parent->key_, key))
    parent->right_ = new_node;
  else
    parent->left_ = new_node;
  this->BalanceAfterInsert(new_node);
  return std::pair<iterator, bool>(Find(new_node->key_), true);
}

template <class Key, class T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::InsertOrAssign(
    const Key &key, const T &obj) {
  node_type *current_node = this->root_;
  node_type *parent = this->nil_.get();
  while (current_node != this->nil_.get()) {
    parent = current_node;
    if (this->compare_(parent->key_, key))
      current_node = current_node->right_;
    else if (this->compare_(key, parent->key_))
      current_node = current_node->left_;
    else {
      current_node->value_ = obj;
      return std::pair<iterator, bool>(Find(current_node->key_), false);
    }
  }
  node_type *new_node = new node_type(key, obj);
  new_node->parent_ = parent;
  if (parent == this->nil_.get())
    this->root_ = new_node;
  else if (this->compare_(parent->key_, key))
    parent->right_ = new_node;
  else
    parent->left_ = new_node;
  this->BalanceAfterInsert(new_node);
  return std::pair<iterator, bool>(Find(new_node->key_), true);
}

template <class Key, class T>
typename Map<Key, T>::iterator Map<Key, T>::Find(const Key &key) {
  node_type *current_node = this->root_;
  while (current_node != this->nil_.get() && current_node->key_ != key) {
    current_node =
        (key < current_node->key_) ? current_node->left_ : current_node->right_;
  }
  return IteratorMap(current_node);
}

template <class Key, class T>
void Map<Key, T>::Erase(iterator pos) {
  typename RedBlackTree<Key, T>::iterator it;
  it.node_ = pos.node_;
  it.past_node_ = pos.past_node_;
  RedBlackTree<Key, T>::Erase(it);
}

template <class Key, class T>
void Map<Key, T>::Merge(Map &other) {
  if (this->root_ == this->nil_.get())
    RedBlackTree<Key, T>::Swap(other);
  else {
    iterator iter = other.Begin();
    iterator next_iter = other.Begin();
    while (iter != other.End()) {
      ++next_iter;
      std::pair<iterator, bool> result_insert =
          Insert(iter.node_->key_, iter.node_->value_);
      if (result_insert.second) other.Erase(iter);
      iter = next_iter;
    }
  }
}
}  // namespace s21