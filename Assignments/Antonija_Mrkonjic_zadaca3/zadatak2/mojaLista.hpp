#pragma once

#include <initializer_list>
#include <iostream>

template <typename T>
class mojaLista {
  public:
  mojaLista() : head_{nullptr}, tail_{nullptr}, size_{0} {}
  mojaLista(const std::initializer_list<T>& other) {
    auto it = other.begin();
    while (it != other.end()) {
      push_back(*it);
      ++it;
    }
  }

  mojaLista(const mojaLista& other) {
    auto temp = other.head_;
    while (temp != nullptr) {
      push_back(temp->data);
      temp = temp->next;
    }
  }

  mojaLista(mojaLista&& other)
      : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  mojaLista& operator=(const mojaLista& other) {
    if (&other != this) {
      clear();
      auto temp = other.head_;
      while (temp != nullptr) {
        push_back(temp->data);
        temp = temp->next;
      }
    }
    return *this;
  }

  mojaLista& operator=(mojaLista&& other) {
    if (&other != this) {
      clear();
      std::swap(head_, other.head_);
      std::swap(tail_, other.tail_);
      std::swap(size_, other.size_);
    }
    return *this;
  }

  ~mojaLista() { clear(); }

  void clear() {
    while (head_ != nullptr) {
      auto temp = head_;
      head_ = head_->next;
      delete temp;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
  }

  void push_back(const T& element) {
    size_++;
    if (head_ == nullptr) {
      tail_ = head_ = new Node{nullptr, element, nullptr};
    } else {
      auto temp = new Node{tail_, element, nullptr};
      tail_->next = temp;
      tail_ = temp;
    }
  }

  void push_back(T&& element) {
    size_++;
    if (head_ == nullptr) {
      tail_ = head_ = new Node{nullptr, std::move(element), nullptr};
    } else {
      auto temp = new Node{tail_, std::move(element), nullptr};
      tail_->next = temp;
      tail_ = temp;
    }
  }

  void push_front(const T& element) {
    size_++;
    if (head_ == nullptr) {
      tail_ = head_ = new Node{nullptr, element, nullptr};
    } else {
      auto temp = new Node{nullptr, element, head_};
      head_->prev = temp;
      head_ = temp;
    }
  }

  void push_front(T&& element) {
    size_++;
    if (head_ == nullptr) {
      tail_ = head_ = new Node{nullptr, std::move(element), nullptr};
    } else {
      auto temp = new Node{nullptr, std::move(element), head_};
      head_->prev = temp;
      head_ = temp;
    }
  }

  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }
  void pop_front() {
    --size_;
    auto temp = head_->next;
    temp->prev = nullptr;
    delete head_;
    head_ = temp;
  }

  void pop_back() {
    --size_;
    auto temp = tail_->prev;
    temp->next = nullptr;
    delete tail_;
    tail_ = temp;
  }

  bool operator==(const mojaLista& other) const {
    if (size_ != other.size_)
      return false;
    else {
      auto v1 = head_;
      auto v2 = other.head_;
      while (v1 != nullptr) {
        if (*v1 != *v2) return false;
        v1 = v1->next;
        v2 = v2->next;
      }
    }
    return true;
  }

  bool operator!=(const mojaLista& other) const { return !(*this == other); }

  // slozenost O(n)
  // const T& at(size_t index) const;

  T& front() { return head_->data; }
  T& back() { return tail_->data; }

  class iterator;

  iterator begin() { return iterator{head_, nullptr}; }
  iterator end() { return iterator{nullptr, tail_}; }
  iterator begin() const { return iterator{head_, nullptr}; }
  iterator end() const { return iterator{nullptr, tail_}; }

  void insert(iterator position, const T& element) {
    if (position == end())
      push_back(element);
    else if (position == begin())
      push_front(element);
    else {
      auto before = position->prev;
      auto after = before->next;
      ++size_;
      auto novi = new Node{before, element, after};
      before->next = novi;
      after->prev = novi;
    }
  }

  void insert(iterator position, T&& element) {
    if (position == end())
      push_back(std::move(element));
    else if (position == begin())
      push_front(std::move(element));
    else {
      auto before = position->prev;
      auto after = before->next;
      ++size_;
      auto novi = new Node{before, std::move(element), after};
      before->next = novi;
      after->prev = novi;
    }
  }

