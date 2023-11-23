#ifndef SRC_S21_CONTAINERSPLUS_ARRAY_ARRAY_H
#define SRC_S21_CONTAINERSPLUS_ARRAY_ARRAY_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T, size_t N>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array();
  ~Array();
  Array(const Array<T, N> &a);
  Array(Array<T, N> &&a) noexcept;
  Array(std::initializer_list<T> const &items);

  Array<T, N> &operator=(Array<T, N> &&a);
  Array<T, N> &operator=(const Array<T, N> &a);

  const_reference operator[](size_type pos) const;
  reference operator[](size_type pos);

  reference At(size_type pos);
  const_reference At(size_type pos) const;
  const_reference Front();
  const_reference Back();

  bool Empty() const;
  size_type Size() const;
  size_type MaxSize() const;

  iterator Data();
  iterator Begin();
  iterator End();

  void Swap(Array<T, N> &other);
  void Fill(const_reference value);

 private:
  size_type size_;
  iterator array_;

  void CopyArray(const Array<T, N> &a);
};

}  // namespace s21

#include "array.tpp"
#endif  // SRC_S21_CONTAINERSPLUS_ARRAY_ARRAY_H
