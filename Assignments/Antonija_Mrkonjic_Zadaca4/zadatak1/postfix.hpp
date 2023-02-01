#pragma once
#include <iostream>
#include <sstream>
#include <stack>

class postfix {
  public:
  void plus();
  void minus();
  void multiply();
  void devide();

  std::string input(std::istream& in);
  void process(const std::string& input);

  int result();

  private:
  std::stack<int> numbers;
};
