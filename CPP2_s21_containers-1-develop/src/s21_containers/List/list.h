#ifndef SRC_S21_CONTAINERS_LIST_LIST_H
#define SRC_S21_CONTAINERS_LIST_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <class T>
class List {
 public:
  List();
  List(size_t n);
  List(std::initializer_list<T> const &items);
  List(const List &l);
  List(List &&l) noexcept;
  ~List();

 private:
  class ListIterator;
  class ListConstIterator;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;

  List &operator=(const List &l);
  List &operator=(List &&l) noexcept;

  const_reference Front() const;
  const_reference Back() const;

  iterator Begin() const;
  iterator End() const;

  bool Empty() const;
  size_type Size() const;
  size_type MaxSize() const;

  void Clear();
  void PushBack(const_reference value);
  void PushFront(const_reference value);
  void PopFront();
  void PopBack();
  iterator Insert(iterator pos, const_reference value);
  void Erase(iterator pos);
  void Swap(List &other);
  void Merge(List &other);
  void Splice(const_iterator pos, List &other);
  void Reverse();
  void Unique();
  void Sort();
  template <class... Args>
  iterator InsertMany(const_iterator pos, Args &&...args);
  template <class... Args>
  void InsertManyBack(Args &&...args);
  template <class... Args>
  void InsertManyFront(Args &&...args);

 private:
  class Node {
   public:
    value_type data_;
    Node *ptr_next_;
    Node *ptr_prev_;
    Node(value_type data = value_type(), Node *ptr_next = nullptr,
         Node *ptr_prev = nullptr);
  };

  class ListIterator {
   public:
    Node *ptr_;
    ListIterator();
    ListIterator(Node *ptr);
    ListIterator(const iterator &other);

    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    reference operator*();
    iterator &operator++();
    iterator operator++(int value);
    iterator operator+(int value);
    iterator &operator--();
    iterator operator--(int value);
    iterator operator-(int value);
    iterator &operator=(const iterator other);
  };
  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator();
    ListConstIterator(Node *ptr);
    ListConstIterator(const const_iterator &other);
    ListConstIterator(const iterator &other);
  };

  Node *head_;
  Node *tail_;
  Node *fict_;
  int size_;

  void InitHeadTail(value_type data);
  void InitList();
  void Rewrite(int key);
  void CopyObject(const List &l);
  void MoveObject(List &l);
  bool FindIterator(ListIterator it);
};

}  // namespace s21

#include "list.tpp"
#endif  //  SRC_S21_CONTAINERS_LIST_LIST_H