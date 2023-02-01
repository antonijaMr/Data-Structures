#include "postfix.hpp"

void postfix::plus() {
  int res = numbers.top();
  numbers.pop();
  res += numbers.top();
  numbers.pop();
  numbers.push(res);
}
void postfix::minus() {
  int temp = numbers.top();
  numbers.pop();
  auto res = numbers.top();
  numbers.pop();
  res -= temp;
  numbers.push(res);
}
void postfix::multiply() {
  int res = numbers.top();
  numbers.pop();
  res *= numbers.top();
  numbers.pop();
  numbers.push(res);
}
void postfix::devide() {
  int res = numbers.top();
  numbers.pop();
  res /= numbers.top();
  numbers.pop();
  numbers.push(res);
}

std::string postfix::input(std::istream& in) {
  std::string input;
  getline(in, input);
  return input;
}

void postfix::process(const std::string& input) {
  std::string oneString;
  int num;
  std::stringstream ss(input);

  while (ss >> oneString) {
    if (oneString == "+") {
      plus();
    } else if (oneString == "-") {
      minus();
    } else if (oneString == "*") {
      multiply();
    } else if (oneString == "/") {
      devide();
    } else {
      num = stoi(oneString);
      numbers.push(num);
    }
  }
}

int postfix::result() {
  if (numbers.size() == 1)
    return numbers.top();
  else
    std::cout << "something is wrong" << std::endl;
  return 0;
}

