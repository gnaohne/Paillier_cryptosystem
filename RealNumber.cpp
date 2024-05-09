#include "RealNumber.h"

RealNumber::RealNumber()
{
    n = BigInteger();
    exponent = 0;
}

RealNumber::RealNumber(BigInteger n, int exponent)
{
    this->n = n;
    this->exponent = exponent;
}

RealNumber::RealNumber(double n)
{
    while (n != (int)n)
    {
        n *= 10;
        this->exponent--;
    }
    this->n = BigInteger(n);
}

RealNumber::RealNumber(string double_string)
{
    int i = 0;
    while (i < double_string.size() && double_string[i] != '.')
    {
        i++;
    }
    if (i == double_string.size())
    {
        n = BigInteger(stoll(double_string, nullptr, 10));
        exponent = 0;
    }
    else
    {
        n = BigInteger(stoll(double_string.substr(0, i) + double_string.substr(i + 1), nullptr, 10));
        exponent = i - double_string.size() + 1;
    }
}

RealNumber RealNumber::operator+(const RealNumber &other)
{
    // x = a * 10^{-2}
    // y = c * 10^{-5}
    int diff = exponent - other.exponent;
    if (diff > 0)
    {
        
        int i = diff % (BIT_PER_DIGIT - 4);
        diff /= (BIT_PER_DIGIT - 4);
        BigInteger temp = BigInteger(n) * BigInteger(pow(10, i));
        for (int j = 0; j < diff; j++)
        {
            temp = temp * BigInteger(pow(10, BIT_PER_DIGIT - 4));
        }
        temp = temp + other.n;
        return RealNumber(temp, other.exponent);
    }
    diff = -diff;
    int i = diff % (BIT_PER_DIGIT - 4);
    diff /= (BIT_PER_DIGIT - 4);
    BigInteger temp = BigInteger(other.n) * BigInteger(pow(10, i));
    for (int j = 0; j < diff; j++)
    {
        temp = temp * BigInteger(pow(10, BIT_PER_DIGIT - 4));
    }
    temp = temp + n;
    return RealNumber(temp, exponent);
}

RealNumber RealNumber::operator-(const RealNumber &other)
{
    RealNumber temp = other;
    temp.n.setSign(-temp.n.getSign());
    return *this + temp;
}

RealNumber RealNumber::operator*(const RealNumber &other)
{
    BigInteger temp = n * other.n;
    return RealNumber(temp, exponent + other.exponent);
}

string RealNumber::toDecimalString()
{
    string res = n.toDecimal();
    if (exponent < 0)
    {
        int i = res.size() + exponent;
        if (i < 0)
        {
            res = "0." + string(-i, '0') + res;
        }
        else
        {
            res.insert(i, ".");
        }
    }
    else
    {
        res += string(exponent, '0');
    }
    return res;
}

int RealNumber::getExponent()
{
    return exponent;
}

BigInteger RealNumber::getN()
{
    return n;
}

void RealNumber::setN(BigInteger n)
{
    this->n = n;
}

void RealNumber::setExponent(int exponent)
{
    this->exponent = exponent;
}
