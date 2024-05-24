#ifndef PAILLIER_CRYPTOSYSTEM_H
#define PAILLIER_CRYPTOSYSTEM_H

#include "BigInteger.h"
#include "RealNumber.h"
#include <chrono>
#include <random>
#include <string>
#include <bitset>

#define KEY_SIZE 128

BigInteger random_in_Zn2(BigInteger n);

BigInteger random_in_Zn(BigInteger n);

string message_to_binary(const string &message);

string binary_to_message(const string &binary);

class Pailler_sys {
private:
    BigInteger n, g; // public key
    BigInteger lamda, mu; // private key
public: 
    void keyGen();
    Pailler_sys();
    BigInteger getN();
    BigInteger getG();

    RealNumber encrypt(const RealNumber &m);
    RealNumber decrypt(const RealNumber &c);
};

#endif //PAILLIER_CRYPTOSYSTEM_H