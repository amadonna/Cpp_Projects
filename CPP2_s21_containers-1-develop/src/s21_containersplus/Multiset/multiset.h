#ifndef SRC_S21_CONTAINERSPLUS_MULTISET_MULTISET_H
#define SRC_S21_CONTAINERSPLUS_MULTISET_MULTISET_H
#include "../../s21_containers/RedBlackTree/red_black_tree.h"

namespace s21 {
template <class Key>
class Multiset : public RedBlackTree<Key, Key, std::less_equal<Key>> {
 public:
  using key_type = Key;
  using value_type = Key;
  using referance = value_type &;
  using const_referance = const value_type &;
  using iterator =
      typename RedBlackTree<Key, Key, std::less_equal<Key>>::Iterator;
  using const_iterator =
      typename RedBlackTree<Key, Key, std::less_equal<Key>>::ConstIterator;
  using size_type = std::size_t;

  Multiset() : RedBlackTree<Key, Key, std::less_equal<Key>>(){};
  Multiset(std::initializer_list<value_type> const &items)
      : RedBlackTree<Key, Key, std::less_equal<Key>>(items){};
  Multiset(const Multiset &other)
      : RedBlackTree<Key, Key, std::less_equal<Key>>(other){};
  Multiset &operator=(const Multiset &other);
  Multiset(Multiset &&other) noexcept
      : RedBlackTree<Key, Key, std::less_equal<Key>>(std::move(other)){};
  Multiset &operator=(Multiset &&other) noexcept;
  ~Multiset() = default;

  size_type Count(const Key &key) const;
  std::pair<iterator, iterator> EqualRange(const Key &key) const;
  iterator LowerBound(const Key &key) const;
  iterator UpperBound(const Key &key) const;
};
}  // namespace s21
#include "multiset.tpp"
#endif  // SRC_S21_CONTAINERSPLUS_MULTISET_MULTISET_H
