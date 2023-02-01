#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "employee.hpp"
#include "person.hpp"
#include "functions.hpp"

 
int main()
{
  std::vector<Employee> employees;
  
  std::ofstream CorpFile{"CORP.txt"};
  std::ofstream increaseTo15File{"IncreaseTo15.txt"};
  std::ofstream increaseTo20File{"IncreaseTo20.txt"};
  std::ifstream acme{"acme.txt"};
  std::ifstream globex{"globex.txt"}; 
  std::cout << "Ucitavamo radnike iz firmi Acme i Globex" << std::endl;

  fileToVector(acme,employees);
  fileToVector(globex,employees);
  
  std::cout << "Firma CORP ima "<< employees.size() << " radnika"  << std::endl;

  std::vector<Employee> employeesInCORP = retire(employees);

  sortByName(employeesInCORP);
  VectorToFile(CorpFile,employeesInCORP);
  std::cout << "Nakon brisanja firma ima " << employeesInCORP.size() << " radnika" << std::endl;
  
  std::cout << "Radnici iz IncraeseTo15 imaju povecanu platu za 15%" << std::endl;
  std::vector<Employee> to15 = increase15(employeesInCORP);
  VectorToFile(increaseTo15File,to15);

  std::cout << "Radnici iz IncreaseTo20 imaju povecanu platu za 20%" << std::endl;
  std::vector<Employee> to20 = increase20(employeesInCORP);
  VectorToFile(increaseTo20File,to20);
}

