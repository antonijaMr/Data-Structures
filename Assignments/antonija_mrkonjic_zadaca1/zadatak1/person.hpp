#pragma once
#include <string>

class Person{
  public:
    Person()=default;
    Person(const std::string& n, const std::string& s, int a)
      :name_{n},surname_{s},age_{a}{}

    void setName(const std::string& n){name_=n;}
    void setSurname(const std::string& s){surname_=s;}
    void setAge(int a){age_=a;}

    const std::string& getName()const{return name_;}
    const std::string& getSurname()const{return surname_;}
    int getAge()const{return age_;}

  private:
    std::string name_;
    std::string surname_;
    int age_;
};

