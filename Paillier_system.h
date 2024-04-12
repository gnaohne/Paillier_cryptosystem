#ifndef PAILLIER_CRYPTOSYSTEM_H
#define PAILLIER_CRYPTOSYSTEM_H

#include "BigInteger.h"

#define KEY_SIZE 128

auto keyGen();

BigInteger random_in_Zn2(BigInteger n);

#endif //PAILLIER_CRYPTOSYSTEM_H