#include "nombre.h"

using namespace std;

///Metodo privado
void Nombre::copyAll(const Nombre& n) {
    firstName = n.firstName;
    secondName = n.secondName;
    }

///Constructores
Nombre::Nombre() {}

Nombre::Nombre(const Nombre& n) {
    copyAll(n);
    }

///Metodos (Getters,Setters y etc)
std::string Nombre::getFirstName() const {
    return firstName;
    }

std::string Nombre::getLastName() const {
    return secondName;
    }

void Nombre::setFirstName(const std::string& name_1) {
    firstName = name_1;
    }

void Nombre::setLastName(const std::string& name_2) {
    secondName = name_2;
    }

std::string Nombre::toString() const {
    return firstName + " " + secondName;
    }

///Sobrecarga de operadores
Nombre& Nombre::operator =(const Nombre& n) {
    copyAll(n);
    return *this;
    }
bool Nombre::operator ==(const Nombre& n) const {
    return toString() == n.toString();
    }

bool Nombre::operator!=(const Nombre& n) const {
    return !(*this == n);
    }

bool Nombre::operator<(const Nombre& n) const {
    return toString() < n.toString();
    }

bool Nombre::operator<=(const Nombre& n) const {
    return *this < n or *this == n;
    }

bool Nombre::operator>(const Nombre& n) const {
    return !(*this <= n);
    }

bool Nombre::operator>=(const Nombre& n) const {
    return !(*this < n);
    }

