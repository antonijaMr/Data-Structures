#include <stack>
#include <fstream>
#include <iostream>
// napisati progam koji provjerava da li su zagrade balansirane

bool otvorenaZagrada(char c) { return c == '(' || c == '[' || c == '{' || c == '<'; }

bool zatvorenaZagrada(char c) { return c == ')' || c == ']' || c == '}' || c == '>'; }

bool podudarneZagrade(char l, char r) {
  return (l == '(' && r == ')') || (l == '[' && r == ']') ||
         (l == '{' && r == '}') || (l == '<' && r == '>');
}
int main(void) {
  std::stack<char> zagrade;
  char c;
  while (std::cin >> c) {
    if (otvorenaZagrada(c)) {
      zagrade.push(c);
    } else if (zatvorenaZagrada(c)) {
      if (!zagrade.empty() && podudarneZagrade(zagrade.top(), c)) {
        zagrade.pop();
      } else {
        std::cout << "pogresan!!" << std::endl;
        return 1;
      }
    }
  }
  if (zagrade.empty())
    std::cout << "dobar!" << std::endl;
  else
    std::cout << "pogresan!!!" << std::endl;
  return 0;
}
