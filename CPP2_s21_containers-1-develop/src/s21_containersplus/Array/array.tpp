#include "array.h"

namespace s21 {
template <class T, std::size_t N>
Array<T, N>::Array() : size_(N) {
  array_ = new value_type[N]{};
}

template <class T, size_t N>
Array<T, N>::~Array() {
  delete[] array_;
  size_ = 0;
}

template <class T, size_t N>
Array<T, N>::Array(const Array<T, N> &a) {
  size_ = N;
  if (size_ == a.size_) {
    array_ = new T[size_]();
    CopyArray(a);
  }
}

template <class T, std::size_t N>
Array<T, N>::Array(Array<T, N> &&a) noexcept {
  size_ = a.size_;
  array_ = new T[size_]();
  CopyArray(a);
  a.Fill(value_type{});
}

template <class T, size_t N>
Array<T, N>::Array(const std::initializer_list<T> &items) {
  size_ = N;
  if (size_ < items.size())
    throw std::invalid_argument("Invalid initializer list size");
  array_ = new T[size_]{};
  std::copy(items.begin(), items.end(), array_);
}

template <class T, size_t N>
Array<T, N> &Array<T, N>::operator=(const Array<T, N> &a) {
  CopyArray(a);
  return *this;
}

template <class T, size_t N>
Array<T, N> &Array<T, N>::operator=(Array<T, N> &&a) {
  CopyArray(a);
  return *this;
}

template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::operator[](
    size_type pos) const {
  if (pos > size_) throw std::out_of_range("invalid index");
  return array_[pos];
}

template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) {
  if (pos > size_) throw std::out_of_range("invalid index");
  return array_[pos];
}

template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::At(size_type pos) {
  return (*this)[pos];
}

template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::At(size_type pos) const {
  return (*this)[pos];
}

template <class T, size_t N>
void Array<T, N>::CopyArray(const Array<T, N> &a) {
  for (size_type i = 0; i < size_; ++i) array_[i] = a.array_[i];
}

template <class T, size_t N>
typename Array<T, N>::size_type Array<T, N>::Size() const {
  return size_;
}

template <class T, size_t N>
typename Array<T, N>::size_type Array<T, N>::MaxSize() const {
  return N;
}

template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::Front() {
  if (Empty()) throw std::invalid_argument("Array is empty");
  return array_[0];
}

template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::Back() {
  if (Empty()) throw std::invalid_argument("Array is empty");
  return array_[size_ - 1];
}

template <class T, size_t N>
bool Array<T, N>::Empty() const {
  return size_ == 0;
}

template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::Begin() {
  iterator it = iterator();
  if (N != 0) it = array_;
  return it;
}

template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::End() {
  iterator it = iterator();
  if (N != 0) it = array_ + N;
  return it;
}

template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::Data() {
  iterator it = iterator();
  if (N != 0) it = array_;
  return it;
}

template <class T, size_t N>
void Array<T, N>::Swap(Array<T, N> &other) {
  std::swap(array_, other.array_);
  std::swap(size_, other.size_);
}

template <class T, size_t N>
void Array<T, N>::Fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) array_[i] = value;
}
}  // namespace s21