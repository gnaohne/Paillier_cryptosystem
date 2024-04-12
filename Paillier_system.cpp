#include "Paillier_system.h"

auto keyGen()
{
    struct keyPair
    {
        BigInteger e;
        BigInteger d;
    };
    
    keyPair ans;

    BigInteger p = generate_large_prime(KEY_SIZE);
    BigInteger q = generate_large_prime(KEY_SIZE);

    while(q == p)
    {
        q = generate_large_prime(KEY_SIZE);
    }


    BigInteger n = p * q;

    BigInteger phi = (p - BigInteger(1)) * (q - BigInteger(1));

    // i wanna check gcd(n,(p-1)(q-1)) == 1 use bezout function
    BigInteger gcd_n_phin = bezout(n, phi).d;

    while(gcd_n_phin != BigInteger(1))
    {
        q = generate_large_prime(KEY_SIZE);
    }
    
    // d = lcm((p-1),(q-1))
    ans.d = lcm(p - BigInteger(1), q - BigInteger(1));

    // g = random in Zn^2
    BigInteger g = random_in_Zn2(n);
    

}

BigInteger random_in_Zn2(BigInteger n)
{
    // i wanna g is random number in Zn^2 so g have the same bit with n^2 and satisfy gcd(g,n^2) = 1 
    // it means g is generator of Zn^2
    // n = p*q => n^2 = p^2 * q^2 => bit(n^2) = 2*bit(n)
    // for example p and q is 128 bit so n is 256 bit => n^2 is 512 bit
    // so i wanna g is 512 bit and gcd(g,n^2) = 1
    int bit_size = KEY_SIZE * 4; 

    string binary = "1";

    for(int i = 1; i < bit_size; i++)
    {
        binary += (rand() % 2) ? '1' : '0';
    }

    BigInteger g(binary);

    BigInteger gcd_g_n2 = bezout(g, n * n).d;

    while(gcd_g_n2 != BigInteger(1))
    {
        binary = "1";

        for(int i = 1; i < bit_size; i++)
        {
            binary += (rand() % 2) ? '1' : '0';
        }

        g = BigInteger(binary);

        gcd_g_n2 = bezout(g, n * n).d;
    }

    return g;
}
