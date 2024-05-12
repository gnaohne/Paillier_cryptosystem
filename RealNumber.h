#ifndef PAILLIER_CRYPTOSYSTEM_REALNUMBER_H
#define PAILLIER_CRYPTOSYSTEM_REALNUMBER_H

#include "BigInteger.h"
#include <string>
#include <algorithm>

#define FP16 1
#define FP32 2

class RealNumber {
private:
    BigInteger n;
    int exponent;
public: 
    RealNumber();
    RealNumber(BigInteger n, int exponent);
    RealNumber(double n);
    RealNumber(string double_string);
    RealNumber(string float_string, int type);
    
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