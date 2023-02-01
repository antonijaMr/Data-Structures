#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "employee.hpp"
#include <sstream>
#include <fstream>
#include <exception>

void print(const std::vector<Employee>& vec);

void sortByName(std::vector<Employee>& vec);
void sortByAge(std::vector<Employee>& vec);

void fileToVector(std::ifstream& fin, std::vector<Employee>& vec);
void VectorToFile(std::ofstream& fout,const std::vector<Employee>& vec);


std::vector<Employee> retire(const std::vector<Employee>& vec);
std::vector<Employee> increase15(std::vector<Employee> vec);
std::vector<Employee> increase20(std::vector<Employee> vec);

