#include "postfix.hpp"

int main(void)
{
  postfix calc;

  auto result = calc.input(std::cin);
  calc.process(result);
  
  std::cout << "processed" << std::endl;
  std::cout << "result: " << calc.result() << std::endl;

  return 0;
}
