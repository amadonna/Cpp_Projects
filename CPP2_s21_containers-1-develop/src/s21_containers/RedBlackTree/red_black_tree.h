#ifndef SRC_S21_CONTAINERS_RED_BLACK_TREE_RED_BLACK_TREE_H
#define SRC_S21_CONTAINERS_RED_BLACK_TREE_RED_BLACK_TREE_H
#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

namespace s21 {
template <class Key, class Value>
class Map;
template <class Key, class Value = Key, class Compare = std::less<Key>>
class RedBlackTree {
  enum Color { BLACK, RED };

 public:
  struct Node;
  struct ConstIterator;
  struct Iterator;
  using key_type = Key;
  using value_type = Value;
  using referance = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  struct Node {
   public:
    Node() = default;
    explicit Node(Value value)
        : key_(value),
          value_(value),
          color_(RED),
          left_(nil_.get()),
          right_(nil_.get()),
          parent_(nil_.get()){};
    Node(Key key, Value value)
        : key_(key),
          value_(value),
          color_(RED),
          left_(nil_.get()),
          right_(nil_.get()),
          parent_(nil_.get()){};
    Node(Key key, Value value, Color color, Node *parent)
        : key_(key),
          value_(value),
          color_(color),
          left_(nil_.get()),
          right_(nil_.get()),
          parent_(parent){};

   protected:
    Key key_;
    Value value_;
    Color color_ = BLACK;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
    Node *parent_ = nullptr;

    friend class RedBlackTree<Key, Value, Compare>;
    friend class Map<Key, Value>;
  };

  struct ConstIterator {
   public:
    ConstIterator() = default;
    explicit ConstIterator(Node *node)
        : node_(node), past_node_(node->parent_){};
    bool operator!=(const const_iterator &other) const;
    bool operator==(const const_iterator &other) const;
    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);
    const Value &operator*();

   private:
    Node *NextValue();
    Node *PrevValue();

   protected:
    Node *node_ = nil_.get();
    Node *past_node_ = nil_.get();

    friend class RedBlackTree<Key, Value, Compare>;
    friend class Map<Key, Value>;
  };

  struct Iterator : ConstIterator {
   public:
    Iterator() : ConstIterator(){};
    explicit Iterator(Node *node) : ConstIterator(node){};
  };

  RedBlackTree();
  RedBlackTree(std::initializer_list<value_type> const &items);
  RedBlackTree(const RedBlackTree &other);
  RedBlackTree &operator=(const RedBlackTree &other);
  RedBlackTree(RedBlackTree &&other) noexcept;
  RedBlackTree &operator=(RedBlackTree &&other) noexcept;
  ~RedBlackTree();

  iterator Begin() const;
  iterator End() const;

  bool Empty() const;
  size_type Size() const;
  size_type MaxSize() const;

  void Clear();
  std::pair<iterator, bool> Insert(const_reference value);
  void Erase(iterator pos);
  void Swap(RedBlackTree &other);
  void Merge(RedBlackTree &other);

  iterator Find(const Key &key) const;
  bool Contains(const Key &key) const;

  template <class... Args>
  std::vector<std::pair<iterator, bool>> InsertMany(Args &&...args);

 private:
  Node *CopyTree(Node *node, Node *new_parent = nil_.get());
  void BalanceAfterErase(Node *node);
  void BalanceAfterEraseLeft(Node *&node);
  void BalanceAfterEraseRight(Node *&node);
  void RightRotate(Node *node);
  void LeftRotate(Node *node);
  void MakeClearTree(Node *node);

 protected:
  static std::unique_ptr<Node> nil_;
  Node *root_;
  Compare compare_ = Compare();
  void BalanceAfterInsert(Node *node);
  static Node *MinValue(Node *node);
  static Node *MaxValue(Node *node);
};
}  // namespace s21

#include "red_black_tree.tpp"
#endif  // SRC_S21_CONTAINERS_RED_BLACK_TREE_RED_BLACK_TREE_H
