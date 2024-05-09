#include <chrono>
#include "BigInteger.cpp"
#include "Paillier_system.cpp"
#include "RealNumber.cpp"

int main() {

    // string input_message;
    // cout << "Enter a message: ";
    // getline(cin, input_message);
    
    // string plantext = string_to_binary(input_message);

    // plantext = "1" + plantext;

    // BigInteger mess(plantext);

    // cout << "--------------------------------------------------------" << endl;
    // cout << "Generating key..." << endl;
    // auto key = keyGen();
  
    // auto start = std::chrono::high_resolution_clock::now();  
    // cout << "--------------------------------------------------------" << endl;
    // cout << "Encrypting..." << endl;
    // BigInteger c = encrypt(mess, key.n, key.g);
    // cout << "Encrypted message: " << c.toString() << endl;
    // cout << "c: " << c.toDecimal() <<endl;

    // cout << "--------------------------------------------------------" << endl;
    // cout << "Decrypting..." << endl;
    // BigInteger m = decrypt(c, key.n, key.d, key.mu);

    // string message = m.toString();
    // message = message.substr(1);

    // string decrypted_message = binary_to_string(message);

    // cout << "Decrypted message: " << decrypted_message << endl;
    // cout << "Original message : " << input_message << endl;

    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration = end - start;
    // cout << "Time: " << duration.count() << "s" << endl;

    RealNumber m("3.1416");

    cout << "m = " << m.toDecimalString() << endl;

    cout << "--------------------------------------------------------" << endl;
    cout << "Generating key..." << endl;
    auto key = keyGen();
    
    cout << "Encrypting..." << endl;
    RealNumber c = encrypt(m, key.n, key.g);
    cout << "Encrypt : c = " << c.toDecimalString() << endl;

    cout << "--------------------------------------------------------" << endl;
    cout << "Decrypting..." << endl;
    RealNumber m_decrypt = decrypt(c, key.n, key.d, key.mu);
    cout << "Decrypt : m = " << m_decrypt.toDecimalString() << endl;

    return 0;
}