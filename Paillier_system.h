#ifndef PAILLIER_CRYPTOSYSTEM_H
#define PAILLIER_CRYPTOSYSTEM_H

#include "BigInteger.h"
#include "RealNumber.h"
#include <chrono>
#include <random>
#include <string>
#include <bitset>

#define KEY_SIZE 256

auto keyGen();

BigInteger random_in_Zn2(BigInteger n);

BigInteger random_in_Zn(BigInteger n);

BigInteger encrypt(const BigInteger &m, const BigInteger &n, const BigInteger &g);

BigInteger decrypt(const BigInteger &c, const BigInteger &n, const BigInteger &d, const BigInteger &mu); // d = lamda

string message_to_binary(const string &message);

string binary_to_message(const string &binary);

RealNumber encrypt(const RealNumber &m, const BigInteger &n, const BigInteger &g);

RealNumber decrypt(const RealNumber &c, const BigInteger &n, const BigInteger &d, const BigInteger &mu);

#endif //PAILLIER_CRYPTOSYSTEM_H