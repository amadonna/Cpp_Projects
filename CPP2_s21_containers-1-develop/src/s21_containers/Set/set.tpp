#include "set.h"

namespace s21 {
template <class Key>
Set<Key> &Set<Key>::operator=(Set &&other) noexcept {
  if (this != other) {
    this->root_ = this->nil_.get();
    swap(other);
    other.clear();
  }
  return *this;
}

template <class Key>
Set<Key> &Set<Key>::operator=(const Set &other) {
  if (this != other) {
    this->clear();
    this->root_ = copyTree(other.root_);
  }
  return *this;
}
}  // namespace s21