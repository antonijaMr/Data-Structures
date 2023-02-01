#include "automobil.hpp"
#include <iostream>

Automobil::Automobil(const std::string& m, const std::string& b, int g)
  :model_{m}, boja_{b}, godinaProizvodnje_{g}{}
Automobil::Automobil(const Automobil& a)
  :model_{a.model_}, boja_{a.boja_}, godinaProizvodnje_{a.godinaProizvodnje_}{}
Automobil::Automobil(Automobil&& a)
  :model_{std::move(a.model_)}, boja_{std::move(a.boja_)},godinaProizvodnje_{std::move(a.godinaProizvodnje_)}{}

Automobil Automobil::operator=(const Automobil& a){
  model_=a.model_;
  boja_=a.boja_;
  godinaProizvodnje_=a.godinaProizvodnje_;
  return *this;
}

const std::string& Automobil::getModel()const{ return model_; }
const std::string& Automobil::getBoja()const{ return boja_; }
int Automobil::getGodinaProzvodnje()const{ return godinaProizvodnje_; }

void Automobil::setModel(const std::string& m){ model_ = m; }
void Automobil::setBoja(const std::string& b){ boja_ = b; }
void Automobil::setGodinaProizvodnje(int g){ godinaProizvodnje_ = g; }

std::ostream& operator<<(std::ostream& out, const Automobil& a){
  return out << a.getModel() << " " << a.getBoja() << " " << a.getGodinaProzvodnje();
}

