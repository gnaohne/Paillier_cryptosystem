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

RealNumber::RealNumber(string float_string, int type)
{
    // type = 1: float point 16
    // type = 2: float point 32

    int sign = (float_string[0] == '1') ? -1 : 1;

    int exp_bits = (type == 1) ? 5 : 8;

    int bias = (type == 1) ? 15 : 127;


    string exp_str = float_string.substr(1, exp);
    
    int exponent = 0;

    for (int i = 0; i < exp_bits; i++)
    {
        exponent = (exponent << 1) | (exp_str[i] - '0');
    }

    exponent -= bias;

    string frac_str = float_string.substr(1 + exp_bits);

    long long frac = 0;

    for (int i = 0; i < frac_str.size(); i++)
    {
        frac = (frac << 1) | (frac_str[i] - '0');
    }

    this->exponent = exponent;
    this->n = BigInteger(frac);
}

RealNumber RealNumber::operator+(const RealNumber &other)
{
    // x = a * 10^{-2}
    // y = c * 10^{-5}
    int diff = exponent - other.exponent;
    if (diff > 0)
    {  
        BigInteger temp = other.n;
        temp = temp + n * BigInteger(10).pow(diff);
        return RealNumber(temp, other.exponent);
    }
    diff = -diff;
    BigInteger temp = n;
    temp = temp + other.n * BigInteger(10).pow(diff);
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
            if (res[0] == '.')
            {
                res = "0" + res;
            }
        }
    }
    else
    {
        res += string(exponent, '0');
    }
    return res;
}

int RealNumber::getExponent() const
{
    return exponent;
}

BigInteger RealNumber::getN() const
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
