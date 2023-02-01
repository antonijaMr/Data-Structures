#pragma once
#include <iostream>
#include "person.hpp"

class Employee :public Person{
  public:
    Employee(const std::string& name, const std::string& surname, int age, int experience,double salary, const std::string& number)
      :Person{name,surname,age},experience_{experience},salary_{salary},number_{number}{}
    Employee(const Employee& e)
      :Person{e.getName(),e.getSurname(),e.getAge()},experience_{e.experience_},salary_{e.salary_},number_{e.number_}{}

    void setSalary(int s){salary_=s;}
    void setExperience(int e){experience_=e;}
    void setNumber(const std::string& n){number_=n;}

    int getSalary()const{return salary_;}
    int getExperience()const{return experience_;}
    const std::string& getNumber()const{return number_;}

    void increaseSalary(double num){ salary_ *= num;}

  private:
    int experience_;
    double salary_;
    std::string number_;
};

std::ostream& operator<<(std::ostream& out, const Employee& e);
