#include "bank.hpp"

void menu() {
  std::cout << "Actions: " << std::endl;
  std::cout << "\t1. New transaction" << std::endl;
  std::cout << "\t2. Apply transaction" << std::endl;
  std::cout << "\t3. Pending transaction" << std::endl;
  std::cout << "\t4. Discard pending transaction" << std::endl;
  std::cout << "\t5. Ballance" << std::endl;
  std::cout << "\t6. Exit" << std::endl;
  std::cout << "Your choice? ";
}

bool bankAccount::empty() const {
  if (transactions_.size() == 0) {
    std::cout << "No transactions in queue" << std::endl;
    return true;
  } else
    return false;
}

void bankAccount::add() {
  transaction newTr;
  std::cout << "Amount to add: ";
  std::cin >> newTr.toAdd;
  std::cout << "Date: ";
  std::cin >> newTr.date;
  std::cout << "Time: ";
  std::cin >> newTr.time;
  transactions_.push(std::move(newTr));
}

void bankAccount::subtract() {
  transaction newTr;
  std::cout << "Amount to subtract: ";
  std::cin >> newTr.toSubstract;
  std::cout << "Date: ";
  std::cin >> newTr.date;
  std::cout << "Time: ";
  std::cin >> newTr.time;
  transactions_.push(std::move(newTr));
}

void bankAccount::option1() {
  int input;
  std::cout << "\t1. ADD" << std::endl;
  std::cout << "\t2. SUBTRACT" << std::endl;
  std::cout << "Your choice: ";
  std::cin >> input;
  if (input == 1) {
    add();
  } else if (input == 2) {
    subtract();
  } else {
    std::cout << "Incorrect input!" << std::endl;
    return;
  }
}
void bankAccount::option2() {
  if (empty()) return;

  std::cout << "Applying transaction..." << std::endl;
  auto currentTr = transactions_.front();
  transactions_.pop();
  if (currentTr.toAdd == 0) {
    ballance_ -= currentTr.toSubstract;
  } else {
    ballance_ += currentTr.toAdd;
  }
}

void bankAccount::option3() {
  if (empty()) return;

  std::cout << "Pending transaction" << std::endl;
  auto currentTr = transactions_.front();
  std::cout << "To add: " << currentTr.toAdd << std::endl;
  std::cout << "To substract: " << currentTr.toSubstract << std::endl;
  std::cout << "Date: " << currentTr.date << std::endl;
  std::cout << "Time: " << currentTr.time << std::endl;
}

void bankAccount::option4() {
  if (empty()) return;

  std::cout << "Dicarding pending transaction..." << std::endl;
  transactions_.pop();
}
void bankAccount::option5() const {
  std::cout << "Ballance: " << ballance_ << std::endl;
}
void bankAccount::option6() const {
  std::cout << "Exiting.." << std::endl;
  return;
}
void bankAccount::option() const {
  std::cout << "Wrong input" << std::endl;
  std::cout << "Try again!" << std::endl;
}

