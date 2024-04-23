//
// Created by as on 4/12/2024.
//

#ifndef PAILLIER_CRYPTOSYSTEM_BIGINTEGER_H
#define PAILLIER_CRYPTOSYSTEM_BIGINTEGER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

#define ll long long
const int BIT_PER_DIGIT = 61;
const ll BASE = 1ll << BIT_PER_DIGIT;

using TYPE = ll;

int Primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
                127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
                179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
                233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
                283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
                353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
                419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
                467, 479, 487, 491, 499, 503, 509, 521, 523, 541};

class BigInteger {
private:
    vector<TYPE> digits;
    int sign;

public:
    BigInteger();

    BigInteger(const string &s);

    BigInteger(TYPE l);

    BigInteger(const BigInteger &other);

    void trim();

    BigInteger abs() const;

    void setDigits(const vector<TYPE> &digit);

    void setSign(int s);

    const vector<TYPE> &getDigits() const;

    int getSign() const;

    int size() const;

    bool operator==(const BigInteger &a) const { return digits == a.digits && sign == a.sign; }

    bool operator!=(const BigInteger &a) const { return !(*this == a); }

    bool operator<(const BigInteger &a);

    bool operator<=(const BigInteger &a);

    bool operator>(const BigInteger &a);

    bool operator>=(const BigInteger &a);

    BigInteger operator+(const BigInteger &a) const;

    BigInteger operator-(const BigInteger &a) const;

    BigInteger operator*(const BigInteger &a) const;

    BigInteger operator%=(const BigInteger &a);

    BigInteger operator>>(int i);

    BigInteger operator<<(int i);

    string toString() const;

    bool is_zero() const;

    bool is_even() const;

    BigInteger mod(const BigInteger &mod) const;

    BigInteger addMod(const BigInteger &other, const BigInteger &mod) const;

    BigInteger mulMod(const BigInteger &other, const BigInteger &mod) const;

    BigInteger powMod(const BigInteger &a, const BigInteger &mod) const;

    int bitLength() const;
};

int msbPosition(ll x);

auto bezout(const BigInteger &x, const BigInteger &y);

auto divide(const BigInteger &a, const BigInteger &b);

BigInteger lcm(const BigInteger &x, const BigInteger &y);

bool Miller_Rabin_check(const BigInteger &n);

string hex_to_bin(const string &hex);

BigInteger generate_large_prime(int bit_length);

BigInteger mod_inverse(const BigInteger &a, const BigInteger &n);

#endif //PAILLIER_CRYPTOSYSTEM_BIGINTEGER_H
