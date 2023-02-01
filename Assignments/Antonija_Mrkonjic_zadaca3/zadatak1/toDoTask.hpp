#pragma once
#include "lista.hpp"

class ToDoTask {
  private:
  struct task {
    int id;
    std::string title;
    std::string description;
    int priority;

    bool operator==(const task& other) const;
    bool operator!=(const task& other) const;
    bool operator>=(const task& other) const;
    bool operator<=(const task& other) const;
    bool operator<(const task& other) const;
    bool operator>(const task& other) const;
  };
  Lista<task> tasks;

  public:
  int generateId();
  void addTask();
  void printTask()const;
  bool menuExit()const;
  void menu0()const;
  void menu1()const;
  void option1()const;
  void option2();
  void option3();
  void wronginput()const;
};
