#include "MojVektor.hpp"

int main(void)
{
  MojVector<int> v{1,2,3,4,5};
  std::cout << v << std::endl;

  v.erase(v.begin()+1,v.end()-1);
  std::cout << v << std::endl;
  // v.erase(v.end()-1);
  // std::cout << v << std::endl;
  // v.erase(v.begin()+1);
  // std::cout << v << std::endl;

  // std::cout << "Resize na 0" << std::endl;
  // v.resize(0);
  // std::cout << v << std::endl;
  
  return 0;
}
