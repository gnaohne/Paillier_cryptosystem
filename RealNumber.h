#ifndef PAILLIER_CRYPTOSYSTEM_REALNUMBER_H
#define PAILLIER_CRYPTOSYSTEM_REALNUMBER_H

#include "BigInteger.h"
#include <string>
#include <algorithm>

class RealNumber {
private:
    BigInteger n;
    int exponent;
public: 
    RealNumber();
    RealNumber(BigInteger n, int exponent);
    RealNumber(double n);
    RealNumber(string double_string);
    
    RealNumber operator+(const RealNumber& other);
    RealNumber operator-(const RealNumber& other);
    RealNumber operator*(const RealNumber& other);
    string toDecimalString();

    int getExponent() const;
    BigInteger getN() const;
    void setN(BigInteger n);
    void setExponent(int exponent);
};

#endif //PAILLIER_CRYPTOSYSTEM_REALNUMBER_H