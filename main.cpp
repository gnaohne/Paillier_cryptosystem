#include <chrono>
#include "BigInteger.cpp"
#include "Paillier_system.cpp"

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
    // auto key = keyGen();

    // BigInteger a(18);
    // BigInteger c = a << 212;

    BigInteger a("111101011001011000110111111111011001110001010001100000101110000");
    BigInteger b(4);
    BigInteger temp = b << 60;
    cout << "a = " << a.toString() << endl;
    cout << "temp = " << temp.toString() << endl;
    
    BigInteger d = a - temp;
    cout << "d = " << d.toString() << endl;

    // cout << c.toString() << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Time: " << duration.count() << "s" << endl;

    return 0;
}