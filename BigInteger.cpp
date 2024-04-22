//
// Created by as on 4/12/2024.
//

#include "BigInteger.h"

BigInteger::BigInteger() {
    digits.clear();
    sign = 1;
}

BigInteger::BigInteger(const string &s) {
    string binary = s;
    digits.clear();
    sign = 1;
    if (binary[0] == '-') {
        sign = -1;
        binary = binary.substr(1);
    }

    reverse(binary.begin(), binary.end());
    int pos = 0;
    while (pos < binary.size()) {
        TYPE value = 0;
        for (int i = pos; i < pos + BIT_PER_DIGIT && i < binary.size(); i++) {
            value += (binary[i] - '0') * (TYPE(1) << (i - pos));
        }
        digits.push_back(value);
        pos += BIT_PER_DIGIT;
    }
    this->trim();
}

BigInteger::BigInteger(TYPE l) {
    if (l < 0) {
        sign = -1;
        l = -l;
    } else {
        sign = 1;
    }

    if (l == 0) {
        digits.push_back(0);
        return;
    }

    while (l > 0) {
        digits.push_back(l % (1ll << BIT_PER_DIGIT));
        l /= (1ll << BIT_PER_DIGIT);
    }
}

BigInteger::BigInteger(const BigInteger &other) {
    digits = other.digits;
    sign = other.sign;
}

BigInteger BigInteger::abs() const {
    BigInteger res(*this);
    res.sign = 1;
    return res;
}

void BigInteger::setDigits(const vector<TYPE> &digit) {
    BigInteger::digits = digit;
}

void BigInteger::setSign(int s) {
    BigInteger::sign = s;
}

const vector<TYPE> &BigInteger::getDigits() const {
    return digits;
}

int BigInteger::getSign() const {
    return sign;
}

bool BigInteger::operator<(const BigInteger &a) {
    if (sign != a.sign) return sign < a.sign;

    bool is_negative = (sign == -1);

    int n = size();
    int m = a.size();
    if (n < m) return !is_negative;
    if (n > m) return is_negative;

    for (int i = n - 1; i >= 0; i--) {
        if (digits[i] < a.digits[i]) return !is_negative;
        if (digits[i] > a.digits[i]) return is_negative;
    }
    return false;
}

int BigInteger::size() const {
    return digits.size();
}

bool BigInteger::operator<=(const BigInteger &a) {
    if (sign != a.sign) return sign < a.sign;
    bool is_negative = (sign == -1);

    int n = size();
    int m = a.size();
    if (n < m) return !is_negative;
    if (n > m) return is_negative;
    for (int i = n - 1; i >= 0; i--) {
        if (digits[i] < a.digits[i]) return !is_negative;
        if (digits[i] > a.digits[i]) return is_negative;
    }
    return true;
}

bool BigInteger::operator>(const BigInteger &a) {
    return !(*this <= a);
}

bool BigInteger::operator>=(const BigInteger &a) {
    return !(*this < a);
}

BigInteger BigInteger::operator+(const BigInteger &a) const {
    int n = size();
    int m = a.size();
    BigInteger ans;
    ans.digits.resize(max(n, m) + 1);

    if (sign == a.sign) {
        ans.sign = sign;
        ll carry = 0;
        ll sum = 0;
        for (int i = 0; i < max(n, m); i++) {
            sum = carry;
            if (i < n) sum += digits[i];
            if (i < m) sum += a.digits[i];
            ans.digits[i] = sum % BASE;
            carry = sum / BASE;
        }
        ans.digits[max(n, m)] = carry;
        ans.trim();
        return ans;
    } 
    if (this->abs() >= a.abs()) {
        ans.sign = sign;
        ll carry = 0;
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            sum = carry + digits[i];
            if (i < m) sum -= a.digits[i];
            if (sum < 0) { 
                sum += BASE;
                carry = -1;
            } else {
                carry = 0;
            }
            ans.digits[i] = sum;
        }
        ans.trim();
        return ans;
    }
    ans.sign = a.sign;
    int carry = 0;
    ll sum = 0;
    for (int i = 0; i < m; i++) {
        sum = carry + a.digits[i];
        if (i < n) sum -= digits[i];
        if (sum < 0) {
            sum += BASE;
            carry = -1;
        } else {
            carry = 0;
        }
        ans.digits[i] = sum;
    }
    ans.trim();
    return ans;
}

