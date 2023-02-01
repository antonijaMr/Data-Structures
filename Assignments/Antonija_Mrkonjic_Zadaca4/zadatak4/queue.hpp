#pragma once
#include <iostream>
// queue kao cirkularni buffer

template <typename T>
class queue {
  public:
  queue(size_t cap)
      : size_{0},
        capacity_{cap},
        data_{new T[capacity_]},
        first_{0},
        last_{0} {}

  queue()
      : size_{0}, capacity_{10}, data_{new T[capacity_]}, first_{0}, last_{0} {}

  queue(const queue& other)
      : size_{other.size_},
        capacity_{other.capacity_},
        data_{new T[capacity_]} {
    std::copy(other.data_, other.data_ + size_, data_);
    first_ = other.first_;
    last_ = other.last_;
  }

  queue(queue&& other)
      : size_{other.size_},
        capacity_{other.capacity_},
        data_{other.data_},
        first_{other.first_},
        last_{other.last_} {
    other.data_ = nullptr;
    other.size_ = other.capacity_ = 0u;
  }

  ~queue() { delete[] data_; }

  queue& operator=(const queue& other) {
    if (this == &other) return *this;
    delete[] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new T[capacity_];
    std::copy(other.data_, other.data_ + size_, data_);
    first_ = other.first_;
    last_ = other.last_;
    return *this;
  }

  queue& operator=(queue&& other) {
    if (this == &other) return *this;
    delete[] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;
    other.data_ = nullptr;
    first_ = other.first_;
    last_ = other.last_;
    return *this;
  }

  // move/forward
  // akoje pun iznimka out of range
  template <typename F>
  queue& push(F&& el) {
    if (size_ < capacity_) {
      if (last_ == capacity_)
        last_ = 0;
      else
        ++last_;
      data_[last_] = std::forward<F>(el);
      ++size_;
      return *this;
    } else {
      throw std::out_of_range("Queue is full");
    }
  }

  T pop() {
    if (size_ == 0) return T{};
    auto toDel = data_[first_+1];
    if (first_ == capacity_)
      first_ = 0;
    else
      ++first_;
    --size_;
    return std::move(toDel);
  }

  T& front() { return data_[first_ + 1]; }
  T& back() { return data_[last_]; }

  T& front() const { return data_[first_ + 1]; }
  T& back() const { return data_[last_]; }

  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  bool empty() const { return size_ == 0; }

  private:
  size_t size_;
  size_t capacity_;
  int first_;
  int last_;

  T* data_;
};
