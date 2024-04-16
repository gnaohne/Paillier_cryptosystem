#include <chrono>
#include "BigInteger.cpp"
#include "Paillier_system.cpp"

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
    auto key = keyGen();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Time: " << duration.count() << "s" << endl;

    return 0;
}