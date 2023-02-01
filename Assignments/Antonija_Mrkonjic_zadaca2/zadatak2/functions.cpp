#include <iostream>
#include <algorithm>
#include "employee.hpp"
#include "MojVektor.hpp"
#include <sstream>
#include <fstream>
#include <exception>

void print(const MojVector<Employee>& vec){
  for(auto it = vec.begin(); it!=vec.end(); ++it)
    std::cout << *it;
}

void sortByName(MojVector<Employee>& vec){
  auto lambda = [](const Employee& one, const Employee& two){ 
    if(one.getName() != two.getName()){
      return one.getName() < two.getName();
    }else if (one.getSurname() != two.getSurname()){
      return one.getSurname() < two.getName();
    }else{
      return one.getAge() < two.getAge();
    }
  };
  std::sort(vec.begin(), vec.end(),lambda);
}

void sortByAge(MojVector<Employee>& vec){
auto lambda = [](const Employee& one, const Employee& two){
    if(one.getAge() != two.getAge())
      return one.getAge() > two.getAge();
    else
      return one.getExperience() > two.getExperience();
  };
  std::sort(vec.begin(),vec.end(),lambda);
}


void fileToVector(std::ifstream& fin, MojVector<Employee>& vec){
  if(fin.is_open()){
  std::string temp;
  while(getline(fin,temp)){
      std::replace(temp.begin(),temp.end(),',',' ');
      std::stringstream ss(temp);
      std::string name,surname,number; 
      int age,salary,expi;
      ss >> name >> surname >> age >> expi >> salary >> number;
      Employee e(name,surname,age,expi,salary,number);
      vec.push_back(e);
      }
  }else{
    throw std::out_of_range("Can't open the file");
  }
}

void VectorToFile(std::ofstream& fout,const MojVector<Employee>& vec){
  if(fout.is_open()){
  fout << "Name \tSurname \tAge \tExperience \tSalary \tNumber"<< std::endl;
  for(auto it = vec.begin(); it!=vec.end(); ++it){ 
    fout << it->getName() << "\t" << it->getSurname()
         << "\t" << it->getAge() << "\t" << it->getExperience() 
         << "\t" << it->getSalary() << "\t" << "\t" << it->getNumber() << std::endl;
  }
  }else{
    throw std::out_of_range("Can't open the file");
  }
}

MojVector<Employee> retire(const MojVector <Employee>& vec){
  MojVector<Employee> newVec;
  for(auto it = vec.begin(); it!=vec.end(); ++it){
    if(it->getAge() < 55){
      newVec.push_back(*it);
    }
  }
  return newVec;
}

MojVector<Employee> increase15(MojVector<Employee> vec){
  sortByAge(vec);

  MojVector<Employee> newVec;
  int ten = vec.size()-10;

  for(int i = ten; i< vec.size(); ++i){
    vec[i].increaseSalary(1.15);
    newVec.push_back(vec[i]);
  }
  return newVec;
}

MojVector<Employee> increase20(MojVector<Employee> vec){
  MojVector<Employee> newVec;
  for(auto it = vec.begin(); it!=vec.end();++it){
    if(it->getExperience() >= 15){
      it->increaseSalary(1.2);
      newVec.push_back(*it);
    }
  }
  return newVec;
}