BigInteger BigInteger::operator-(const BigInteger &a) const {
    BigInteger temp(a);
    temp.sign = -temp.sign;
    return *this + temp; 
}

void BigInteger::trim() {
    while (!digits.empty() && !digits.back()) {
        digits.pop_back();
    }
    if (digits.empty()) {
        digits.push_back(0);
        sign = 1;
    }
}

BigInteger BigInteger::operator*(const BigInteger &a) const {
    BigInteger res;
    if (digits.empty() || a.getDigits().empty()) {
        return res;
    }

    BigInteger temp(*this);

    vector<TYPE> y = a.getDigits();

    for (size_t i = 0; i < y.size() * BIT_PER_DIGIT; ++i) {
        if (y[i / BIT_PER_DIGIT] & (1ll << (i % BIT_PER_DIGIT))) {
            res = res + temp;
        }
        temp = temp + temp;
    }

    return res;
}

string BigInteger::toString() const {
    if (is_zero()) return "0";
    string binary = "";
    for (TYPE val: digits) {
        for (int i = 0; i < BIT_PER_DIGIT; i++) {
            binary += (val & (TYPE(1) << i)) ? '1' : '0';
        }
    }

    while (binary.size() > 1 && binary.back() == '0') {
        binary.pop_back();
    }

    reverse(binary.begin(), binary.end());
    if (sign == -1) {
        binary = '-' + binary;
    }
    return binary;
}

bool BigInteger::is_zero() const {
    return digits.empty() || (digits.size() == 1 && digits[0] == 0);
}

BigInteger BigInteger::addMod(const BigInteger &other, const BigInteger &mod) const {
    if (this->is_zero()) {
        return other.mod(mod);
    }
    if (other.is_zero()) {
        return this->mod(mod);
    }
    BigInteger temp(*this);
    BigInteger res = temp + other;
    return res.mod(mod);
}

BigInteger BigInteger::mod(const BigInteger &mod) const {
    BigInteger temp(*this);

    BigInteger abs_mod = mod.abs();

    while (temp >= abs_mod) {
        temp = temp - abs_mod;
    }
    return temp;
}

BigInteger BigInteger::mulMod(const BigInteger &other, const BigInteger &mod) const {
    BigInteger res;
    if (this->is_zero() || other.is_zero())
        return res;
    BigInteger temp(*this);
    BigInteger abs_mod = mod.abs();

    vector<TYPE> y = other.getDigits();

    for (size_t i = 0; i < y.size() * BIT_PER_DIGIT; ++i) {
        if (y[i / BIT_PER_DIGIT] & (1ll << (i % BIT_PER_DIGIT))) {
            res = res.addMod(temp, abs_mod);
        }
        temp = temp.addMod(temp, abs_mod);
    }
    return res;
}

BigInteger BigInteger::powMod(const BigInteger &a, const BigInteger &mod) const {
    BigInteger res("1");
    BigInteger temp(*this);
    if (a.is_zero())
        return res;
    BigInteger abs_mod = mod.abs();
    vector<TYPE> y = a.getDigits();

    for (int i = y.size() * BIT_PER_DIGIT - 1; i >= 0; --i) {
        if (res.size() != 1 || res.getDigits()[0] != 1) {
            res = res.mulMod(res, mod);
        }
        if (y[i / BIT_PER_DIGIT] & (1ll << (i % BIT_PER_DIGIT))) {
            res = res.mulMod(temp, mod);
        }
    }
    return res;
}

BigInteger BigInteger::operator>>(int i) { 
    if (i < 0) {
        throw "Shift right must be positive";
    }

    if (i == 0) return *this;

    ll value = (ll)1 << (i);
    value--; // set i bits to 1

    int n = size();
    BigInteger ans;
    ans.sign = sign;
    ans.digits.resize(n);

    int shilfS = i / BIT_PER_DIGIT;
    // remove shilfS last digits    
    for (int j = 0; j < n; j++) {
        if (j + shilfS < n) {
            ans.digits[j] = digits[j + shilfS];
        }
    }
    
    int shilf = i % BIT_PER_DIGIT;
    ll carry = 0;
    for (int j = n - 1; j >= 0; j--) {
        ans.digits[j] = ans.digits[j] & (1ll << BIT_PER_DIGIT - 1);
        if (j == n - 1) {
            carry = digits[j] & value; // get the last i bits
            ans.digits[j] = digits[j] >> shilf;
        } else {
            // n = n1{101} n2{010}
            // n >> 1 = n1{10} n2{101}

            ll temp = carry;
            carry = digits[j] & value;
            // put the last i bits of the previous number to the first i bits of the current number
            ans.digits[j] = (digits[j] >> shilf) | (temp << (BIT_PER_DIGIT - shilf)); 
        }
    }
    ans.trim();
    return ans;
}

