#include <chrono>
#include "BigInteger.cpp"
#include "Paillier_system.cpp"
#include "RealNumber.cpp"
#include <fstream>

int main() {
    // double a = -0.036773681640625;
    // cout << a << endl;

    // i want run 100 times encryption and decryption a FP16 number
    // and measure the time it takes to encrypt and decrypt 
    // and minimize, maximize the time it takes to encrypt and decrypt
    // write down it to file 
    // and calculate the average time it takes to encrypt and decrypt

    ofstream file;
    file.open("time_fp16_128.txt");
    if (!file) {
        cout << "Unable to open file";
        exit(1);
    }

    auto time_min_encrypt = 1000000;
    auto time_max_encrypt = 0;
    auto time_min_decrypt = 1000000;
    auto time_max_decrypt = 0;
    auto total_encrypt = 0;
    auto total_decrypt = 0;
    auto average_encrypt = 0;
    auto average_decrypt = 0;

    for (int i = 0; i < 100; i++) {
        file << "Test " << i + 1 << endl;
        string rand = random_FP16();
        file << "Random number: " << rand << endl;
        RealNumber m(rand, FP16);
        
        file << "Real number: " << m.toDecimalString() << endl;

        auto key = keyGen();
        
        auto start = chrono::high_resolution_clock::now();
        file << "Encrypting..." << endl;
        RealNumber c = encrypt(m, key.n, key.g);
        file << "Encrypted number: " << c.toDecimalString() << endl;
        auto end = chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        total_encrypt += duration.count();
        if (duration.count() < time_min_encrypt) {
            time_min_encrypt = duration.count();
        }
        if (duration.count() > time_max_encrypt) {
            time_max_encrypt = duration.count();
        }
        file << duration.count() << endl;
        file << "--------------------------------------------------------" << endl;
        
        auto start_decrypt = chrono::high_resolution_clock::now();
        file << "Decrypting..." << endl;
        RealNumber m_decrypt = decrypt(c, key.n, key.d, key.mu);
        file << "Decrypted number: " << m_decrypt.toDecimalString() << endl;
        auto end_decrypt = chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_decrypt = (end_decrypt - start_decrypt);
        total_decrypt += duration_decrypt.count();
        if (duration_decrypt.count() < time_min_decrypt) {
            time_min_decrypt = duration_decrypt.count();
        }
        if (duration_decrypt.count() > time_max_decrypt) {
            time_max_decrypt = duration_decrypt.count();
        }
        file << duration_decrypt.count() << endl;
        file << "********************************************************" << endl;
        file << endl;
    }

    average_encrypt = total_encrypt / 100;
    average_decrypt = total_decrypt / 100;
    file << "Time min encrypt: " << time_min_encrypt << endl;
    file << "Time max encrypt: " << time_max_encrypt << endl;
    file << "Average time encrypt: " << average_encrypt << endl;
    file << "Time min decrypt: " << time_min_decrypt << endl;

    file.close();
    return 0;
}