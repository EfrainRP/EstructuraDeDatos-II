#include "House.h" //"libreria" de implementacion del objeto a manejar

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

///Getters y Setters
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

string House::toString() const {///Metodo String
    string myStr;

    //Formato para la impresion de los atributos
    myStr += to_string(Number);
    myStr.resize (25,' ');
    myStr += " | ";
    myStr += Street.c_str();
    myStr.resize (56,' ');
    myStr += " | ";
    myStr += Colony.c_str();
    myStr.resize (88,' ');
    myStr += " | ";

    return myStr;//Regresara la cadena con todo el formato para la tabla
    }

///Sobrecarga de operadores
House& House::operator =(const House& h) {
    copyAll(h);
    return *this;
    }
//El atributo base para la comparacion sera con el numero de la casa
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

    os<<h.Number<<'|'<<h.Street<<'|'<<h.Colony<<'*';//Imprimira los datos de este formato, si se usa el operador <<
    return os;
    }

istream& operator >> (istream& is, House& h) { //Entrada
    string str;
    getline(is, str,'|');
    h.Number = atoi(str.c_str());//atoi, funcion de string para convertir una cadena a un entero
                                //.c_str(), funcion de string para converir una cadena a una cadena de caracteres

    getline(is,h.Street,'|');
    getline(is,h.Colony,'*');
    return is;//Guardara la informacion de lo que lea en sus respectivos atributos con, getline y su delimitador respectivo
    }
