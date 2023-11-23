#include "vector.h"

namespace s21 {

template <class T>
Vector<T>::Vector() {
  ZeroVector();
}

template <class T>
Vector<T>::Vector(size_t n) {
  MemoryAllocation(n);
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> const &items) {
  MemoryAllocation(items.size());
  std::copy(items.begin(), items.end(), vector_);
}

template <class T>
Vector<T>::Vector(const Vector &v) {
  MemoryAllocation(v.size_);
  std::copy(v.vector_, v.vector_ + v.size_, vector_);
}

template <class T>
Vector<T>::Vector(Vector &&v) noexcept
    : vector_(v.vector_), size_(v.size_), capacity_(v.capacity_) {
  v.ZeroVector();
}

template <class T>
Vector<T>::~Vector() {
  delete[] vector_;
  ZeroVector();
}

template <class T>
Vector<T> &Vector<T>::operator=(Vector &&v) noexcept {
  if (this != &v) {
    delete[] vector_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    vector_ = v.vector_;
    v.ZeroVector();
  }
  return *this;
}

template <class T>
Vector<T> &Vector<T>::operator=(const Vector &v) {
  if (this != &v) {
    delete[] vector_;
    vector_ = new T[v.capacity_];
    std::copy(v.vector_, v.vector_ + v.size_, vector_);
    size_ = v.size_;
    capacity_ = v.capacity_;
  }
  return *this;
}

template <class T>
typename Vector<T>::reference Vector<T>::At(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("range check pos >= size_");
  }
  return vector_[pos];
}

template <class T>
typename Vector<T>::const_reference Vector<T>::At(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("range check pos >= size_");
  }
  return vector_[pos];
}

template <class T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return vector_[pos];
}

template <class T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
  return vector_[pos];
}

template <class T>
typename Vector<T>::const_reference Vector<T>::Front() const {
  return vector_[0];
}

template <class T>
typename Vector<T>::const_reference Vector<T>::Back() const {
  return vector_[size_ - 1];
}

template <class T>
typename Vector<T>::iterator Vector<T>::Data() {
  return vector_;
}

template <class T>
typename Vector<T>::iterator Vector<T>::Begin() const {
  return vector_;
}

template <class T>
typename Vector<T>::iterator Vector<T>::End() const {
  return vector_ + size_;
}

template <class T>
bool Vector<T>::Empty() const {
  return size_ == 0;
}
template <class T>
size_t Vector<T>::Size() const {
  return size_;
}
template <class T>
size_t Vector<T>::MaxSize() const {
  return std::min<size_type>(std::allocator<T>().max_size(),
                             std::numeric_limits<difference_type>::max());
}
template <class T>
void Vector<T>::Reserve(size_type size) {
  if (size > capacity_) {
    ChangeCapacity(size);
  }
}
template <class T>
size_t Vector<T>::Capacity() const {
  return capacity_;
}

template <class T>
void Vector<T>::ShrinkToFit() {
  if (capacity_ > size_) {
    ChangeCapacity(size_);
  }
}

template <class T>
void Vector<T>::Clear() {
  size_ = 0;
  delete[] vector_;
  vector_ = nullptr;
}

template <class T>
typename Vector<T>::iterator Vector<T>::Insert(const_iterator pos,
                                               const_reference value) {
  if (pos < Begin() || pos > End()) {
    throw std::out_of_range("range check pos >= size_");
  }
  size_t position = pos - Begin();
  PushBack(value);
  for (size_t i = size_ - 1; i > position; i--) {
    std::swap(vector_[i], vector_[i - 1]);
  }
  return vector_ + position;
}

template <class T>
void Vector<T>::Erase(iterator pos) {
  if (pos < Begin() || pos > End()) {
    throw std::out_of_range("range check pos >= size_");
  }
  size_t position = pos - Begin();
  for (size_t i = position; i < size_ - 1; i++) {
    std::swap(vector_[i], vector_[i + 1]);
  }
  size_ -= 1;
}

template <class T>
void Vector<T>::PushBack(const_reference value) {
  if (size_ + 1 > capacity_) {
    Reserve(size_ * 2);
  }
  vector_[size_] = value;
  size_ += 1;
}

template <class T>
void Vector<T>::PopBack() {
  size_ = size_ > 0 ? size_ - 1 : 0;
}

template <class T>
void Vector<T>::Swap(Vector &other) {
  if (this != &other) {
    std::swap(vector_, other.vector_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }
}

template <class T>
template <class... Args>
typename Vector<T>::iterator Vector<T>::InsertMany(const_iterator pos,
                                                   Args &&...args) {
  size_t position = pos - Begin();
  for (auto i : {args...}) {
    Insert(Begin() + position, i);
    position++;
  }
  return Begin() + position;
}

template <class T>
template <class... Args>
void Vector<T>::InsertManyBack(Args &&...args) {
  for (auto i : {args...}) {
    PushBack(i);
  }
}

template <class T>
void Vector<T>::ZeroVector() {
  vector_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <class T>
void Vector<T>::MemoryAllocation(size_t n) {
  size_ = n;
  capacity_ = size_;
  vector_ = new T[size_]{};
}

template <class T>
void Vector<T>::ChangeCapacity(size_t n) {
  T *tmp_vector = new T[n];
  std::copy(vector_, End(), tmp_vector);
  delete[] vector_;
  vector_ = tmp_vector;
  capacity_ = n;
}

}  // namespace s21