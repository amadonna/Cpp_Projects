#ifndef SRC_S21_CONTAINERS_STACK_STACK_H
#define SRC_S21_CONTAINERS_STACK_STACK_H

#include "../List/list.h"

namespace s21 {
template <class T, class Container = s21::List<T>>
class Stack {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  Stack() : base_class_(){};
  Stack(std::initializer_list<T> const &items) : base_class_(items){};
  Stack(const Stack &s) : base_class_(s.base_class_){};
  Stack(Stack &&s) noexcept : base_class_(std::move(s.base_class_)){};
  Stack &operator=(Stack &&s) noexcept {
    base_class_ = std::move(s.base_class_);
    return *this;
  };
  Stack &operator=(const Stack &s) {
    base_class_ = (s.base_class_);
    return *this;
  };
  ~Stack(){};

  const_reference Top() const { return base_class_.Back(); };

  bool Empty() const { return base_class_.Empty(); };
  size_type Size() const { return base_class_.Size(); };

  void Push(const_reference value) { base_class_.PushBack(value); };
  void Pop() { base_class_.PopBack(); };
  void Swap(Stack &other) { base_class_.Swap(other.base_class_); };
  template <class... Args>
  void InsertManyFront(Args &&...args) {
    for (auto i : {args...}) {
      Push(i);
    }
  };

 private:
  Container base_class_;
};
}  // namespace s21

#endif  //  SRC_S21_CONTAINERS_STACK_STACK_H
