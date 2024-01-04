#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <iostream>
#include <string>

class Integer {
private:
    long long int data;

public:
    Integer();

    Integer(const Integer&);

    Integer(const long long int&);

    std::string toString() const;

    void setInteger(const long long int&);

    long long int getInteger()const;

    Integer& operator ++ ();

    Integer operator ++ (int);

    Integer& operator -- ();

    Integer operator -- (int);

    Integer operator + (const Integer&) const;

    Integer operator - (const Integer&) const;

    Integer operator * (const Integer&) const;

    Integer operator / (const Integer&) const;

    Integer operator % (const Integer&) const;

    Integer operator - () const;

    Integer& operator = (const Integer&);

    Integer& operator += (const Integer&);

    Integer& operator -= (const Integer&);

    Integer& operator *= (const Integer&);

    Integer& operator /= (const Integer&);

    Integer& operator %= (const Integer&);

    bool operator == (const Integer&) const;

    bool operator != (const Integer&) const;

    bool operator < (const Integer&) const;

    bool operator <= (const Integer&) const;

    bool operator > (const Integer&) const;

    bool operator >= (const Integer&) const;

    friend std::istream& operator >> (std::istream&, Integer&);

    friend std::ostream& operator << (std::ostream&, const Integer&);
};

#endif // INTEGER_H_INCLUDED
