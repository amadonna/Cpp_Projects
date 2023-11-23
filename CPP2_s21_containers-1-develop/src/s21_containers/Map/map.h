#ifndef SRC_S21_CONTAINERS_MAP_MAP_H
#define SRC_S21_CONTAINERS_MAP_MAP_H
#include "../RedBlackTree/red_black_tree.h"

namespace s21 {
template <class Key, class T>
class Map : public RedBlackTree<Key, T> {
 public:
  struct ConstIteratorMap;
  struct IteratorMap;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = IteratorMap;
  using const_iterator = ConstIteratorMap;
  using size_type = std::size_t;
  using node_type = typename RedBlackTree<Key, T>::Node;

  struct ConstIteratorMap : RedBlackTree<Key, T>::ConstIterator {
    ConstIteratorMap() : RedBlackTree<Key, T>::ConstIterator(){};
    explicit ConstIteratorMap(node_type *node)
        : RedBlackTree<Key, T>::ConstIterator(node){};
    value_type operator*();
  };

  struct IteratorMap : ConstIteratorMap {
    IteratorMap() : ConstIteratorMap(){};
    explicit IteratorMap(node_type *node) : ConstIteratorMap(node){};
  };

  Map() : RedBlackTree<key_type, mapped_type>(){};
  Map(std::initializer_list<value_type> const &items);
  Map(const Map &m) : RedBlackTree<key_type, mapped_type>(m){};
  Map &operator=(const Map &other);
  Map(Map &&m) noexcept : RedBlackTree<key_type, mapped_type>(std::move(m)){};
  Map &operator=(Map &&other) noexcept;
  ~Map() = default;

  T &At(const Key &key);
  T &operator[](const Key &key);

  iterator Begin() const;
  iterator End() const;

  std::pair<iterator, bool> Insert(const_reference value);
  std::pair<iterator, bool> Insert(const Key &key, const T &obj);
  std::pair<iterator, bool> InsertOrAssign(const Key &key, const T &obj);

  void Erase(iterator pos);
  void Merge(Map &other);

 private:
  iterator Find(const Key &key);
};

}  // namespace s21

#include "map.tpp"
#endif  // SRC_S21_CONTAINERS_MAP_MAP_H
