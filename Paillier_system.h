#ifndef PAILLIER_CRYPTOSYSTEM_H
#define PAILLIER_CRYPTOSYSTEM_H

#include "BigInteger.h"
#include <chrono>
#include <random>

#define KEY_SIZE 128

auto keyGen();

BigInteger random_in_Zn2(BigInteger n);

BigInteger random_in_Zn(BigInteger n);

BigInteger encrypt(const BigInteger &m, const BigInteger &n, const BigInteger &g);

#endif //PAILLIER_CRYPTOSYSTEM_H