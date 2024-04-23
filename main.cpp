#include <chrono>
#include "BigInteger.cpp"
#include "Paillier_system.cpp"

int main() {
    auto start = std::chrono::high_resolution_clock::now();
   

    // string message;
    // cout << "Enter the message: ";
    // getline(cin, message);

    // string binary = message_to_binary(message);
    // cout << "Binary message: " << binary << endl;
    // binary = "1" + binary;

    BigInteger mess("1001");

    auto key = keyGen();

    cout << "Encrypting..." << endl;
    BigInteger c = encrypt(mess, key.n, key.g);

    cout << "Decrypting..." << endl;
    BigInteger m = decrypt(c, key.n, key.d, key.g);

    string decrypted_message = binary_to_message(m.toString());

    cout << "Decrypted message: " << decrypted_message << endl;


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Time: " << duration.count() << "s" << endl;

    return 0;
}