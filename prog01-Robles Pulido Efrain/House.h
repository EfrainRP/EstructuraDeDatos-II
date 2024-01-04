#ifndef HOUSE_H_INCLUDED
#define HOUSE_H_INCLUDED

#include <string> //libreria de las cadenas
#include <iostream>
#include <fstream> //contiene tipos de procesamiento de flujos de archivos

class House {
    private:
        ///Atributos privados
        int Number;
        std::string Street;
        std::string Colony;

        ///Metodo privado
        void copyAll(const House&);//Guardara el objeto creado a una copia

    public:
        ///Constructor
        House();
        House(const House&);

        ///Getters y Setters
        int getNumber() const;
        std::string getStreet() const;
        std::string getColony() const;

        void setNumber(const int&);
        void setStreet(const std::string&);
        void setColony(const std::string&);

        std::string toString()const;///Metodo String

        ///Sobrecarga de operadores
        House& operator = (const House&);
        bool operator == (const House&) const;
        bool operator != (const House&) const;
        bool operator < (const House&) const;
        bool operator <= (const House&) const;
        bool operator > (const House&) const;
        bool operator >= (const House&) const;

        ///Sobrecarga de operadores de flujo
        friend std::ofstream& operator << (std::ofstream&, House&); //Salida
        friend std::istream& operator >> (std::istream&, House&);   //Entrada
    };


#endif // HOUSE_H_INCLUDED
