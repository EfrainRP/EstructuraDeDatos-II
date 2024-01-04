#include <iostream>
#include <fstream>
#include <string>

#include "Integer.h"

using namespace std;

///Costructor
Integer::Integer() {}

Integer::Integer(const Integer& _integer): data(_integer.data) {}

Integer::Integer(const long long int& _data) : data(0) {}

string Integer::toString() const {
    return to_string(data);
}

void Integer::setInteger(const long long int& i) {
    data = i;
}

long long int Integer::getInteger() const {
    return data;
}

Integer& Integer::operator++() {//Version prefija
    return *this;
}

Integer Integer::operator++(int) {//Version postfija
    Integer old = *this;
    operator++();
    return old;
}

Integer& Integer::operator--() {//Version prefija
    return *this;
}

Integer Integer::operator--(int) {//Version postfija
    Integer old = *this;
    operator--();
    return old;
}

Integer Integer::operator+(const Integer& i) const {
    return data + i.data;
}

Integer Integer::operator-(const Integer& i) const {
    return data - i.data;
}

Integer Integer::operator*(const Integer& i) const {
    return data * i.data;
}

Integer Integer::operator/(const Integer& i) const {
    return data / i.data;
}

Integer Integer::operator%(const Integer& i) const {
    return data % i.data;
}

Integer Integer::operator-() const {
    return data;
}

Integer& Integer::operator=(const Integer& i) {
    data = i.data;
    return *this;
}

Integer& Integer::operator+=(const Integer& i) {
    data = data + i.data;
    return *this;
}

Integer& Integer::operator-=(const Integer& i) {
    return *this = *this - i.data;
}

Integer& Integer::operator*=(const Integer& i) {
    return *this = *this * i.data;
}

Integer& Integer::operator/=(const Integer& i) {
    return *this = *this / i.data;
}

Integer& Integer::operator%=(const Integer& i) {
    return *this = *this % i.data;
}

bool Integer::operator==(const Integer& i) const {
    return data == i.data;
}

bool Integer::operator!=(const Integer& i) const {
    return !(*this == i);
}

bool Integer::operator<(const Integer& i) const {
    return data < i.data;
}

bool Integer::operator<=(const Integer& i) const {
    return (*this < i) or (*this == i);
}

bool Integer::operator>(const Integer& i) const {
    return !(*this <= i);
}

bool Integer::operator>=(const Integer& i) const {
    return !(*this < i);
}

istream& operator >> (istream& is, Integer& i) {
    string str;
    getline(is,str,'*');
    i.data = atoi (str.c_str());
    return is;
}

ostream& operator << (ostream& os, const Integer& i) {
    os << i.data << '*';
}
