/*
Author: nxphuc

Note:
    inv function use Little Fermat's Theorem,
    if MOD is not prime number, you have to use Extended Euclidean Algorithm

References:
-   https://codeforces.com/profile/Benq
-   https://codeforces.com/profile/tourist
-   https://github.com/ngthanhtrung23

Tested:
-   https://codeforces.com/contest/1569/problem/C
-   https://www.codechef.com/SEPT21B/problems/TREHUNT
-   https://atcoder.jp/contests/abc215/tasks/abc215_e

Usage:
    modular a, b;
    cin >> a >> b;
    modular c = a + b;
    modular d = a - b;
    modular e = a * b;
    modular f = a / b;
    cout << c << d << e << f << "\n";
 */
const int MOD = 998244353;
template<int MOD>
struct ModInt {
    static const int mod = MOD;
    int v;

    explicit operator int() const { return v; }

    ModInt() : v(0) {}

    ModInt(int _v) {
        v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
        if (v < 0) v += MOD;
    }

    ModInt(long long _v) {
        v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
        if (v < 0) v += MOD;
    }

#define COMPAREOP(OP) bool constexpr operator OP(ModInt other) const { return v OP other.v; }
    COMPAREOP(==) COMPAREOP(!=) COMPAREOP(<) COMPAREOP(>) COMPAREOP(<=) COMPAREOP(>=)
#undef COMPAREOP

    ModInt& operator+=(const ModInt& other) { 
        if ((v += other.v) >= MOD) v -= MOD; 
        return *this;
    }

    ModInt& operator-=(const ModInt& other) { 
        if ((v -= other.v) < 0) v += MOD; 
        return *this;
    }

    ModInt& operator*=(const ModInt& other) {
        v = int((ll)v * other.v % MOD);
        return *this;
    }

    ModInt &operator/=(const ModInt &other) { return (*this) *= inv(other); }

    friend ModInt pow(ModInt a, ll p) {
        ModInt ans = 1;
        assert(p >= 0);
        for (; p; p /= 2, a *= a)
            if (p & 1)
                ans *= a;
        return ans;
    }

    // if MOD is not prime number, you have to use Extended Euclidean Algorithm
    friend ModInt inv(const ModInt& a) {
        assert(a.v != 0);
        return pow(a, MOD-2);
    }

    ModInt operator-() const { return ModInt(-v); }
    ModInt& operator++() { return *this += 1; }
    ModInt& operator--() { return *this -= 1; }
    ModInt operator++(int) {
        ModInt temp = *this;
        *this += 1;
        return temp;
    }
    ModInt operator--(int) {
        ModInt temp = *this;
        *this -= 1;
        return temp;
    }
    friend ModInt operator+(ModInt a, const ModInt &b) { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt &b) { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt &b) { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt &b) { return a /= b; }

    friend std::ostream& operator << (std::ostream& os, const ModInt& m) { return os << m.v; }
    friend std::istream& operator >> (std::istream& is, ModInt& m) { return is >> m.v; }
};

using modular = ModInt<MOD>;
