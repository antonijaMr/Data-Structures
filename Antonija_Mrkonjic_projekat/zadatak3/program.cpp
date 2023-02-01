#include "program.hpp"

void meni() {
  std::cout << "Izaberite jednu od opcija: " << std::endl;
  std::cout << "1. Dodaj novog studenta" << std::endl;
  std::cout << "2. Dodaj novi ispit" << std::endl;
  std::cout << "3. Dodaj novi predmet" << std::endl;
  std::cout << "4. Dodaj novi rezultat ispita" << std::endl;
  std::cout << "5. Dohvati sve ispite za odredjeni datum" << std::endl;
  std::cout << "6. Dohvati po datumu i imenu predmeta" << std::endl;
  std::cout << "7. Dohvati po indeksu sve predmete hronoloski i prosjecu ocjenu"
            << std::endl;
  std::cout << "8. Odjavi se" << std::endl;
  std::cout << "INPUT: ";
}

double Program::Student::prosjecnaOcjena() {
  double result = 0;
  for (auto i = 0; i < listaPointeraDoIspita.size(); ++i) {
    result += (listaPointeraDoIspita[i])->ocjena;
  }
  return result / listaPointeraDoIspita.size();
}

void Program::option1() {
  // Dodaj novog studenta
  Student s;
  std::cout << "Unesite indeks studenta: ";
  std::cin >> s.index;
  studenti.emplace(s.index, s);
}

void Program::option2() {
  // Dodaj novi ispit
  kljucPr predmet;
  kljucDatum datum;
  std::cout << "Unesite sifru/ime predmeta: ";
  std::cin >> predmet;
  std::cout << "Unesite datum: ";
  std::cin >> datum;
  //operator[] dodaje u mapu sa isptima 
  //kljuc je ime/sifra predmenta
  auto& referencaNaMapuSaIspitima = ispiti[predmet];
  //U podmapu dodajemo sa datumom kao kljucem
  referencaNaMapuSaIspitima[datum];
}

void Program::option3() {
  // Dodaj novi predmet
  kljucPr ime;
  std::cout << "Unesite sifru/ime predmeta: ";
  std::cin >> ime;
  ispiti[ime];
}

void Program::option4() {
  // Dodaj novi rezultat ispita
  std::string indeks, predmet, datum;
  int ocjena;
  std::cout << "Unesite indeks: ";
  std::cin >> indeks;
  std::cout << "Unesite sifru/ime predmeta: ";
  std::cin >> predmet;
  std::cout << "Unesite datum ispita: ";
  std::cin >> datum;
  std::cout << "Unesite ocjenu: ";
  std::cin >> ocjena;

  //study je jedan student
  //adresa/pokazivac na jednog studenta
  auto study = &studenti[indeks]; 
  auto& MapaSaIspitima = ispiti[predmet]; // mapa sa ispitima sa kljucem(predmet)
  auto& listaIspita = MapaSaIspitima[datum]; //podmapa sa kljucem datumom

  listaIspita.push_back(Ispit(ocjena, study, predmet, datum));
  auto iter = listaIspita.begin() + listaIspita.size() - 1;

  (study->listaPointeraDoIspita).push_back(Pointer(iter));
  //svaki student ima vektor pointera/iterator do polozenih ispita
}

void Program::option5() const {
  // Dohvati sve ispite za odredjeni datum
  kljucDatum datum;
  std::cout << "Unesite datum: ";
  std::cin >> datum;
  std::cout << "ime \tocjena \tindex" << std::endl;
  //prolazimo kroz mapu sa predmetima
  for (auto it = ispiti.begin(); it != ispiti.end(); ++it) {
    auto& MapaSaIspitima = it->second;
    const auto& iteratorNaVecIspita = MapaSaIspitima.find(datum);
    //za predmet koji ima ispit na datum koji smo naveli ispisujemo rezultate
    if (iteratorNaVecIspita != MapaSaIspitima.end()) {
      auto& VektorIspita = (iteratorNaVecIspita)->second;
      printVec(VektorIspita);
    }
  }
}

void Program::option6() {
  // Dohvati po datumu i imenu predmeta
  std::string ime, datum;
  std::cout << "Unesite sifru/ime predmeta: ";
  std::cin >> ime;
  std::cout << "Unesite datum: ";
  std::cin >> datum;

  //dohvatamo po kljucu za predemt
  auto& MapaSaIspitima = ispiti[ime];
  //dohvatamo po kljucu za datum
  auto& listaIspita = MapaSaIspitima[datum];

  //ispisujemo sve studente
  std::cout << "Studenti koji su polozili" << std::endl;
  for (auto& e : listaIspita) std::cout << (e.student)->index << " ";
  std::cout << std::endl;
}

void Program::option7() {
  // Dohvati po indeksu sve predmete hronoloski
  // i prosjecnu ocjenu
  kljucPr indeks;
  std::cout << "Unesite indeks: ";
  std::cin >> indeks;
  //dovatamo jednog studenta po kljucu za indeks
  auto& study = studenti[indeks];
  auto& vecIspita = study.listaPointeraDoIspita;

  std::cout << "Hronoloska lista polozenih predmeta" << std::endl;
  std::cout << "\tIme \tdatum \tocjena" << std::endl;
  for (auto& e : vecIspita) {
    std::cout << "\t" << e->imePredmeta << "\t" << e->datum << "\t" << e->ocjena
              << std::endl;
  }

  std::cout << "Prosjecna ocjena: " << study.prosjecnaOcjena() << std::endl;
}

void Program::option8() const { std::cout << "odjava...." << std::endl; }

void Program::printVec(const std::vector<Ispit>& vec) const {
  for (auto& e : vec) {
    std::cout << e.imePredmeta << "\t" << e.ocjena << "\t" << (e.student)->index
              << std::endl;
  }
}

