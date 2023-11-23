#ifndef SRC_S21_CONTAINERS_QUEUE_QUEUE_H
#define SRC_S21_CONTAINERS_QUEUE_QUEUE_H

#include "../List/list.h"

namespace s21 {
template <class T, class Container = s21::List<T>>
class Queue {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  Queue() : base_class_(){};
  Queue(std::initializer_list<value_type> const &items) : base_class_(items){};
  Queue(const Queue &q) : base_class_(q.base_class_){};
  Queue(Queue &&q) noexcept : base_class_(std::move(q.base_class_)){};
  Queue &operator=(Queue &&q) noexcept {
    base_class_ = std::move(q.base_class_);
    return *this;
  };
  Queue &operator=(const Queue &q) {
    base_class_ = (q.base_class_);
    return *this;
  };
  ~Queue(){};

  const_reference Front() const { return base_class_.Front(); };
  const_reference Back() const { return base_class_.Back(); };

  bool Empty() const { return base_class_.Empty(); };
  size_type Size() const { return base_class_.Size(); };

  void Push(const_reference value) { base_class_.PushBack(value); };
  void Pop() { base_class_.PopFront(); };
  void Swap(Queue &other) { base_class_.Swap(other.base_class_); };
  void Print() { base_class_.print(); };

  template <class... Args>
  void InsertManyBack(Args &&...args) {
    base_class_.InsertManyBack(args...);
  };

 private:
  Container base_class_;
};
}  // namespace s21

#endif  //  SRC_S21_CONTAINERS_QUEUE_QUEUE_H