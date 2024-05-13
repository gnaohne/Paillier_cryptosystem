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
    int pos = double_string.find('.');

    if (pos == string::npos)
    {
        n = BigInteger(stoll(double_string, nullptr, 10));
        exponent = 0;
    }
    else
    {
        n = BigInteger(stoll(double_string.substr(0, pos) + double_string.substr(pos + 1), nullptr, 10));
        exponent = pos - double_string.size() + 1;
    }
}

RealNumber::RealNumber(string float_string, int type)
{
    // float_string in binary
    // sign | exp | mantissa

    // type = 1: float point 16
    // type = 2: float point 32

    int sign = (float_string[0] == '1') ? -1 : 1;

    int exp_bits = (type == 1) ? 5 : 8;

    int bias = (type == 1) ? 15 : 127;

    int exp = 0;
    for (int i = 1; i <= exp_bits; i++)
    {
        exp = exp * 2 + (float_string[i] - '0');
    }
    exp -= bias;

    string mantissa = float_string.substr(exp_bits + 1);

    double mantissa_value = 1.0;
    
    double factor = 0.5; 
    
    for (int i = 0; i < mantissa.size(); i++)
    {
        if (mantissa[i] == '1')
        {
            mantissa_value += factor;
        }
        factor /= 2;
    }

    double value = mantissa_value * pow(2, exp);
    
    stringstream ss;

    if (type == 1)
    {
        ss << std::fixed << std::setprecision(PrecisionFP16) << value;
    }
    else
    {
        ss << std::fixed << std::setprecision(PrecisionFP32) << value;
    }
    
    string double_string = ss.str();
    
    while (double_string.back() == '0')
    {
        double_string.pop_back();
    }

    int pos = double_string.find('.');

    if (pos == string::npos)
    {
        n = BigInteger(double_string, 10, sign);
        exponent = 0;
    }
    else
    {
        string temp = double_string.substr(0, pos) + double_string.substr(pos + 1);
        n = BigInteger(temp, 10, sign);
        exponent = pos - double_string.size() + 1;
    }
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
    int sign = n.getSign();

    BigInteger temp = n;
    if (sign == -1)
    {
        temp = n.abs();
    }

    string res = temp.toDecimal();
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

    if (sign == -1)
    {
        res = "-" + res;
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

string random_FP16()
{
    srand(time(0));
    string res = "";
    for (int i = 0; i < 16; i++)
    {
        res += to_string(rand() % 2);
    }
    return res;
}

string random_FP32()
{
    srand(time(0));
    string res = "";
    for (int i = 0; i < 32; i++)
    {
        res += to_string(rand() % 2);
    }
    return res;
}
