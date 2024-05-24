#include <chrono>
#include "BigInteger.cpp"
#include "Paillier_system.cpp"
#include "RealNumber.cpp"
#include <fstream>

int main() {
    Pailler_sys paillier;
    
    string rand = random_FP32();
    cout << "Random number: " << rand << endl;
    RealNumber m(rand, FP32);
    
    RealNumber c = paillier.encrypt(m);

    cout << "Encrypted number: " << c.toDecimalString() << endl;

    RealNumber m_dec = paillier.decrypt(c);

    cout << "Decrypted number: " << m_dec.toDecimalString() << endl;
    return 0;
}