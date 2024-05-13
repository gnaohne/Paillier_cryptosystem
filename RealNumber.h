#ifndef PAILLIER_CRYPTOSYSTEM_REALNUMBER_H
#define PAILLIER_CRYPTOSYSTEM_REALNUMBER_H

#include "BigInteger.h"
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <random>

#define FP16 1
#define FP32 2
#define PrecisionFP16 15 // 15 decimal places
#define PrecisionFP32 46 // 46 decimal places

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
string random_FP16();
string random_FP32();

#endif //PAILLIER_CRYPTOSYSTEM_REALNUMBER_H