#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T>
class MojVector {
  public:
  MojVector() : capacity_{1}, size_{0}, arr_{new T[capacity_]} {}  
  MojVector(const std::initializer_list<T> &il)
      : capacity_{il.size()+10}, size_{il.size()}, arr_{new T[capacity_]} {
    std::copy(il.begin(), il.end(), arr_);
  }
  MojVector(const MojVector &other)
      : capacity_{other.capacity_},
        size_{other.size_},
        arr_{new T[capacity_]} {
    std::copy(other.arr_, other.arr_ + size_, arr_);
  }

  MojVector &operator=(const MojVector &other) {
    if (&other == this) return *this;
    delete[] arr_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = new T[capacity_];
    std::copy(other.arr_, other.arr_ + size_, arr_);
    return *this;
  }

  MojVector(MojVector &&other)
      : capacity_{other.capacity_}, size_{other.size_} {
    other.size_ = 0;
    other.capacity_ = 0;
    std::swap(arr_, other.arr_);
  }

  MojVector &operator=(MojVector &&other) {
    if(&other == this) return *this;
    delete[] arr_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = other.arr_;
    other.arr_ = nullptr;
    // std::swap(arr_, other.arr_);
    other.capacity_ = 0;
    other.size_ = 0;
    return *this;
  }

  ~MojVector() { delete[] arr_; }

  MojVector &push_back(const T &element) {
    if (size_ == capacity_) reallocate();
    arr_[size_++] = element;
    return *this;
  }
  T &at(size_t index) const {
    if (index >= size_) throw std::out_of_range("Out of range");
    return arr_[index];
  }

  T &operator[](size_t index) const { return arr_[index]; }
  T &at(size_t index) {
    if (index >= size_) throw std::out_of_range("Out of range");
    return arr_[index];
  }

  T &operator[](size_t index) { return arr_[index]; }
  void clear(){ 
    delete [] arr_;
    arr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }
  const T &back() const { return arr_[size_ - 1]; }
  const T &front() const { return arr_[0]; }
  T &back() { return arr_[size_ - 1]; }
  T &front() { return arr_[0]; }

  void resize(size_t cap) {
    auto temp = new T[cap];
    for(int i = 0; i<size_ && i < cap; ++i)
      temp[i] = arr_[i];
    size_ = cap;
    capacity_ = cap;
    delete [] arr_;
    arr_ = std::move(temp);
  }

  MojVector &pop_back() {
    if (empty()) throw std::out_of_range{"Vector is empty"};
    --size_;
    return *this;
  }

  size_t capacity() const { return capacity_; }  // done

  bool operator==(const MojVector &other) const {
    if (other.size_ != size_ ) return false;
    for (auto i = 0u; i < size_; ++i) {
      if (other.arr_[i] != arr_[i]) return false;
    }
    return true;
  }

  bool operator!=(const MojVector &other) const {
    return !(*this==other);
  }

  void reallocate() {
    auto temp = new T[capacity_ * 2];
    std::copy(arr_, arr_ + size_, temp);
    delete[] arr_;
    arr_ = std::move(temp);
    capacity_ *= 2;
  }

  class Iterator;
  Iterator begin() const { return arr_; }
  Iterator end() const { return arr_ + size_; }
  Iterator find(const T &element) const {
    for (auto it = begin(); it != end(); ++it) {
      if (*it == element) return Iterator{it};
    }
    return end();
  }

  MojVector& insert(Iterator pos, T element) {
    if (size_ == capacity_) reallocate();
    for(auto it = end(); it!=pos; --it){
      *it=*(it-1);
    }
    *pos = element;
    ++size_;
    return *this;
  }

  Iterator erase(Iterator pos) {
    if (pos == end()) return end();
    for (auto it = pos; it < end() - 1; ++it) {
      *it = *(it + 1);
    }
    --size_;
    return pos;
  }

  Iterator erase(Iterator beginIt, Iterator endIt){
    auto n = endIt - beginIt;
    for(auto it = begin(); it < end(); ++it){
      if((it>=beginIt) || (it == end())){
        *it = *(it+n);
            }
    }
    size_ = size_-n;
    return beginIt;
  }

  private:
  size_t capacity_;
  size_t size_;
  T *arr_;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const MojVector<T> &v) {
  out << "{ ";
  for (auto i = 0u; i < v.size(); ++i) {
    out << v[i] << " ";
  }
  out << "}";
  return out;
}

template <typename T>
class MojVector<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
  public:
  Iterator(T *ptr) : ptr_{ptr} {}
  // Iterator(const Iterator& it) :ptr_{it.ptr_}{}
  // Iterator(Iterator&& it) :ptr_{it.ptr_}{}

  // Iterator &operator=(const Iterator &it) {
  //   if(&it != this) ptr_ = it.ptr_;
  //   return *this;
  // }

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  Iterator &operator++() {
    ++ptr_;
    return *this;
  }
  Iterator operator++(int) {
    auto temp = *this;
    ++ptr_;
    return temp;
  }
  Iterator &operator--() {
    --ptr_;
    return *this;
  }
  Iterator operator--(int) {
    auto temp = *this;
    --ptr_;
    return temp;
  }
  Iterator operator+(size_t index) { return ptr_ + index; }
  Iterator operator-(size_t index) { return ptr_ - index; }
  size_t operator-(Iterator other) { return ptr_ - other.ptr_; }

  bool operator==(const Iterator &it) const { return ptr_ == it.ptr_; }
  bool operator!=(const Iterator &it) const { return !(ptr_ == it.ptr_); }
  bool operator>=(const Iterator &it) const { return ptr_ >= it.ptr_; }
  bool operator<(const Iterator &it) const { return ptr_ < it.ptr_;};
  bool operator>(const Iterator &it) const { return ptr_ > it.ptr_;};

  ~Iterator() { ptr_ = nullptr; }

  private:
  T *ptr_;
};

