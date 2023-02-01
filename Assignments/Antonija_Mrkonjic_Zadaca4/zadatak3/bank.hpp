#pragma once
#include <iostream>
#include <queue>

void menu();

class bankAccount {
  public:
  bool empty()const;
  void add();
  void subtract();

  void option1();
  void option2();
  void option3();
  void option4();
  void option5()const;
  void option6()const;
  void option()const;

  private:
  struct transaction {
    double toAdd = 0;
    double toSubstract = 0;
    std::string date;
    std::string time;
  };
  std::queue<transaction> transactions_;
  double ballance_;
};
