#include <iostream>
#include "mojaLista.hpp"

int main(int argc, char *argv[])
{
  mojaLista<int> a{1,2,3,4,4};
  a.print();
  a.swap();
  a.print();
  a.swap();
  a.print();
  
  return 0;
}
