#pragma once
#include <iostream>

class Osoba{
  public:

    Osoba()=default;
    Osoba(const std::string& i, const std::string& p, int g);

    const std::string& getIme()const;
    const std::string& getPrezime()const;
    int getGodine()const;

    void setIme(const std::string& i);
    void setPrezime(const std::string& p);
    void setGodine(int g);

  private:
    std::string ime_;
    std::string prezime_;
    int godine_;
};

