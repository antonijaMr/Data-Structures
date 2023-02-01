#include <algorithm>
#include <vector>

#include "vozac.hpp"
#include "automobil.hpp"
#include "osoba.hpp"

int main()
{
  int brojac;
  Vozac v;
  std::cout << "Unesite broj vozaca: ";
  std::cin >> brojac;

  std::vector<Vozac> vozaci;

  for(int i = 0; i<brojac; ++i){
    std::cin >> v;
      vozaci.push_back(v);
    }

    std::sort(vozaci.begin(),vozaci.end(), 
        [](const Vozac& p, const Vozac& d){
        return p.getVrijeme() < d.getVrijeme(); 
        });

    std::cout << "Ispis: " << std::endl;
    print(vozaci);

    return 0;
}
