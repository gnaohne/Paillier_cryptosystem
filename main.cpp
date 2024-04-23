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

    // BigInteger mess("1001");

    // auto key = keyGen();

    // cout << "Encrypting..." << endl;
    // BigInteger c = encrypt(mess, key.n, key.g);

    // BigInteger c("110010100001100111001001010010100010011011001001011110100011111100000000101100110010101001000011011101100001000111101000000110101001110111001110110100010110001110111000010001011001101100110001011110001001011011101110110101111100001111000001001111101000010");

    BigInteger n("10110101110011011110000000110101011100000100011111110110011100011110010000100101100100111000010010001111101001110001010001011001");

    // BigInteger g("1011101001100000000001000010011101000011110110010000011110101110101000110100010000010001101000001011001111101000001010100110111010001011110000001111000001010110000011100111100000000101100011011000110010011111100011110011011011101010101101000111000010010011");

    // BigInteger d("1011010111001101111000000011010101110000010001111111011001110000001100111001010000010111110001010010010110011101110101001010010");

    // cout << "Decrypting..." << endl;
    // BigInteger m = decrypt(c, n, d, g);

    // string decrypted_message = binary_to_message(m.toString());

    // cout << "Decrypted message: " << decrypted_message << endl;

    BigInteger L("10110010010100001000000110011010110000110110000111110111010001010110111111100100111010010001000001000010001000000101000111101101");

    BigInteger mu = mod_inverse(L, n);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Time: " << duration.count() << "s" << endl;

    return 0;
}