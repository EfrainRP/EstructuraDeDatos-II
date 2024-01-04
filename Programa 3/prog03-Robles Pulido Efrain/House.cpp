#include "House.h"
using namespace std;

///Metodo privado
void House::copyAll(const House& h) {
    Number = h.Number;
    Street = h.Street;
    Colony = h.Colony;
}

///Constructores
House::House() {}

House::House(const House& h) {
    copyAll(h);
}

///Metodos (Getters,Setters y etc)
int House::getNumber() const {
    return this->Number;
}

string House::getStreet() const {
    return this->Street;
}

string House::getColony() const {
    return this->Colony;
}

void House::setNumber(const int& n) {
    Number = n;
}

void House::setStreet(const string& s) {
    Street = s;
}

void House::setColony(const string& c) {
    Colony = c;
}

string House::toString() const {
    string myStr;

    myStr += "\t" + to_string(Number);
    myStr.resize (8,' ');
    myStr += " | ";
    myStr += Street.c_str();
    myStr.resize (26,' ');//+10
    myStr += " | ";
    myStr += Colony.c_str();
    myStr.resize (43,' ');
    myStr += " | ";
    return myStr;
}

///Sobrecarga de operadores
House& House::operator=(const House& h) {
    copyAll(h);
    return *this;
}

bool House::operator==(const House& h) const {
    return Number == h.Number;
}

bool House::operator!=(const House& h) const {
    return !(*this == h);
}

bool House::operator<(const House& h) const {
    return Number < h.Number;
}

bool House::operator<=(const House& h) const {
    return (*this < h) or (*this==h);
}

bool House::operator>(const House& h) const {
    return !(*this<=h);
}

bool House::operator>=(const House& h) const {
    return !(*this<h);
}

ofstream& operator << (ofstream& os, House& h) { //Salida

    os<<h.Number<<'|'<<h.Street<<'|'<<h.Colony<<'*';
    return os;
}

istream& operator >> (istream& is, House& h) { //Entrada

    string str;
    getline(is, str,'|');
    h.Number = atoi(str.c_str());

    getline(is,h.Street,'|');
    getline(is,h.Colony,'*');
    return is;
}
