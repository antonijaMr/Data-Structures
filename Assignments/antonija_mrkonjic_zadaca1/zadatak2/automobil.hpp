#pragma once
#include <string>

class Automobil{
  public:
    Automobil()=default;
    Automobil(const std::string& m, const std::string& b, int g);
    Automobil(const Automobil& a);
    Automobil(Automobil&& a);
    
    Automobil operator=(const Automobil& a);

    const std::string& getModel()const;
    const std::string& getBoja()const;
    int getGodinaProzvodnje()const;

    void setModel(const std::string& m);
    void setBoja(const std::string& b);
    void setGodinaProizvodnje(int g);

  private:
    std::string model_; 
    std::string boja_;
    int godinaProizvodnje_ = 2000;
};

std::ostream& operator <<(std::ostream& out, const Automobil& a);

