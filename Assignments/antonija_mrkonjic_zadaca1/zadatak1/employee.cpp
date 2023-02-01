#include "employee.hpp"

std::ostream& operator<<(std::ostream& out, const Employee& e){
  return out << e.getName() << " " << e.getSurname() << " "
             << e.getAge() << " " << e.getExperience() << " "
             << e.getSalary() << " " << e.getNumber() << std::endl;
}
