#include <string> 
#include "osoba.hpp"

Osoba::Osoba(const std::string& i, const std::string& p, int g)
  :ime_{i},prezime_{p},godine_{g}{}

const std::string& Osoba::getIme()const{ return ime_; }
const std::string& Osoba::getPrezime()const{ return prezime_; }
int Osoba::getGodine()const{ return godine_; }

void Osoba::setIme(const std::string& i){ ime_ = i; }
void Osoba::setPrezime(const std::string& p){ prezime_ = p; }
void Osoba::setGodine(int g){ godine_ = g; }


