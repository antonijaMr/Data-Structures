#include "polinom.hpp"

Polinom::Polinom(const std::initializer_list<int>& inList) {
  for (auto e : inList) elements_.push_back(e);
}

Polinom::Polinom(int n){
  for(auto i = 0u; i<n; ++i) elements_.push_back(0);
}

Polinom Polinom::operator+(const Polinom& other) {
  Polinom max((other.size() >= this->size() ? other : *this));
  Polinom min((other.size() <= this->size() ? other : *this));
  for (auto i = 0; i < min.size(); ++i) {
    max[i] += min[i];
  }
  return max;
}

Polinom Polinom::operator-(const Polinom& other) {
  Polinom max((other.size() >= this->size() ? other : *this));
  Polinom min((other.size() <= this->size() ? other : *this));
  for (auto i = 0; i < min.size(); ++i) {
    max[i] -= min[i];
  }
  return max;
}

Polinom Polinom::operator*(const Polinom& other) {
   Polinom p(size()+other.size()-1);
  for(int i = 0; i<size(); ++i){
    for(int j = 0; j<other.size(); ++j){
      p.elements_[i+j] += elements_[i]*other.elements_[j];
    }
  }
  return p;
}

Polinom& Polinom::operator+=(const Polinom& other) {
  int max = this->size() > other.size() ? this->size() : other.size();
  for (int i = 0; i < max; ++i) {
    if (i > other.size() - 1)
      break;
    else if (i > this->size() - 1)
      elements_.push_back(other[i]);
    else
      elements_[i] += other[i];
  }
  return *this;
}

double Polinom::operator()(int n) {
  double suma = elements_[0];
  for (int i = 1; i < elements_.size(); ++i) {
    suma += elements_[i] * pow(n, i);
  }
  return suma;
}

Polinom Polinom::izvod() {
  Polinom temp(this->size());
  for (int i = 0; i < temp.size(); ++i) {
    temp[i] = elements_[i + 1] * (i + 1);
  }
  return temp;
}

std::istream& operator>>(std::istream& in, Polinom& p) {
  int n;
  int pos = 0;
  while (in >> n) {
    p.set(n, pos);
    ++pos;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Polinom& p) {
  auto temp = p.getElements();
  for (int i = 0; i < temp.size(); ++i) {
    if (temp[i] == 0) continue;
    if (i == 1)
      out << temp[i] << "X" << " ";
    else if (i == 0)
      out << temp[i] << " ";
    else
      out << temp[i] << "X^" << i << " ";
  }
  return out;
}

