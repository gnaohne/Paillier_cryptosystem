#include "Paillier_system.h"

auto keyGen()
{
    struct key
    {
        BigInteger n;
        BigInteger g;
        
        BigInteger d;
    };
    cout << "Generating key..." << endl;
    key ans;

    cout << "Generating p..." << endl;
    BigInteger p = generate_large_prime(KEY_SIZE);
    
    cout << "Generating q..." << endl;
    BigInteger q = generate_large_prime(KEY_SIZE);

    while(q == p)
    {
        q = generate_large_prime(KEY_SIZE);
    }

    cout << "p: " << p.toString() << endl;
    cout << "q: " << q.toString() << endl;

    ans.n = p * q;
    cout << "n: " << ans.n.toString() << endl;

    BigInteger p_1 = p - BigInteger(1);
    BigInteger q_1 = q - BigInteger(1);
    BigInteger phi = p_1 * q_1;

    // i wanna check gcd(n,(p-1)(q-1)) == 1 use bezout function
    BigInteger gcd_n_phin = bezout(ans.n, phi).d;

    while(gcd_n_phin != BigInteger(1))
    {
        q = generate_large_prime(KEY_SIZE);
    }
    
    // d = lcm((p-1),(q-1))
    ans.d = lcm(p_1, q_1);
    cout << "d: " << ans.d.toString() << endl;

    // g = random in Zn^2
    cout << "Generating g..." << endl;
    ans.g = random_in_Zn2(ans.n);

    // mu = (L(g^d mod n2))^-1 (mod n) with L(x)=(x-1)/n
    
    BigInteger g_d = ans.g.powMod(ans.d, ans.n * ans.n);

    BigInteger L = divide((g_d - BigInteger(1)), ans.n).quotient;

    BigInteger mu = mod_inverse(L, ans.n);

    return ans;
}

BigInteger random_in_Zn2(BigInteger n)
{
    // i wanna g is random number in Zn^2 so g have the same bit with n^2 and satisfy gcd(g,n^2) = 1 
    // it means g is generator of Zn^2
    // n = p*q => n^2 = p^2 * q^2 => bit(n^2) = 2*bit(n)
    // for example p and q is 128 bit so n is 256 bit => n^2 is 512 bit
    // so i wanna g is 512 bit and gcd(g,n^2) = 1
    
    auto start = chrono::high_resolution_clock::now();

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
        cout << "Generating g..." << endl;
        binary = "1";

        for(int i = 1; i < bit_size; i++)
        {
            binary += (rand() % 2) ? '1' : '0';
        }

        g = BigInteger(binary);

        gcd_g_n2 = bezout(g, n * n).d;
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Time to generate g: " << duration.count() << " ms" << endl;
    return g;
}
