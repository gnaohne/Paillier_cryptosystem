#include <chrono>
#include "BigInteger.cpp"
#include "Paillier_system.cpp"

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
    BigInteger a("1000100001000101101011011101010010100111010111001010111000011000101010100100101001010110111110110001110010011110001111010111000111110010001010000110100010100100110000100001101001101101011101111110101011001011000110111111111011001110001010001100000101110000");
    BigInteger b(4);
    auto c = divide(a, b);

    cout << "a / b = " << c.quotient.toString() << endl;
    cout << "a % b = " << c.remainder.toString() << endl;

    // auto key = keyGen();
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Time: " << duration.count() << "s" << endl;

    return 0;
}