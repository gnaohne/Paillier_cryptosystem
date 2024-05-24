#include "Paillier_system.h"

BigInteger random_in_Zn2(BigInteger n)
{    
    std::mt19937_64 rng(std::random_device{}()); 
    std::uniform_int_distribution<uint64_t> dist(0, 1); 

    int bit_size = n.bitLength() * 2; 

    BigInteger g;

    do {
        string binary;
        for(int i = 0; i < bit_size - 1; i++)
        {
            binary += std::to_string(dist(rng));
        }

        binary += "1";

        g = BigInteger(binary);

    } while (bezout(g, n * n).d != BigInteger(1));
    return g;
}

BigInteger random_in_Zn(BigInteger n)
{
    std::mt19937_64 rng(std::random_device{}()); 
    std::uniform_int_distribution<uint64_t> dist(0, 1); 

    BigInteger r;

    int n_bit_size = n.bitLength();

    do {
        string binary;
        for(int i = 0; i < n_bit_size - 1; i++)
        {
            binary += std::to_string(dist(rng));
        }

        binary += "1";

        r = BigInteger(binary);

    } while (bezout(r, n * n).d != BigInteger(1));
    return r;
}

string message_to_binary(const string &message)
{
    string binary;
    for(char c : message)
    {
        binary += std::bitset<8>(c).to_string();
    }
    return binary;
}

string binary_to_message(const string &binary)
{
    string message;
    for(int i = 0; i < binary.size(); i += 8)
    {
        string byte = binary.substr(i, 8);
        char c = (char)std::bitset<8>(byte).to_ulong();
        message += c;
    }
    return message;
}

void Pailler_sys::keyGen()
{
    BigInteger p = generate_large_prime(KEY_SIZE);

    BigInteger q = generate_large_prime(KEY_SIZE);

    while(q == p)
    {
        q = generate_large_prime(KEY_SIZE);
    }

    this->n = p * q;
    
    BigInteger p_1 = p - BigInteger(1);
    BigInteger q_1 = q - BigInteger(1);
    BigInteger phi = p_1 * q_1;

    BigInteger gcd_n_phin = bezout(this->n, phi).d;

    while(gcd_n_phin != BigInteger(1))
    {
        q = generate_large_prime(KEY_SIZE);
    }
    
    this->lamda = lcm(p_1, q_1);
    
    BigInteger n2 = this->n * this->n;

    do
    {
        this->g = random_in_Zn2(this->n);
    } while (bezout(this->g, n2).d != BigInteger(1)); 
    

    // mu = (L(g^d mod n2))^-1 (mod n) with L(x)=(x-1)/n
    BigInteger g_d = this->g.powMod(this->lamda, n2);

    BigInteger L = divide((g_d - BigInteger(1)), this->n).quotient;

    this->mu = mod_inverse(L, this->n);
}

Pailler_sys::Pailler_sys()
{
    keyGen();
}

BigInteger Pailler_sys::getN()
{
    return this->n;
}

BigInteger Pailler_sys::getG()
{
    return this->g;
}

RealNumber Pailler_sys::encrypt(const RealNumber &m)
{
    int sign = m.getN().getSign();

    // c = g^m mod n2 * r^n mod n2
    BigInteger m_n = m.getN();

    BigInteger r = random_in_Zn(this->n);

    BigInteger n2 = this->n * this->n;

    BigInteger g_m = this->g.powMod(m_n, n2);

    BigInteger r_n = r.powMod(n, n2);

    BigInteger c = g_m.mulMod(r_n, n2);
    c.setSign(sign);

    RealNumber c_real(c, m.getExponent());

    return c_real;
}

RealNumber Pailler_sys::decrypt(const RealNumber &c)
{
    int sign = c.getN().getSign();

    // m = mu.L(c^d mod n2) mod n
    BigInteger c_n = c.getN();

    BigInteger n2 = this->n * this->n;

    BigInteger c_d = c_n.powMod(this->lamda, n2);

    BigInteger L_c_d = divide((c_d - BigInteger(1)), n).quotient;
   
    BigInteger m = this->mu.mulMod(L_c_d, n);
    m.setSign(sign);
    
    RealNumber m_real(m, c.getExponent());

    return m_real;
}
