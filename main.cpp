#include <chrono>
#include "BigInteger.cpp"
#include "Paillier_system.cpp"

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    BigInteger mess("1001");

    auto key = keyGen();

    cout << "Encrypting..." << endl;
    BigInteger c = encrypt(mess, key.n, key.g);

    cout << "Decrypting..." << endl;
    BigInteger m = decrypt(c, key.n, key.d, key.g);

    string message = m.toString();

    cout << "Decrypted message: " << message << endl;


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Time: " << duration.count() << "s" << endl;

    return 0;
}