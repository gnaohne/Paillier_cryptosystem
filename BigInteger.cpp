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
    if (s[0] == '-') {
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
    } else {
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
        } else {
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
    }
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

    int value = 1 << (i);

    int n = size();
    BigInteger ans;
    ans.sign = sign;
    ans.digits.resize(n);

    int carry = 0;
    ll sum = 0;
    for (int j = n - 1; j >= 0; j--) {
        if (j == n - 1) {
            carry = digits[j] % value;
            ans.digits[j] = digits[j] >> i;
        } else {
            sum = digits[j] + BASE * carry;
            carry = sum % value;
            ans.digits[j] = sum >> i;
        }
    }
    ans.trim();
    return ans;
}

BigInteger BigInteger::operator<<(int i) {
    if (i < 0) {
        throw "Shift left must be positive";
    }

    if (i == 0) return *this;


    ll carry = 0;
    ll sum = 0;
    int n = size();
    BigInteger ans;
    ans.sign = sign;
    ans.digits.resize(n + i);
    for (int j = 0; j < n; j++) {
        if (j == 0) {
            sum = digits[j] << i;
            ans.digits[j] = sum % BASE;
            carry = sum / BASE;
        } else {
            sum = digits[j] + carry;
            ans.digits[j] = sum % BASE;
            carry = sum / BASE;
        }
    }
    ans.digits[n] = carry;
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

auto bezout(BigInteger &x, BigInteger &y) {
    struct Ans {
        BigInteger a, b;
        BigInteger d; // Bezout => ax + by = gcd(x,y) = d
    };

    if (x.is_zero()) {
        return Ans{BigInteger("0"), BigInteger("1"), y};
    }
    if (y.is_zero()) {
        return Ans{BigInteger("1"), BigInteger("0"), x};
    }

    int sign_x = x.getSign();
    int sign_y = y.getSign();

    x = x.abs();
    y = y.abs();

    string x_binary = x.toString();
    string y_binary = y.toString();
    reverse(x_binary.begin(), x_binary.end());
    reverse(y_binary.begin(), y_binary.end());

    int g = 0;
    int i = 0, j = 0;

    while (i < x_binary.size() && j < y_binary.size() && x_binary[i] == '0' && y_binary[i] == '0') {
        g++;
        i++;
        j++;
    }

    x = x >> i;

    y = y >> j;
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
    answer.quotient = BigInteger();
    answer.remainder = x;

    int shift = BIT_PER_DIGIT * (x.size() - y.size() + 1);
    while (shift >= 0) {
        BigInteger shiftedY = y << shift;
        if (answer.remainder >= shiftedY) {
            answer.remainder = answer.remainder - shiftedY;
            answer.quotient = answer.quotient + (BigInteger("1") << shift);
        }
        shift--;
    }

    answer.quotient.setSign(sign_x * sign_y);
    answer.remainder.setSign(sign_x);

    return answer;
}

BigInteger lcm(BigInteger &x, BigInteger &y) {
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

    for (int i = 0; i < 10; i++) {
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
