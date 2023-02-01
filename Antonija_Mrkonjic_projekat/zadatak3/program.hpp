#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

void meni();

class Program {
  public:
  struct Student;
  struct Ispit;
  using kljucSt = std::string;
  using kljucPr = std::string;
  using kljucDatum = std::string;
  using Pointer = std::vector<Ispit>::iterator;
  using MapaStudenata = std::unordered_map<kljucSt, Student>;
  using MapaIspita =
      std::unordered_map<kljucPr,
                         std::unordered_map<kljucDatum, std::vector<Ispit>>>;

  struct Student {
    kljucSt index;
    std::vector<Pointer> listaPointeraDoIspita;

    double prosjecnaOcjena();
  };

  struct Ispit {
    Ispit(int o, Student* s, const std::string& str, const std::string& d)
        : ocjena{o}, student{s}, imePredmeta{str}, datum{d} {}
    int ocjena;
    Student* student;
    kljucPr imePredmeta;
    kljucDatum datum;
  };

  void option1();
  void option2();
  void option3();
  void option4();
  void option5() const;
  void option6();
  void option7();
  void option8() const;

  private:
  MapaStudenata studenti;
  MapaIspita ispiti;

  void printVec(const std::vector<Ispit>& vec) const;
};

