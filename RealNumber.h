#ifndef PAILLIER_CRYPTOSYSTEM_REALNUMBER_H
#define PAILLIER_CRYPTOSYSTEM_REALNUMBER_H

#include "BigInteger.h"

class RealNumber {
private:
    BigInteger n;
    int exponent;
public: 
    RealNumber();
    RealNumber(BigInteger n, int exponent);
    RealNumber(double n);
    RealNumber operator+(const RealNumber& other);
    RealNumber operator-(const RealNumber& other);
    RealNumber operator*(const RealNumber& other);
    string toDecimalString();
};

#endif //PAILLIER_CRYPTOSYSTEM_REALNUMBER_H