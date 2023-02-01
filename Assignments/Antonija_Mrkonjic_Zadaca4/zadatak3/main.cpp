#include "bank.hpp"

int main(void) {
  int input;
  bankAccount account;

  menu();
  while (std::cin >> input) {
    if(input == 1){
      account.option1();
    }else if(input == 2){
      account.option2();
    }else if(input ==3){
      account.option3();
    }else if(input == 4){
      account.option4();
    }else if(input ==5){
      account.option5();
    }else if(input ==6){
      account.option6();
      break;
    }else{
      account.option();
    }
    menu();
  }

  return 0;
}
