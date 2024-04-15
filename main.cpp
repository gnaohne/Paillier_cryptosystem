#include <chrono>
#include "BigInteger.cpp"
#include "Paillier_system.cpp"

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
    // BigInteger a("111101011001011000110111111111011001110001010001100000101110000");
    // BigInteger b(4);
    
    // b = b << (253);


    // cout << "a = " << a.toString() << endl;
    // cout << "b = " << b.toString() << endl;

    // BigInteger c = a - b;

    // cout << "a - b = " << c.toString() << endl;

    // auto c = divide(a, b);
    // BigInteger temp = b << 60;
    // cout << "a = " << a.toString() << endl;
    // cout << "temp = " << temp.toString() << endl;

    // BigInteger e("11101011001011000110111111111011001110001010001100000101110000");

    // BigInteger d = a - temp;
    // cout << "a - temp = " << d.toString() << endl;

    // cout << "a / b = " << c.quotient.toString() << endl;
    // cout << "a % b = " << c.remainder.toString() << endl;
    
    auto key = keyGen();
    
    // BigInteger n("101011001011000110111111111011001110001010001100000101110000");
    
    // compare n and b
    // bool check = n >= b;
    // cout << "n >= b: " << check << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Time: " << duration.count() << "s" << endl;

    return 0;
}