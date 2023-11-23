#ifndef SRC_S21_CONTAINERS_VECTOR_VECTOR_H
#define SRC_S21_CONTAINERS_VECTOR_VECTOR_H

#include <limits>
#include <memory>
#include <stdexcept>

namespace s21 {

template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;

  Vector();
  explicit Vector(size_type n);
  Vector(std::initializer_list<T> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v) noexcept;
  ~Vector();

  Vector<T> &operator=(Vector &&v) noexcept;
  Vector<T> &operator=(const Vector &v);

  reference At(size_type pos);
  const_reference At(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference Front() const;
  const_reference Back() const;
  iterator Data();

  iterator Begin() const;
  iterator End() const;

  bool Empty() const;
  size_type Size() const;
  size_type MaxSize() const;
  void Reserve(size_type size);
  size_type Capacity() const;
  void ShrinkToFit();

  void Clear();
  iterator Insert(const_iterator pos, const_reference value);
  void Erase(iterator pos);
  void PushBack(const_reference value);
  void PopBack();
  void Swap(Vector &other);

  template <class... Args>
  iterator InsertMany(const_iterator pos, Args &&...args);
  template <class... Args>
  void InsertManyBack(Args &&...args);

 private:
  T *vector_;
  size_type size_;
  size_type capacity_;
  void ZeroVector();
  void MemoryAllocation(size_t n);
  void ChangeCapacity(size_t n);
};

}  // namespace s21

#include "vector.tpp"
#endif  // SRC_S21_CONTAINERS_VECTOR_VECTOR_H
