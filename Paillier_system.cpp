#include "Paillier_system.h"

auto keyGen()
{
    struct key
    {
        BigInteger n;
        BigInteger g;
        
        BigInteger d;
    };
    key ans;

    BigInteger p = generate_large_prime(KEY_SIZE);
    cout << "p: " << p.toString() << endl;

    
    BigInteger q = generate_large_prime(KEY_SIZE);

    while(q == p)
    {
        q = generate_large_prime(KEY_SIZE);
    }

    cout << "q: " << q.toString() << endl;

    ans.n = p * q;
    cout << "n: " << ans.n.toString() << endl;

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

    // g = random in Zn^2
    cout << "Generating g..." << endl;
    ans.g = random_in_Zn2(ans.n);
    cout << "g: " << ans.g.toString() << endl;

    // mu = (L(g^d mod n2))^-1 (mod n) with L(x)=(x-1)/n
    
    // BigInteger g_d = ans.g.powMod(ans.d, ans.n * ans.n);

    // BigInteger L = divide((g_d - BigInteger(1)), ans.n).quotient;

    // BigInteger mu = mod_inverse(L, ans.n);

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
    BigInteger c = g.powMod(m,n2) * r.powMod(n,n2);
    c = c.mod(n2);
    return c;
}

BigInteger decrypt(const BigInteger &c, const BigInteger &n, const BigInteger &d, const BigInteger &g)
{
    BigInteger n2 = n * n;
    // mu = (L(g^d mod n2))^-1 (mod n) with L(x)=(x-1)/n

    BigInteger g_d = g.powMod(d, n2);
    BigInteger L = divide((g_d - BigInteger(1)), n).quotient;
    BigInteger mu = mod_inverse(L, n);

    // m = mu.L(c^d mod n2) mod n
    BigInteger c_d = c.powMod(d, n2);
    BigInteger L_c_d = divide((c_d - BigInteger(1)), n).quotient;
    BigInteger m = (mu * L_c_d).mod(n);

    return m;
}