BigInteger BigInteger::operator<<(int i) {
    if(i < 0) {
        throw "Shift left must be positive";
    }
    
    if (i == 0) return *this;
    
    int digitShift = i / BIT_PER_DIGIT; // number of digits to shift
    int bitShift = i % BIT_PER_DIGIT; // number of bits to shift

    BigInteger ans;
    ans.sign = sign;
    ans.digits.resize(digits.size() + digitShift + 1, 0);
    
    for (int j = 0; j < digits.size(); j++) {
        // Apply the bit shift and mask to ensure values stay within BIT_PER_DIGIT bits
        ll lower_part = (digits[j] << bitShift) & (BASE - 1);
        ans.digits[j + digitShift] |= lower_part;

        if (j + digitShift + 1 < ans.digits.size()) {
            // Calculate the upper part that will spill over to the next digit
            ll upper_part = digits[j] >> (BIT_PER_DIGIT - bitShift);
            ans.digits[j + digitShift + 1] |= upper_part;
        }
    }

    ans.trim();
    return ans;
}

bool BigInteger::is_even() const {
    return (digits[0] % 2 == 0);
}

BigInteger BigInteger::operator%=(const BigInteger &a) {
    *this = this->mod(a);
    return *this;
}

auto bezout(const BigInteger &x, const BigInteger &y) {
    struct Ans {
        BigInteger a, b;
        BigInteger d; // Bezout => ax + by = gcd(x,y) = d
    };

    BigInteger temp_x, temp_y;

    if (x.is_zero()) {
        return Ans{BigInteger("0"), BigInteger("1"), y};
    }
    if (y.is_zero()) {
        return Ans{BigInteger("1"), BigInteger("0"), x};
    }

    int sign_x = x.getSign();
    int sign_y = y.getSign();

    temp_x = x.abs();
    temp_y = y.abs();

    string x_binary = temp_x.toString();
    string y_binary = temp_y.toString();
    reverse(x_binary.begin(), x_binary.end());
    reverse(y_binary.begin(), y_binary.end());

    int g = 0;
    int i = 0, j = 0;

    while (i < x_binary.size() && j < y_binary.size() && x_binary[i] == '0' && y_binary[i] == '0') {
        g++;
        i++;
        j++;
    }

    temp_x = temp_x >> i;

    temp_y = temp_y >> j;

    BigInteger u(x);
    BigInteger v(y);

    BigInteger A("1");
    BigInteger B("0");
    BigInteger C("0");
    BigInteger D("1");

    while (!u.is_zero()) {
        while (!u.is_zero() && u.is_even()) {
            u = u >> 1;
            if (A.is_even() && B.is_even()) {
                A = A >> 1;
                B = B >> 1;
            } else {
                A = (A + y) >> 1;
                A %= y;
                B = (B - x) >> 1;
                B %= y;
            }

        }

        while (!v.is_zero() && v.is_even()) {
            v = v >> 1;
            if (C.is_even() && D.is_even()) {
                C = C >> 1;
                D = D >> 1;
            } else {
                C = (C + y) >> 1;
                C %= y;
                D = (D - x) >> 1;
                D %= y;
            }
        }

        if (u >= v) {
            u = u - v;
            A = A - C;
            B = B - D;
        } else {
            v = v - u;
            C = C - A;
            D = D - B;
        }
    }

    BigInteger a = C;
    BigInteger b = D;
    BigInteger d = v;
    d = d << g;

    a.setSign(a.getSign() * sign_x);
    b.setSign(b.getSign() * sign_y);

    return Ans{a, b, d};
}

int msbPosition(ll x)
{
    int res = 0;
    while (x > 0)
    {
        x >>= 1;
        res++;
    }
    return res;
}

