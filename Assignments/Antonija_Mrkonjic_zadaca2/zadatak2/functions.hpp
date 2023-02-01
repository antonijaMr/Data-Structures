#pragma once
#include <iostream>
#include <algorithm>
#include "MojVektor.hpp"
#include "employee.hpp"
#include <sstream>
#include <fstream>
#include <exception>

void print(const MojVector<Employee>& vec);

void sortByName(MojVector<Employee>& vec);
void sortByAge(MojVector<Employee>& vec);

void fileToVector(std::ifstream& fin, MojVector<Employee>& vec);
void VectorToFile(std::ofstream& fout,const MojVector<Employee>& vec);


MojVector<Employee> retire(const MojVector<Employee>& vec);
MojVector<Employee> increase15(MojVector<Employee> vec);
MojVector<Employee> increase20(MojVector<Employee> vec);

