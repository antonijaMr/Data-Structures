#include "heap.hpp"

int main(void) {
  {
    //test
    heap<double> h1;
    h1.insert(22);
    h1.insert(25);
    h1.insert(17);
    h1.insert(19);
    h1.insert(18);
    h1.insert(14);
    h1.insert(22);
    h1.insert(19);
    std::cout << "h1: " << h1 << std::endl;

    heap<double> h2 = h1;
    std::cout << "heap h2 = h1: " << h2 << std::endl;

    heap<double> h3 = std::move(h1);
    std::cout << "heap h3 move= h1: " << h3 << std::endl;

    h3 = h2;
    std::cout << "h3 = h2: " << h3 << std::endl;

    h1 = std::move(h3);
    std::cout << "h1 move= h3: " << h1 << std::endl;
    std::cout << std::endl;
  }

  heap<int> h;
  h.insert(22);
  h.insert(25);
  h.insert(17);
  h.insert(19);
  h.insert(18);
  h.insert(14);
  h.insert(22);
  h.insert(19);

  std::cout << "inorder" << std::endl;
  std::cout << h << std::endl;
  std::cout << "depth" << std::endl;
  h.depth();

  std::cout << "max: " << h.max() << std::endl;
  std::cout << "min: " << h.min() << std::endl;

  std::cout << "test: remove min" << std::endl;
  h.removeMin();
  std::cout << h << std::endl;
  h.depth();
  std::cout << "max: " << h.max() << std::endl;
  std::cout << "min: " << h.min() << std::endl;

  std::cout << "test: remove max" << std::endl;
  h.removeMax();
  std::cout << h << std::endl;
  h.depth();
  std::cout << "max: " << h.max() << std::endl;
  std::cout << "min: " << h.min() << std::endl;

  return 0;
}