auto divide(const BigInteger &a, const BigInteger &b) {
    struct res {
        BigInteger quotient;
        BigInteger remainder;
    };
    
    if (b.is_zero()) {
        throw "Divide by zero";
    }

    if (a.is_zero()) {
        return res{BigInteger("0"), BigInteger("0")};
    }

    BigInteger x = a.abs();
    BigInteger y = b.abs();

    int sign_x = a.getSign();
    int sign_y = b.getSign();

    res answer;
    answer.quotient = BigInteger("0");
    answer.remainder = x;

    int n = x.size();
    int m = y.size();

    if (x < y) { 
    // 9 : 10 => 0 : 9
    // -9 : 10 => 0 : -9
    // 9 : -10 => 0 : 9
        return res{BigInteger("0"), a};
    }

    while(answer.remainder >= b) {
        
        int msb_x = msbPosition(answer.remainder.getDigits().back());
        int msb_y = msbPosition(y.getDigits().back());
        int shift = msb_x - msb_y + (int)(answer.remainder.size() - y.size()) * BIT_PER_DIGIT;

        BigInteger shifted_y = y << shift;

        while (answer.remainder < shifted_y) {
            shift--;
            shifted_y = y << shift;
        }
                
        answer.remainder = answer.remainder - shifted_y;
        answer.quotient = answer.quotient + (BigInteger("1") << shift);
    }
    
    if(answer.quotient.is_zero()) {
        answer.quotient = BigInteger("0");
    }
    else {
        answer.quotient.setSign(sign_x * sign_y);
    }
    answer.remainder.setSign(sign_x);

    return answer;
}

BigInteger lcm(const BigInteger &x, const BigInteger &y) {
    BigInteger temp_x(x), temp_y(y);
    BigInteger xy = temp_x * temp_y;
    BigInteger gcd = bezout(x, y).d;
    return divide(xy, gcd).quotient;
}

bool Miller_Rabin_check(const BigInteger &n) {
    if (n.is_even()) return false;

    // n - 1 = 2^s . d
    BigInteger d = n - BigInteger("1");
    int s = 0;
    while (d.is_even()) {
        d = d >> 1;
        s++;
    }

    BigInteger n_minus_1 = n - BigInteger("1");
    srand(time(0));

    int Primes_size = sizeof(Primes) / sizeof(Primes[0]);

    for (int i = 0; i < 5; i++) {
        BigInteger a((ll)Primes[rand() % Primes_size]);

        BigInteger x = a.powMod(d, n);

        if (x == BigInteger("1") || x == n_minus_1) continue;

        bool check = false;

        for (int j = 1; j < s; j++) {
            x = x.mulMod(x, n);
            if (x == BigInteger("1")) return false;
            if (x == n_minus_1) {
                check = true;
                break;
            }
        }
        if (!check) return false;
    }

    return true;
}

string hex_to_bin(const string &hex) {
    string binary = "";
    for (char c: hex) {
        switch (c) {
            case '0':
                binary += "0000";
                break;
            case '1':
                binary += "0001";
                break;
            case '2':
                binary += "0010";
                break;
            case '3':
                binary += "0011";
                break;
            case '4':
                binary += "0100";
                break;
            case '5':
                binary += "0101";
                break;
            case '6':
                binary += "0110";
                break;
            case '7':
                binary += "0111";
                break;
            case '8':
                binary += "1000";
                break;
            case '9':
                binary += "1001";
                break;
            case 'A':
            case 'a':
                binary += "1010";
                break;
            case 'B':
            case 'b':
                binary += "1011";
                break;
            case 'C':
            case 'c':
                binary += "1100";
                break;
            case 'D':
            case 'd':
                binary += "1101";
                break;
            case 'E':
            case 'e':
                binary += "1110";
                break;
            case 'F':
            case 'f':
                binary += "1111";
                break;
            default:
                throw "Invalid hex string";
        }
    }
    return binary;
}

BigInteger generate_large_prime(int bit_length)
{
    std::mt19937_64 rng(std::random_device{}()); 
    std::uniform_int_distribution<uint64_t> dist(0, 1); 

    auto start = chrono::high_resolution_clock::now();
    
    BigInteger n;
    do {
        string binary = "1";
        for (int i = 1; i < bit_length - 1; i++) {
            binary += std::to_string(dist(rng)); 
        }
        binary += "1";
        n = BigInteger(binary);
    } while (!Miller_Rabin_check(n));

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Time generate large prime: " << duration.count() << "s" << endl;
    return n;
}

BigInteger mod_inverse(const BigInteger &a, const BigInteger &n)
{
    auto start = chrono::high_resolution_clock::now();

    BigInteger x = bezout(a, n).a;
    if (x.getSign() == -1) {
        x = x + n;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Time calculate modulo inverse: " << duration.count() << "s" << endl;

    return x;
}
