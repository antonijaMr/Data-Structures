#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

size_t hash(const std::string& s);

template <typename KEY, typename VALUE>
class unordered_map {
  public:
  using key_type = KEY;
  using mapped_type = VALUE;
  using value_type = std::pair<key_type, mapped_type>;
  using bucket_type = std::list<value_type>;
  using iterator_tag =
      std::iterator<std::bidirectional_iterator_tag, value_type>;

  class iterator;

  unordered_map() { storage_.resize(storageSize); }

  void emplace(const key_type& key, VALUE value = {}) {
    auto index = hash(key) % storageSize;
    auto& bucket = storage_[index];
    bucket.push_back(value_type(key, std::move(value)));
    indexlist.push_back(index);
  }

  mapped_type& operator[](const key_type& key) {
    auto index = hash(key) % storageSize;
    auto& bucket = storage_[index];
    //ako pronadjemo element
    for (auto& par : bucket) {
      if (par.first == key) return par.second;
    }
    //ako ne pronadjemo 
    emplace(key);
    return operator[](key);
  }

  //vraca iterator na element
  //ili ako ne pronadje end()
  iterator find(const key_type& key) {
    auto index = hash(key) % storageSize;
    auto& bucket = storage_[index];
    int i = 0;
    for (auto& e : bucket) {
      if (e.first == key) {
        return iterator(&storage_, &indexlist, i);
      }
      ++i;
    }
    return end();
  }

  //ako izbrise (pronadje vraca true)
  //ako ne postoji vraca false
  bool erase(const key_type& key) {
    auto index = hash(key) % storageSize;
    auto& bucket = storage_[index];

    auto it = find_if(bucket.begin(), bucket.end(),
                      [&key](const auto& el) { return el.first == key; });

    if (it != bucket.end()) {
      bucket.erase(it);
      auto toDel = std::find(indexlist.begin(), indexlist.end(), index);
      indexlist.erase(toDel);
      return true;
    } else {
      return false;
    }
  }

  //vraca iterator na prvi element
  iterator begin() { return iterator(&storage_, &indexlist, 0); }
  iterator begin() const { return iterator(&storage_, &indexlist, 0); }

  //vraca iterator koji se nedereferencira
  //pokazuje izvan kontejnera
  //samo oznacava da je kraj
  iterator end() {
    return iterator(&storage_, &indexlist, indexlist.size() - 1, true);
  }
  iterator end() const {
    return iterator(&storage_, &indexlist, indexlist.size() - 1, true);
  }

  private:
  std::vector<bucket_type> storage_;
  const static int storageSize = 1000;
  std::vector<int> indexlist;
};

template <typename KEY, typename VALUE>
class unordered_map<KEY, VALUE>::iterator : public iterator_tag {
  public:
  iterator()
      : storageRef{nullptr}, indexlist{nullptr}, indexInList{0}, isEnd{1} {}
  iterator(std::vector<bucket_type>* s, std::vector<int>* i, int k,
           bool e = false)
      : storageRef{s}, indexlist{i}, indexInList{k}, isEnd{e} {}

  iterator(const iterator& it)
      : storageRef{it.storageRef},
        indexlist{it.indexlist},
        indexInList{it.indexInList},
        isEnd{it.isEnd} {}

  template <typename F>
  iterator& operator=(iterator&& it) {
    if (this == &it) return *this;
    storageRef = std::forward<F>(it.storageRef);
    indexlist = std::forward<F>(it.indexlist);
    indexInList = std::forward<F>(it.indexInList);
    isEnd = it.isEnd;
    return *this;
  }

  //dereferenciramo element u listi sa indeksom koji smo sacuvali
  //vracamo njegov second
  mapped_type& operator*() const {
    bucket_type bt =
        (storageRef->operator[](indexlist->operator[](indexInList)));
    if (!bt.empty()) {
      return (bt.begin())->second;
    } else {
      throw std::out_of_range("Greska");
    }
  }

  //vracamo adresu prvog elementa u bucketu
  value_type* operator->() const {
    bucket_type& bt =
        (storageRef->operator[](indexlist->operator[](indexInList)));
    return &(*(bt.begin()));
  }

  //nekonstanti overload
  value_type* operator->() {
    bucket_type& bt =
        (storageRef->operator[](indexlist->operator[](indexInList)));
    return &(*(bt.begin()));
  }

  //prefix
  //ako uradimo ++end() nista se ne dogodi
  iterator& operator++() {
    if (indexInList >= indexlist->size() - 1) {
      isEnd = true;
      indexInList = indexlist->size() - 1;
    } else if (indexInList < indexlist->size()) {
      ++indexInList;
    }
    return *this;
  }

  //postfix
  iterator operator++(int) {
    if (isEnd == true) return *this;
    auto temp = *this;
    if (indexInList >= indexlist->size() - 1) {
      isEnd = true;
      indexInList = indexlist->size() - 1;
    } else if (indexInList < indexlist->size()) {
      ++indexInList;
    }
    return temp;
  }


  //prefix
  //ako uradimo --begin() nista se ne dogodi
  //--end() vraca zadnji element
  iterator& operator--() {
    if (indexInList == 0) return *this;
    if (isEnd == true) {
      isEnd = false;
      indexInList = indexlist->size() - 1;
    } else if (indexInList < indexlist->size()) {
      --indexInList;
    }
    return *this;
  }

  //postfix
  iterator operator--(int) {
    auto temp = *this;
    if (indexInList == 0) return temp;
    if (isEnd == true) {
      isEnd = false;
      indexInList = indexlist->size() - 1;
    } else if (indexInList < indexlist->size()) {
      --indexInList;
    }
    return temp;
  }

  bool operator==(const iterator& it) const {
    return (indexInList == it.indexInList) && (storageRef == it.storageRef) &&
           (indexlist == it.indexlist) && (isEnd == it.isEnd);
  }

  bool operator!=(const iterator& it) const {
    return (indexInList != it.indexInList) || (storageRef != it.storageRef) ||
           (indexlist != it.indexlist) || (isEnd != it.isEnd);
  }

  //poredimo kako su poredani u listi indeksa
  bool operator>(const iterator& it) const {
    return (indexInList > it.indexInlist);
  }
  bool operator>=(const iterator& it) const {
    return (indexInList >= it.indexInlist);
  }
  bool operator<(const iterator& it) const {
    return (indexInList < it.indexInlist);
  }
  bool operator<=(const iterator& it) const {
    return (indexInList <= it.indexInlist);
  }

  private:
  //pointer na buckete
  std::vector<bucket_type>* storageRef;
  //pointer na listu indeksa 
  std::vector<int>* indexlist;
  int indexInList = 0;
  bool isEnd = false;
};

