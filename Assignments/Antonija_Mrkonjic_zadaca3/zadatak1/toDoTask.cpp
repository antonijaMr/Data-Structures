#include "toDoTask.hpp"

bool ToDoTask::task::operator==(const task& other) const {
  return priority == other.priority;
}
bool ToDoTask::task::operator!=(const task& other) const {
  return priority != other.priority;
}
bool ToDoTask::task::operator>=(const task& other) const {
  return priority >= other.priority;
}
bool ToDoTask::task::operator<=(const task& other) const {
  return priority <= other.priority;
}
bool ToDoTask::task::operator<(const task& other) const {
  return priority < other.priority;
}
bool ToDoTask::task::operator>(const task& other) const {
  return priority > other.priority;
}

int ToDoTask::generateId() {
  static int counter = 0;
  return ++counter;
}

void ToDoTask::addTask() {
  std::cin.ignore();
  task T;
  T.id = generateId();
  std::cout << "Enter a new ToDoTask: " << std::endl;
  std::cout << "Enter the title of the task: ";
  getline(std::cin, T.title);
  std::cout << "Enter the description of the task: ";
  getline(std::cin, T.description);
  std::cout << "Enter a priority (>0): ";
  std::cin >> T.priority;
  tasks.add(T);
}

void ToDoTask::printTask() const {
  std::cout << std::string(40, '*') << std::endl;
  std::cout << std::string(40, '*') << std::endl;
  for (auto it = tasks.begin(); it != tasks.end(); ++it) {
    std::cout << "Title: " << (*it).title << std::endl;
    std::cout << "Description: " << (*it).description << std::endl;
    std::cout << "Priority: " << (*it).priority << std::endl;
    std::cout << "Id: " << (*it).id << std::endl;
    std::cout << std::endl;
  }
  std::cout << std::string(40, '*') << std::endl;
  std::cout << "Enter id of the task which you want to mark as done: ";
}

bool ToDoTask::menuExit() const {
  int input;
  std::cout << "Enter number 0 to EXIT program, or something else to continue"
            << std::endl;
  std::cin >> input;
  if (input == 0) exit(1);
  return (input == '0');
}

void ToDoTask::menu0() const {
  std::cout << "Choose one of the options" << std::endl;
  std::cout << std::string(40, '*') << std::endl;
  std::cout << "1. Display the current LIST of ToDoTask" << std::endl;
  std::cout << "2. Enter a new ToDoTask" << std::endl;
  std::cout << "3. Mark ToDoTask as done" << std::endl;
  std::cout << "Enter your choice: ";
}

void ToDoTask::menu1() const {
  std::cout << std::string(40, '*') << std::endl;
  std::cout << "Your notes is empty" << std::endl;
  menuExit();
}

void ToDoTask::option1() const {
  std::cout << std::string(40, '*') << std::endl;
  if (tasks.size() == 0) {
    std::cout << "Your list is empty!" << std::endl;
    menuExit();
  } else {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
      std::cout << std::string(8, '*') << std::endl;
      std::cout << "* Task *" << std::endl;
      std::cout << std::string(8, '*') << std::endl;
      std::cout << "Title: " << (*it).title << std::endl;
      std::cout << "Description: " << (*it).description << std::endl;
      std::cout << "Priority: " << (*it).priority << std::endl;
    }
  }
  menuExit();
}

void ToDoTask::option2() {
  std::cout << std::string(40, '*') << std::endl;
  addTask();
}

void ToDoTask::option3() {
  int idInput;
  if (tasks.size() == 0) {
    std::cout << "Your list is empty!" << std::endl;
  } else {
    auto predicate = [](const task& t, int n) { return t.id == n; };
    printTask();
    std::cin >> idInput;
    auto it = tasks.find(predicate, idInput);
    if (it != tasks.end())
      tasks.remove(it);
    else
      std::cout << "Task with id=" << idInput << " does not exits" << std::endl;
  }
}

void ToDoTask::wronginput() const { menuExit(); }
