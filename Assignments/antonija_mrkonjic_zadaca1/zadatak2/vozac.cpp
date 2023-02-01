#include "vozac.hpp"

Vozac::Vozac(const std::string& i, const std::string& p, int g, int gs, const Automobil& a, const float& v)
  :Osoba{i,p,g}, automobil_{a}, godineStaza_{gs}, vrijeme_{v}{}

int Vozac::getGodineStaza()const{ return godineStaza_; }
const Automobil& Vozac::getAutomobil()const{ return automobil_; }
float Vozac::getVrijeme()const{ return vrijeme_; }

void Vozac::setGodineStaza(int g){ godineStaza_ = g; }
void Vozac::setAutomobil(const Automobil& a){ automobil_ = a; }
void Vozac::setVrijeme(const float& v){ vrijeme_ = v; }


std::ostream& operator<<(std::ostream& out, const Vozac& v){
  return out << v.getIme() << " " << v.getPrezime() << " " 
      << v.getGodine() << " " << v.getAutomobil() << " "
      << v.getGodineStaza() << " " << v.getVrijeme() << " ";
}

std::istream& operator>>(std::istream& input, Vozac& v){
  std::string i;
  int godine;
  Automobil a;
  double vrijeme;
  
  std::cout << "ime prezime godine model boja godinaProizvodnje godineStaza vrijeme" << std::endl;

  input >> i;
  v.setIme(i);
  input >> i;
  v.setPrezime(i);
  input >> godine;
  v.setGodine(godine);

  input >> i;
  a.setModel(i);
  input >> i;
  a.setBoja(i);
  input >> godine;
  a.setGodinaProizvodnje(godine);
  v.setAutomobil(a);

  input >> godine;
  v.setGodineStaza(godine);
  input >> vrijeme;
  v.setVrijeme(vrijeme);

  return input;
}

