#include <chrono>
#include "BigInteger.cpp"
#include "Paillier_system.cpp"

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    // int number_test = 10;
    // for(int i = 0; i < number_test; i++)
    // {
    //     auto key = keyGen();
    //     cout << "----------------------------------------------------------" << endl;

    // }

    BigInteger p(13);
    BigInteger q(17);
    BigInteger n = p * q;
    
    BigInteger d = lcm(p - 1, q - 1);
    BigInteger m(123);
    
    BigInteger g = random_in_Zn2(n);

    BigInteger c1 = encrypt(m, n, g);

    BigInteger m_dec1 = decrypt(c1, n, d, g);

    BigInteger c2 = encrypt(m, n, g);

    BigInteger m_dec2 = decrypt(c2, n, d, g);
    

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Time: " << duration.count() << "s" << endl;

    return 0;
}