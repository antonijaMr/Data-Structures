#pragma once
#include <math.h>
// #include <vector>
#include "MojVektor.hpp"
#include <iostream>

class Polinom{
  public:
    Polinom(const std::initializer_list<int>& inList);
    Polinom(int n);
    Polinom(const Polinom& other):elements_{other.elements_}{}

    Polinom operator+(const Polinom& other);
    Polinom operator-(const Polinom& other);
    Polinom operator*(const Polinom& other);
    Polinom& operator+=(const Polinom& other);

    double operator()(int n);
    Polinom izvod();

    int& operator[](size_t index){ return elements_[index]; }
    int operator[](size_t index)const{ return elements_[index]; }

    void set(int n, size_t pos){ elements_[pos] = n; }
    MojVector<int> getElements()const{ return elements_;}
    size_t size() const{ return elements_.size();}

  private:
    MojVector<int> elements_;
};

std::istream& operator>>(std::istream& in,Polinom& p);
std::ostream& operator<<(std::ostream& out,const Polinom& p);
