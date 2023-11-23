#include "list.h"

namespace s21 {

template <class value_type>
List<value_type>::List() : head_(nullptr), tail_(nullptr), fict_(nullptr) {
  InitList();
}

template <class value_type>
List<value_type>::List(size_type n)
    : head_(nullptr), tail_(nullptr), fict_(nullptr) {
  InitList();
  for (size_type i = 0; i < n; i++) {
    PushFront(value_type());
  }
}

template <class value_type>
List<value_type>::List(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), fict_(nullptr) {
  for (auto data : items) {
    PushBack(data);
  }
}

template <class value_type>
List<value_type>::List(const List &l) {
  InitList();
  CopyObject(l);
}

template <class value_type>
List<value_type>::List(List &&l) noexcept {
  InitList();
  MoveObject(l);
}

template <class value_type>
List<value_type>::~List() {
  Clear();
  delete fict_;
}

template <class value_type>
List<value_type> &List<value_type>::operator=(const List &l) {
  if (this != &l) {
    CopyObject(l);
  }
  return *this;
}

template <class value_type>
List<value_type> &List<value_type>::operator=(List &&l) noexcept {
  if (this != &l) {
    MoveObject(l);
  }
  return *this;
}

template <class value_type>
void List<value_type>::CopyObject(const List &l) {
  Clear();
  Node *current = l.tail_;
  int count = l.size_;
  while (count > 0) {
    PushFront(current->data_);
    current = current->ptr_prev_;
    count--;
  }
}

template <class value_type>
void List<value_type>::MoveObject(List &l) {
  Clear();
  while (l.size_ > 0) {
    PushFront(l.tail_->data_);
    l.PopBack();
  }
  l.head_ = l.tail_ = nullptr;
}

template <class value_type>
List<value_type>::Node::Node(value_type data, Node *ptr_next, Node *ptr_prev)
    : data_(data), ptr_next_(ptr_next), ptr_prev_(ptr_prev) {}

template <class value_type>
List<value_type>::ListIterator::ListIterator() : ptr_(nullptr) {}

template <class value_type>
List<value_type>::ListIterator::ListIterator(Node *ptr) : ptr_(ptr) {}

template <class value_type>
List<value_type>::ListIterator::ListIterator(const iterator &other)
    : ptr_(other.ptr_) {}

template <class value_type>
bool List<value_type>::ListIterator::operator==(const iterator &other) const {
  return ptr_ == other.ptr_ ? true : false;
}

template <class value_type>
bool List<value_type>::ListIterator::operator!=(const iterator &other) const {
  return ptr_ != other.ptr_ ? true : false;
}

template <class value_type>
typename List<value_type>::reference
List<value_type>::ListIterator::operator*() {
  return ptr_->data_;
}

template <class value_type>
typename List<value_type>::iterator &
List<value_type>::ListIterator::operator++() {
  if (ptr_ != nullptr) {
    ptr_ = ptr_->ptr_next_;
  }
  return *this;
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::ListIterator::operator++(
    int value) {
  (void)value;
  iterator temp(*this);
  if (ptr_ != nullptr) {
    ptr_ = ptr_->ptr_next_;
  }
  return temp;
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::ListIterator::operator+(
    int value) {
  for (int i = 0; i < value; ++i) {
    ptr_ = ptr_->ptr_next_;
  }
  return *this;
}

template <class value_type>
typename List<value_type>::iterator &
List<value_type>::ListIterator::operator--() {
  if (ptr_ != nullptr) {
    ptr_ = ptr_->ptr_prev_;
  }
  return *this;
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::ListIterator::operator--(
    int value) {
  iterator temp(*this);
  if (ptr_ != nullptr) {
    ptr_ = ptr_->ptr_prev_;
  }
  return temp;
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::ListIterator::operator-(
    int value) {
  for (int i = 0; i < value; ++i) {
    ptr_ = ptr_->ptr_prev_;
  }
  return *this;
}

template <class value_type>
typename List<value_type>::iterator &List<value_type>::ListIterator::operator=(
    const iterator other) {
  ptr_ = other.ptr_;
  return *this;
}

template <class value_type>
List<value_type>::ListConstIterator::ListConstIterator() : ListIterator() {}

template <class value_type>
List<value_type>::ListConstIterator::ListConstIterator(Node *ptr)
    : ListIterator(ptr) {}

template <class value_type>
List<value_type>::ListConstIterator::ListConstIterator(
    const const_iterator &other)
    : ListIterator(other) {}

template <class value_type>
List<value_type>::ListConstIterator::ListConstIterator(const iterator &other)
    : ListIterator(other) {}

template <class value_type>
typename List<value_type>::const_reference List<value_type>::Front() const {
  auto iter = Begin();
  return *iter;
}

template <class value_type>
typename List<value_type>::const_reference List<value_type>::Back() const {
  auto iter = End();
  return *(--iter);
}

template <class value_type>
void List<value_type>::PushBack(const_reference value) {
  int key = 0;
  if (head_ == nullptr) {
    InitHeadTail(value);
  } else {
    key = 2;
    Node *current = tail_;
    tail_->ptr_next_ = new Node(value, fict_, current);
    tail_ = tail_->ptr_next_;
  }
  Rewrite(key);
}

template <class value_type>
void List<value_type>::PushFront(const_reference value) {
  int key = 0;
  if (head_ == nullptr) {
    InitHeadTail(value);
  } else {
    key = 1;
    Node *current = head_;
    current->ptr_prev_ = new Node(value, current);
    head_ = current->ptr_prev_;
  }
  Rewrite(key);
}

template <class value_type>
bool List<value_type>::Empty() const {
  return fict_->ptr_next_ == fict_;
}

template <class value_type>
void List<value_type>::PopFront() {
  if (size_ > 0) {
    Node *temp = fict_->ptr_next_;
    fict_->ptr_next_ = fict_->ptr_next_->ptr_next_;
    fict_->ptr_next_->ptr_prev_ = fict_;
    delete temp;
    --size_;
  }
}

template <class value_type>
void List<value_type>::PopBack() {
  if (size_ > 0) {
    Node *temp = tail_;
    tail_ = tail_->ptr_prev_;
    tail_->ptr_next_ = fict_;
    fict_->ptr_prev_ = tail_;
    delete temp;
    --size_;
  }
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::Insert(
    iterator pos, const_reference value) {
  Node *current_node = pos.ptr_;
  Node *prev_node = current_node->ptr_prev_;
  Node *new_node = new Node(value);
  new_node->ptr_next_ = current_node;
  new_node->ptr_prev_ = current_node->ptr_prev_;
  current_node->ptr_prev_ = new_node;
  prev_node->ptr_next_ = new_node;
  ++size_;
  tail_ = fict_->ptr_prev_;
  head_ = fict_->ptr_next_;
  return iterator(new_node);
}

template <class value_type>
void List<value_type>::Erase(iterator pos) {
  if (pos == Begin()) {
    PopFront();
  } else {
    if (pos != End()) {
      Node *current_node = pos.ptr_;
      Node *prev_node = current_node->ptr_prev_;
      Node *next_node = current_node->ptr_next_;
      prev_node->ptr_next_ = next_node;
      next_node->ptr_prev_ = prev_node;
      delete current_node;
      --size_;
    }
  }
}

template <class value_type>
void List<value_type>::Swap(List &other) {
  if (this != &other) {
    List<value_type> copy(other);
    other = std::move(*this);
    MoveObject(copy);
  }
}

template <class value_type>
void List<value_type>::Merge(List &other) {
  if (this != &other) {
    auto iter = Begin();
    auto iter2 = other.Begin();
    while (other.size_ > 0) {
      if (*iter2 < *iter || iter == End()) {
        Insert(iter, *iter2);
        other.Erase(iter2);
        iter2 = other.Begin();
      } else {
        ++iter;
      }
    }
  }
}

template <class value_type>
void List<value_type>::Splice(const_iterator pos, List &other) {
  if (this != &other && !other.Empty() && FindIterator(pos)) {
    auto it = other.Begin();
    for (auto i = other.Begin(); i != other.End();) {
      it = i;
      Insert(pos, *i);
      ++i;
      other.Erase(it);
    }
  }
}

template <class value_type>
void List<value_type>::Reverse() {
  if (size_ > 1) {
    Node *tmp = fict_->ptr_next_;
    std::swap(fict_->ptr_next_, fict_->ptr_prev_);
    while (tmp != fict_) {
      std::swap(tmp->ptr_next_, tmp->ptr_prev_);
      tmp = tmp->ptr_prev_;
    }
  }
}

template <class value_type>
void List<value_type>::Unique() {
  if (size_ > 1) {
    auto itr = Begin();
    for (auto i = Begin(); i != End(); ++i) {
      itr = i;
      while (*i == *(++itr)) {
        Erase(itr);
        itr = i;
      }
    }
  }
}

template <class value_type>
void List<value_type>::Sort() {
  if (size_ > 1) {
    Node *current_node = head_;
    Node *next_node = current_node->ptr_next_;
    for (int i = 0; i < size_; ++i) {
      for (; current_node != tail_; current_node = current_node->ptr_next_) {
        if (current_node->data_ > next_node->data_) {
          std::swap(current_node->data_, next_node->data_);
        }
        next_node = next_node->ptr_next_;
      }
      current_node = head_;
      next_node = current_node->ptr_next_;
    }
  }
}

template <class value_type>
void List<value_type>::Clear() {
  while (size_ > 0) {
    PopFront();
  }
  head_ = tail_ = nullptr;
}

template <class value_type>
template <class... Args>
typename List<value_type>::iterator List<value_type>::InsertMany(
    const_iterator pos, Args &&...args) {
  iterator it = pos;
  for (auto data : {args...}) {
    Insert(pos, data);
  }
  return (--it);
}

template <class value_type>
template <class... Args>
void List<value_type>::InsertManyBack(Args &&...args) {
  for (auto data : {args...}) {
    PushBack(data);
  }
}

template <class value_type>
template <class... Args>
void List<value_type>::InsertManyFront(Args &&...args) {
  for (auto data : {args...}) {
    PushFront(data);
  }
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::Begin() const {
  return ListIterator(fict_->ptr_next_);
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::End() const {
  return ListIterator(fict_);
}

template <class value_type>
typename List<value_type>::size_type List<value_type>::Size() const {
  return size_;
}

template <class value_type>
typename List<value_type>::size_type List<value_type>::MaxSize() const {
  return std::min<size_type>(std::allocator<value_type>().max_size(),
                             std::numeric_limits<difference_type>::max());
}

template <class value_type>
void List<value_type>::InitList() {
  fict_ = new Node();
  fict_->ptr_next_ = fict_;
  fict_->ptr_prev_ = fict_;
  size_ = 0;
}

template <class value_type>
void List<value_type>::InitHeadTail(value_type data) {
  if (fict_ == nullptr) {
    InitList();
  }
  head_ = new Node(data, fict_, fict_);
  tail_ = head_;
}

template <class value_type>
bool List<value_type>::FindIterator(iterator it) {
  bool rez = false;
  if (it.ptr_ == fict_) {
    rez = true;
  } else {
    for (auto i = Begin(); i != End(); ++i) {
      if (i.ptr_ == it.ptr_) {
        rez = true;
      }
    }
    if (rez == false) {
    }
  }
  return rez;
}

template <class value_type>
void List<value_type>::Rewrite(int key) {
  if (size_ < 0) {
    size_ = 0;
  }
  if (key == 0) {
    fict_->ptr_next_ = head_;
    fict_->ptr_prev_ = tail_;
  }
  if (key == 1) {
    head_->ptr_prev_ = fict_;
    fict_->ptr_next_ = head_;
  }
  if (key == 2) {
    tail_->ptr_next_ = fict_;
    fict_->ptr_prev_ = tail_;
  }
  ++size_;
}

}  // namespace s21
