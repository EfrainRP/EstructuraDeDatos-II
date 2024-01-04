#ifndef HOUSE_H_INCLUDED
#define HOUSE_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>

class House {
private:
    ///Atributos
    int Number;
    std::string Street;
    std::string Colony;

    ///Metodo privado
    void copyAll(const House&);//Guardara el objeto creado a una copia

public:
    ///Constructores (original y copia)
    House();
    House(const House&);

    ///Metodos (Getters,Setters y etc)
    int getNumber() const;
    std::string getStreet() const;
    std::string getColony() const;

    void setNumber(const int&);
    void setStreet(const std::string&);
    void setColony(const std::string&);

    std::string toString()const;

    ///Sobrecarga de operadores
    House& operator = (const House&);
    bool operator == (const House&) const;
    bool operator != (const House&) const;
    bool operator < (const House&) const;
    bool operator <= (const House&) const;
    bool operator > (const House&) const;
    bool operator >= (const House&) const;

    friend std::ofstream& operator << (std::ofstream&, House&);
    friend std::istream& operator >> (std::istream&, House&);
};


#endif // HOUSE_H_INCLUDED
