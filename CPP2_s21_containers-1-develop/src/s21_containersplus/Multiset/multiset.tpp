#include "multiset.h"

namespace s21 {
template <class Key>
Multiset<Key> &Multiset<Key>::operator=(Multiset &&other) noexcept {
  if (this != other) {
    this->root_ = this->nil_.get();
    swap(other);
    other.clear();
  }
  return *this;
}

template <class Key>
Multiset<Key> &Multiset<Key>::operator=(const Multiset &other) {
  if (this != other) {
    this->clear();
    this->root_ = copyTree(other.root_);
  }
  return *this;
}

template <class Key>
typename Multiset<Key>::size_type Multiset<Key>::Count(const Key &key) const {
  size_type count = 0;
  iterator iter = this->Begin();
  while (iter != this->End()) {
    if (*iter == key) ++count;
    ++iter;
  }
  return count;
}

template <class Key>
typename Multiset<Key>::iterator Multiset<Key>::LowerBound(
    const Key &key) const {
  iterator iter = this->Begin();
  while (iter != this->End()) {
    if (*iter >= key) return iter;
    ++iter;
  }
  return iter;
}

template <class Key>
typename Multiset<Key>::iterator Multiset<Key>::UpperBound(
    const Key &key) const {
  iterator iter = this->Begin();
  while (iter != this->End()) {
    if (*iter > key) return iter;
    ++iter;
  }
  return iter;
}

template <class Key>
std::pair<typename Multiset<Key>::iterator, typename Multiset<Key>::iterator>
Multiset<Key>::EqualRange(const Key &key) const {
  return std::pair<iterator, iterator>(LowerBound(key), UpperBound(key));
}
}  // namespace s21