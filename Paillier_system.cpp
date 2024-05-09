#include "Paillier_system.h"

auto keyGen()
{
    struct key
    {
        // public key
        BigInteger n;
        BigInteger g;
        
        // private key
        BigInteger d;
        BigInteger mu;
    };
    key ans;

    BigInteger p = generate_large_prime(KEY_SIZE);
    cout << "p: " << p.toString() << endl;
    cout << "p: " << p.toDecimal() <<endl;

    
    BigInteger q = generate_large_prime(KEY_SIZE);

    while(q == p)
    {
        q = generate_large_prime(KEY_SIZE);
    }

    cout << "q: " << q.toString() << endl;
    cout << "q: " << q.toDecimal() <<endl;
    cout << endl;

    ans.n = p * q;
    cout << "n: " << ans.n.toString() << endl;
    cout << "n: " << ans.n.toDecimal() <<endl;
    cout << endl;

    BigInteger p_1 = p - BigInteger(1);
    BigInteger q_1 = q - BigInteger(1);
    BigInteger phi = p_1 * q_1;

    BigInteger gcd_n_phin = bezout(ans.n, phi).d;

    while(gcd_n_phin != BigInteger(1))
    {
        q = generate_large_prime(KEY_SIZE);
    }
    
    ans.d = lcm(p_1, q_1);
    cout << "d: " << ans.d.toString() << endl;
    cout << "d: " << ans.d.toDecimal() <<endl;
    cout << endl;

    // g = random in Zn^2
    ans.g = random_in_Zn2(ans.n);
    cout << "g: " << ans.g.toString() << endl;
    cout << "g: " << ans.g.toDecimal() <<endl;
    cout << endl;
    
    // mu = (L(g^d mod n2))^-1 (mod n) with L(x)=(x-1)/n
    BigInteger n2 = ans.n * ans.n;

    BigInteger g_d = ans.g.powMod(ans.d, n2);

    BigInteger L = divide((g_d - BigInteger(1)), ans.n).quotient;

    ans.mu = mod_inverse(L, ans.n);
    cout << "mu: " << ans.mu.toString() << endl;
    cout << "mu: " << ans.mu.toDecimal() <<endl;

    cout << "Done generating key" << endl;

    return ans;
}

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

BigInteger encrypt(const BigInteger &m, const BigInteger &n, const BigInteger &g)
{
    BigInteger r = random_in_Zn(n);

    BigInteger n2 = n * n;

    BigInteger g_m = g.powMod(m, n2);

    BigInteger r_n = r.powMod(n, n2);

    BigInteger c = g_m.mulMod(r_n, n2);

    return c;
}

BigInteger decrypt(const BigInteger &c, const BigInteger &n, const BigInteger &d, const BigInteger &mu)
{
    // m = mu.L(c^d mod n2) mod n
    BigInteger n2 = n * n;

    BigInteger c_d = c.powMod(d, n2);

    BigInteger L_c_d = divide((c_d - BigInteger(1)), n).quotient;
   
    BigInteger m = mu.mulMod(L_c_d, n);

    return m;
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

RealNumber encrypt(const RealNumber &m, const BigInteger &n, const BigInteger &g)
{
    // c = g^m mod n2 * r^n mod n2
    BigInteger m_n = m.getN();

    BigInteger r = random_in_Zn(n);

    BigInteger n2 = n * n;

    BigInteger g_m = g.powMod(m_n, n2);

    BigInteger r_n = r.powMod(n, n2);

    BigInteger c = g_m.mulMod(r_n, n2);

    RealNumber c_real(c, m.getExponent());

    return c_real;
}

RealNumber decrypt(const RealNumber &c, const BigInteger &n, const BigInteger &d, const BigInteger &mu)
{
    // m = mu.L(c^d mod n2) mod n
    BigInteger c_n = c.getN();

    BigInteger n2 = n * n;

    BigInteger c_d = c_n.powMod(d, n2);

    BigInteger L_c_d = divide((c_d - BigInteger(1)), n).quotient;
   
    BigInteger m = mu.mulMod(L_c_d, n);

    RealNumber m_real(m, c.getExponent());

    return m_real;
}
