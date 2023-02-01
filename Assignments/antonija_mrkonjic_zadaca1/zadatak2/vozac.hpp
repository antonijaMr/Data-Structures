#pragma once 

#include "osoba.hpp"
#include "automobil.hpp"
#include <iostream>
#include <vector>

class Vozac: public Osoba{
  public:
    Vozac()=default;
    Vozac(const std::string& i, const std::string& p, int g, int gs, const Automobil& a, const float& v);

    int getGodineStaza()const;
    const Automobil& getAutomobil()const;
    float getVrijeme()const;
    
    void setGodineStaza(int g);
    void setAutomobil(const Automobil& a);
    void setVrijeme(const float& v);

  private:
    Automobil automobil_;
    int godineStaza_;
    float vrijeme_;
};

std::ostream& operator<<(std::ostream& out, const Vozac& v);
std::istream& operator>>(std::istream& input, Vozac& v);

template<typename T>
void print(const std::vector<T>& niz){
  for(int i = 0; i<niz.size(); ++i){
    std::cout << niz[i] << std::endl;
  }
}