  iterator find(const T& element) const {
    auto temp = begin();
    while (temp != end()) {
      if (*temp == element) return temp;
      ++temp;
    }
    return end();
  }

  iterator erase(iterator position) {
    if (position == begin()) {
      pop_front();
      return begin();
    } else if (position == --end()) {
      pop_back();
      return end();
    } else if (position != begin()) {
      --size_;
      auto p = position->prev;
      auto n = position->next;
      auto toDel = p->next;
      p->next = n;
      n->prev = p;
      delete toDel;
      return p;
    } else {
      return end();
    }
  }

  void print() {
    auto temp = head_;
    while (temp != nullptr) {
      std::cout << temp->data << " ";
      temp = temp->next;
    }
    std::cout << std::endl;
  }

  // void swap(){
  //   auto drugi = head_->next;
  //   auto predzadnji = tail_->prev;
  //
  //   auto temp = head_;
  //   head_ = tail_;
  //   tail_ = temp;
  //   head_->prev = nullptr;
  //   head_->next = drugi;
  //   drugi->prev = head_;
  //
  //   tail_->next = nullptr;
  //   tail_->prev = predzadnji;
  //   predzadnji->next = tail_;
  //   std::cout << "swaped"<< std::endl;
  // }

  // reverse
  // ne radi btw :(
  // void swap(){
  //   auto newHead = tail_;
  //   auto nodePrev = tail_;
  //   auto nodeNext = tail_->prev->prev;
  //   newHead->prev = nullptr;
  //   newHead->next = tail_->prev;
  //   newHead = newHead->next;
  //   while(newHead != nullptr){
  //     newHead->next = nodeNext++;
  //     newHead->prev = nodePrev++;
  //     newHead = newHead->next;
  //   }
  //   tail_ = head_;
  //   tail_->next = nullptr;
  //   head_ = newHead;
  //   std::cout << "swaped" << std::endl;
  // }

  void swap() {
    // samo swap vrijednosti
    /*
    auto tempH = head_->data;
    auto tempT = tail_->data;

    head_->data= tempT;
    tail_->data= tempH;
    */

    auto secondL = head_->next;
    auto notLast = tail_->prev;

    auto temp = head_;
    head_ = tail_;
    head_->next = secondL;
    head_->prev = nullptr;

    tail_ = temp;
    tail_->next = nullptr;
    tail_->prev = notLast;

    secondL->prev = head_;
    notLast->next = tail_;

    std::cout << "swaped" << std::endl;
  }

  private:
  struct Node {
    Node* prev;
    T data;
    Node* next;

    bool operator!=(const Node& other) const { return data != other.data; }
    bool operator==(const Node& other) const { return data == other.data; }
  };

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_t size_ = 0;
};

template <typename T>
class mojaLista<T>::iterator
    : public std::iterator<std::bidirectional_iterator_tag, T> {
  public:
  iterator() : p_{nullptr}, pPrev_{nullptr} {}
  iterator(Node* p, Node* otherP) : p_{p}, pPrev_{otherP} {}
  iterator(Node* p) : p_{p}, pPrev_{p->prev} {}

  T& operator*() const { return p_->data; }
  Node* operator->() const { return p_; }
  T& operator*() { return p_->data; }
  Node* operator->() { return p_; }

  iterator& operator++() {
    if (p_ == nullptr) return *this;
    pPrev_ = p_;
    p_ = p_->next;
    return *this;
  }
  iterator operator++(int) {
    if (p_ == nullptr) return *this;
    auto temp = iterator{p_};
    pPrev_ = p_;
    p_ = p_->next;
    return temp;
  }

  iterator& operator--() {
    if (pPrev_ == nullptr) return *this;
    p_ = pPrev_;
    pPrev_ = p_->prev;
    return *this;
  }
  iterator operator--(int) {
    if (pPrev_ == nullptr) return *this;
    auto temp = iterator{p_};
    p_ = pPrev_;
    pPrev_ = p_->prev;
    return temp;
  }

  bool operator!=(const iterator& other) const { return p_ != other.p_; }
  bool operator==(const iterator& other) const { return p_ == other.p_; }

  // friend mojaLista;

  private:
  Node* p_;
  Node* pPrev_;
};
