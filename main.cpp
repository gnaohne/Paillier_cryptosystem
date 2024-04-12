#include <chrono>
#include "BigInteger.cpp"

int main() {
    // string hex = "D112143E229CA826359782A9D7624714F229BE1A007C1CC420FFE7E6F778D5AC0A61F05736CF956EE82BB2BDF171BEC4340C1A623BFF7CE9FEE04ADF265BCDEE";
    // std::reverse(hex.begin(), hex.end());
    // string binary = hex_to_bin(hex);

    // BigInteger n(binary);
    auto start = std::chrono::high_resolution_clock::now();
    // cout << "Result: " << Miller_Rabin_check(n) << endl;
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration = end - start;
    // cout << "Time: " << duration.count() << "s" << endl;

    BigInteger p = generate_large_prime(512);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Time: " << duration.count() << "s" << endl;
    
    cout << "Prime: " << p.toString() << endl;
    return 0;
}