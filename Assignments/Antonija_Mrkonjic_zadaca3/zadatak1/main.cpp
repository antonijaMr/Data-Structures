#include "toDoTask.hpp"

int main(void)
{
  ToDoTask tasks;
  int choice;
  tasks.menu0();
  while( std::cin >> choice){
    if(choice == 1){
      tasks.option1();
    }else if(choice == 2){
      tasks.option2();
    }else if(choice == 3){
      tasks.option3();
    }else{
      tasks.wronginput();
    }
    tasks.menu0();
  }
  
  return 0;
}
