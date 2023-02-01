#include "queue.hpp"

int main(void) {
  queue<int> red(3);
  //konstruktori
  {
    queue<int> red1;
    queue<int> red2 = red1;
    queue<int> red3(100);

    red1 = red3;
    red2 = std::move(red1);
  }

  red.push(1);
  red.push(2);
  red.push(3);

  std::cout << "first: " << red.front() << std::endl;
  std::cout << "last: " << red.back() << std::endl;
  std::cout << "size: " << red.size() << std::endl;

  red.pop();
  red.push(4);
  red.pop();
  red.push(5);
  red.pop();
  red.push(6);
  red.pop();
  red.push(7);

  // 123
  // 234
  // 345
  // 456
  // 567

  std::cout << "After pop i push" << std::endl;
  std::cout << "first: " << red.front() << std::endl;
  std::cout << "last: " << red.back() << std::endl;
  std::cout << "size: " << red.size() << std::endl;
  std::cout << "pop: " << red.pop() << std::endl;

  return 0;
}
