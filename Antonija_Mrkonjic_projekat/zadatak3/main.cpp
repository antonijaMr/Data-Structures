#include <iostream>
#include "program.hpp"

int main(void) {
  Program mapa;
  int input;

  meni();
  while (std::cin >> input) {
    if (input == 1) {
      mapa.option1();
    } else if (input == 2) {
      mapa.option2();
    } else if (input == 3) {
      mapa.option3();
    } else if (input == 4) {
      mapa.option4();
    } else if (input == 5) {
      mapa.option5();
    } else if (input == 6) {
      mapa.option6();
    } else if (input == 7) {
      mapa.option7();
    } else if (input == 8) {
      mapa.option8();
      break;
    } else{
      std::cout << "Pogresan unos" << std::endl;
      break;
    }
    meni();
  }
    
    return 0;
  }
