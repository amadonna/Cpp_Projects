#ifndef SRC_S21_CONTAINERS_SET_SET_H
#define SRC_S21_CONTAINERS_SET_SET_H
#include "../RedBlackTree/red_black_tree.h"

namespace s21 {
template <class Key>
class Set : public RedBlackTree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using referance = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RedBlackTree<Key>::Iterator;
  using const_iterator = typename RedBlackTree<Key>::ConstIterator;
  using size_type = std::size_t;

  Set() : RedBlackTree<Key>(){};
  Set(std::initializer_list<value_type> const &items)
      : RedBlackTree<Key>(items){};
  Set(const Set &other) : RedBlackTree<Key>(other){};
  Set &operator=(const Set &other);
  Set(Set &&other) noexcept : RedBlackTree<Key>(std::move(other)){};
  Set &operator=(Set &&other) noexcept;
  ~Set() = default;
};
}  // namespace s21
#include "set.tpp"
#endif  // SRC_S21_CONTAINERS_SET_SET_H
