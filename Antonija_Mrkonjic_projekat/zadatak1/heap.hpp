#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class heap {
  private:
  int N;
  size_t capacity_;
  T* data_;

  void reallocate();
  void bottomUp(int k);
  void topDown(int k, int n);

  int findMin() const;
  void printInorder(int nodeIndex) const;

  public:
  heap();
  heap(int maxN);
  heap(const heap& other);
  heap(heap&& other);
  ~heap() { delete[] data_; }

  heap& operator=(const heap& other);
  heap& operator=(heap&& other);

  void insert(T const& v);

  T removeMin();
  T removeMax();

  T max() const { return data_[1]; }
  T min() const { return data_[findMin()]; }

  size_t size() const { return N; }

  void printInorder() const;
  void depth() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const heap<T>& h) {
  h.printInorder();
  return out;
}

template <typename T>
void heap<T>::reallocate() {
  auto temp = new T[capacity_ * 2];
  std::copy(data_, data_ + N+1, temp);
  delete[] data_;
  data_ = std::move(temp);
  capacity_ *= 2;
}

template <typename T>
void heap<T>::bottomUp(int k) {
  while (k > 1 && data_[k / 2] < data_[k]) {
    std::swap(data_[k], data_[k / 2]);
    k = k / 2;
  }
}

template <typename T>
void heap<T>::topDown(int k, int n) {
  while (2 * k <= n) {
    int j = 2 * k;
    if (j < n && data_[j] < data_[j + 1]) ++j;
    if (!(data_[k] < data_[j])) break;
    std::swap(data_[k], data_[j]);
    k = j;
  }
}

template <typename T>
//trazimo najmanjeg i vracamo njegov indeks
int heap<T>::findMin() const {
  int min = 1;
  for (auto i = 1; i < N; ++i) {
    min = data_[min] < data_[i + 1] ? min : i + 1;
  }
  return min;
}

template <typename T>
//print rekurzija
void heap<T>::printInorder(int nodeIndex) const {
  while (nodeIndex < N + 1) {
    if (nodeIndex == 1) {
      printInorder(nodeIndex * 2);
      std::cout << data_[nodeIndex] << " ";
      printInorder(nodeIndex * 2 + 1);
      return;
    } else if (nodeIndex == N) {
      std::cout << data_[nodeIndex] << " ";
      return;
    } else if (nodeIndex > N) {
      return;
    } else {
      printInorder(nodeIndex * 2);
      std::cout << data_[nodeIndex] << " ";
      printInorder(nodeIndex * 2 + 1);
      return;
    }
  }
}

template <typename T>
heap<T>::heap() : data_{new T[10]}, N{0}, capacity_{10} {}

template <typename T>
heap<T>::heap(int maxN) : data_{new T[maxN]}, N{0}, capacity_(maxN) {}

template <typename T>
heap<T>::heap(const heap<T>& other)
    : N{other.N}, capacity_{other.capacity_}, data_{new T[capacity_]} {
  std::copy(other.data_, other.data_ + N+1, data_);
}

template <typename T>
heap<T>::heap(heap<T>&& other) : N{other.N}, capacity_{other.capacity_} {
  data_ = other.data_;
  other.data_ = nullptr;
  other.capacity_ = 0;
  other.N = 0;
}

template <typename T>
heap<T>& heap<T>::operator=(const heap& other) {
  if (&other == this) return *this;
  delete[] data_;
  N = other.N;
  capacity_ = other.capacity_;
  data_ = new T[capacity_];
  std::copy(other.data_, other.data_ + N, data_);
  return *this;
}

template <typename T>
heap<T>& heap<T>::operator=(heap&& other) {
  if (&other == this) return *this;
  delete[] data_;
  N = other.N;
  capacity_ = other.capacity_;
  data_ = other.data_;
  other.data_ = nullptr;
  other.N = other.capacity_ = 0;
  return *this;
}

template <typename T>
//ubacujemo element na zadnje mjesto
//sredjujemo prema gore
void heap<T>::insert(T const& v) {
  if (N == capacity_-1) reallocate();
  data_[++N] = v;
  bottomUp(N);
}

template <typename T>
//trazimo najmanji,
//mijenjamo ga sa zadnjim(osim ako je zadnji)
//sredjujemo prema gore
T heap<T>::removeMin() {
  if (N == 0) throw std::out_of_range("Heap is empty!");
  auto min = findMin();
  if (min != N - 1) {
    std::swap(data_[N], data_[min]);
    bottomUp(min);
  }
  return data_[N--];
}

template <typename T>
//mijenjamo najveci sa posljednjim
//sredjujemo prema dole
T heap<T>::removeMax() {
  if (N == 0) throw std::out_of_range("Heap is empty!");
  std::swap(data_[1], data_[N]);
  topDown(1, N - 1);
  return data_[N--];
}

template <typename T>
//pozivamo rekurzivnu funkciju
void heap<T>::printInorder() const {
  printInorder(1);
}

template <typename T>
//prolazenje po nivoima
void heap<T>::depth() const {
  for (auto i = 1; i < size() + 1; ++i) std::cout << data_[i] << " ";
  std::cout << std::endl;
}

