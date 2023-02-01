#pragma once
#include <functional>
#include <iostream>

// Napraviti sortiranu jednostruko linkanu listu.
// Lista treba da ima default, copy i move konstruktore, te copy i move
// operatore jednako. Lista treba da sadrži metode add(), find() i remove().
// Metodi find() i remove() rade sa iteratorima, tako da je potrebno
// implementirati i iteratore za listu. Metod add() dodaje element na poziciju
// tako da lista bude sortirana, metod find() uzima predikat i vraća iterator na
// element koji zadovoljava predikat funkciju, a ukoliko ni jedan element ne
// zadovoljava, vraća iterator na kraj (end()). Metod remove() uzima iterator i
// briše element u listi sa te pozicije. (Obratiti pažnju na granične
// slučajeve!).

template <typename T>
class Lista {
  public:
  Lista() : head_{nullptr}, tail_{nullptr}, size_{0} {}

  Lista(const Lista& other) : head_{nullptr}, tail_{nullptr}, size_{0} {
    for (auto it = other.begin(); it != other.end(); it++) add(*it);
  }

  Lista(Lista&& other)
      : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  Lista& operator=(const Lista& other) {
    if (&other != this) {
      std::cout << "1" << std::endl;
      clear();
      for (auto it = other.begin(); it != other.end(); it++) add(*it);
    }
    return *this;
  }

  Lista& operator=(Lista&& other) {
    if (&other != this) {
      clear();
      std::swap(head_, other.head_);
      std::swap(tail_, other.tail_);
      std::swap(size_, other.size_);
    }
    return *this;
  }

  ~Lista() { clear(); }

  void clear() {
    while (head_ != nullptr) {
      auto temp = head_;
      delete head_;
      head_ = temp->nextNode_;
    }
    tail_ = nullptr;
    size_ = 0;
  }

  class iterator;

  // O(n)
  void add(const T& newElement) {
    if (size_ == 0) {
      head_ = tail_ = new Node;
      head_->element_ = newElement;
    } else if (tail_->element_ <= newElement) {
      auto temp = new Node;
      temp->element_ = newElement;
      tail_->nextNode_ = temp;
      tail_ = temp;
    } else {
      auto tempIt = begin();
      for (auto it = begin(); it != end(); it++) {
        if (*it > newElement) break;
        tempIt = it;
      }
      auto temp = new Node;
      temp->element_ = newElement;
      temp->nextNode_ = tempIt->nextNode_;
      tempIt->nextNode_ = temp;
    }
    ++size_;
  }

  iterator find(const T& element) const {
    auto temp = head_;
    while (temp != nullptr) {
      if (temp->element_ == element) break;
      temp++;
    }
    return std::move(temp);
  }

  template <typename F>
  iterator find(F func, int n) const {
    auto temp = begin();
    while (temp != end()) {
      if (func(*temp, n)) break;
      temp++;
    }
    return temp;
  }

  // O(n)
  void remove(iterator it) {
    if (size_ == 0) return;
    size_--;
    if (it == begin()) {
      auto temp = head_;
      head_ = head_->nextNode_;
      delete temp;
    } else if (it == tail_) {
      auto temp = begin();
      for (auto i = begin(); i != end(); i++) {
        if (i == it) break;
        temp = i;
      }
      temp->nextNode_ = nullptr;
      delete it.getP();
      tail_ = temp.getP();
      // pop back O(n)
    } else {
      auto temp = begin();
      for (auto i = begin(); i != end(); i++) {
        if (i == it) break;
        temp = i;
      }
      temp->nextNode_ = it->nextNode_;
      delete it.getP();
    }
  }

  size_t size() const { return size_; }

  iterator begin() const { return head_; }
  iterator end() const { return nullptr; }

  private:
  struct Node {
    T element_;
    Node* nextNode_;
  };
  Node* head_;
  Node* tail_;
  size_t size_;
};

template <typename T>
class Lista<T>::iterator : public std::iterator<std::forward_iterator_tag, T> {
  public:
  // iterator():p_{nullptr}{}
  iterator(Node* other) : p_{other} {}
  iterator(const iterator& it) : p_{it.p_} {}
  iterator(iterator&& it) : p_{it.p_} {}

  Node* getP() { return p_; }

  iterator& operator=(const iterator& other) { p_ = other.p_; }

  iterator& operator++() {
    p_ = p_->nextNode_;
    return *this;
  }
  iterator operator++(int) {
    auto temp = p_;
    p_ = p_->nextNode_;
    return temp;
  }
  T& operator*() const { return p_->element_; }
  Node* operator->() const { return p_; }

  bool operator!=(const iterator& other) const { return p_ != other.p_; }
  bool operator==(const iterator& other) const { return p_ == other.p_; }

  private:
  Node* p_;
};

