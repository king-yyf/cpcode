#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<const unsigned &MOD>
struct _m_uint {
    unsigned val;
    _m_uint(int64_t v = 0) {
        if (v < 0) v = v % MOD + MOD; if (v >= MOD) v %= MOD;
        val = unsigned(v);
    }
    _m_uint(uint64_t v) { if (v >= MOD) v %= MOD; val = unsigned(v);}
    _m_uint(int v) : _m_uint(int64_t(v)) {}
    _m_uint(unsigned v) : _m_uint(uint64_t(v)) {}
    explicit operator uint64_t() const { return val; }
    _m_uint& operator+=(const _m_uint &other) {
        val = val < MOD - other.val ? val + other.val : val - (MOD - other.val);
        return *this;
    }
    static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
        return unsigned(x % m);
#endif
        unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }
    _m_uint& operator*=(const _m_uint &other) {
        val = fast_mod(uint64_t(val) * other.val);
        return *this;
    }
    _m_uint& operator/=(const _m_uint &other) { return *this *= other.inv();}
    friend _m_uint operator+(const _m_uint &a, const _m_uint &b) { return _m_uint(a) += b; }
    friend _m_uint operator*(const _m_uint &a, const _m_uint &b) { return _m_uint(a) *= b; }
    friend _m_uint operator/(const _m_uint &a, const _m_uint &b) { return _m_uint(a) /= b; }
    friend bool operator==(const _m_uint &a, const _m_uint &b) { return a.val == b.val; }
    static const int SAVE_INV = int(1e6) + 5;
    static _m_uint save_inv[SAVE_INV];
    static void prepare_inv() { // assert( is_prime(MOD) )
        for (int64_t p = 2; p * p <= MOD; p += p % 2 + 1) assert(MOD % p != 0);
        save_inv[0] = 0, save_inv[1] = 1;
        for (int i = 2; i < SAVE_INV; i++) save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
    }
    _m_uint inv() const {
        if (save_inv[1] == 0) prepare_inv();
        if (val < SAVE_INV) return save_inv[val];
        _m_uint product = 1;
        unsigned v = val;
        do {
            product *= MOD - MOD / v;
            v = MOD % v;
        } while (v >= SAVE_INV);
        return product * save_inv[v];
    }
};
template<const unsigned &MOD> _m_uint<MOD> _m_uint<MOD>::save_inv[_m_uint<MOD>::SAVE_INV];
uint64_t random_address() { char *p = new char; delete p; return uint64_t(p); }
mt19937_64 rng_hash(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
extern const unsigned HASH_P = unsigned(-13337); // both P and (P - 1) / 2 are prime.
using hash_int = _m_uint<HASH_P>;
const uint64_t HASH_P2 = uint64_t(HASH_P) * HASH_P;
const int HASH_COUNT = 2;
const int INF = int(1e9) + 5;
uniform_int_distribution<unsigned> MULT_DIST(unsigned(0.1 * HASH_P), unsigned(0.9 * HASH_P));
const hash_int HASH_MULT[] = {MULT_DIST(rng_hash), MULT_DIST(rng_hash)};
const hash_int HASH_INV[] = {1 / HASH_MULT[0], 1 / HASH_MULT[1]};
vector<hash_int> hash_pow[] = {{1}, {1}};

template<typename T_string = string>
struct string_hash {
    static const bool BUILD_REVERSE = false; // if need BUILD_REVERSE, set true
    static uint64_t hash(const T_string &str) {
        uint64_t result = 0;
        for (int h = 0; h < HASH_COUNT; h++) {
            uint64_t value = 1;
            for (const auto &x : str) value = (uint64_t(HASH_MULT[h]) * value + x) % HASH_P;
            result += value << (32 * h);
        }
        return result;
    }
    T_string str;
    vector<hash_int> _prefix[HASH_COUNT], _inv_prefix[HASH_COUNT];
    string_hash() { build({});}
    string_hash(const T_string &_str) { build(_str);}
    int length() const { return int(_prefix[0].size()) - 1;}
    template<typename T_char>
    void add_char(const T_char &c) {
        str.push_back(c);
        for (int h = 0; h < HASH_COUNT; h++) {
            _prefix[h].push_back(HASH_MULT[h] * _prefix[h].back() + c);
            if (hash_pow[h].size() < _prefix[h].size())
                hash_pow[h].push_back(HASH_MULT[h] * hash_pow[h].back());
            if (BUILD_REVERSE)
                _inv_prefix[h].push_back((_inv_prefix[h].back() + c) * HASH_INV[h]);
        }
    }
    void pop_char() {
        str.pop_back();
        for (int h = 0; h < HASH_COUNT; h++) {
            _prefix[h].pop_back();
            if (BUILD_REVERSE) _inv_prefix[h].pop_back();
        }
    }
    void build(const T_string &_str) {
        str = {}; str.reserve(_str.size());
        for (int h = 0; h < HASH_COUNT; h++) {
            hash_pow[h].reserve(_str.size() + 1);
            _prefix[h] = {0};
            _prefix[h].reserve(_str.size() + 1);
            if (BUILD_REVERSE) {
                _inv_prefix[h] = {0};
                _inv_prefix[h].reserve(_str.size() + 1);
            }
        }
        for (auto &c : _str) add_char(c);
    }
    uint64_t _single_hash(int h, int start, int end) const {
        uint64_t power = uint64_t(hash_pow[h][end - start]);
        return (power + uint64_t(_prefix[h][end]) + HASH_P2 - uint64_t(_prefix[h][start]) * power) % HASH_P;
    }
    uint64_t substring_hash(int start, int end) const {
        assert(0 <= start && start <= end && end <= length());
        return _single_hash(0, start, end) + (HASH_COUNT > 1 ? _single_hash(1, start, end) << 32 : 0);
    }
    uint64_t complete_hash() const { return substring_hash(0, length());}
    uint64_t _reverse_single_hash(int h, int start, int end) const {
        uint64_t power = uint64_t(hash_pow[h][end - start]);
        return (power + uint64_t(_inv_prefix[h][end]) * power + HASH_P - uint64_t(_inv_prefix[h][start])) % HASH_P;
    }
    uint64_t reverse_substring_hash(int start, int end) const {
        assert(0 <= start && start <= end && end <= length());
        return _reverse_single_hash(0, start, end) + (HASH_COUNT > 1 ? _reverse_single_hash(1, start, end) << 32 : 0);
    }
    uint64_t reverse_complete_hash() const { return reverse_substring_hash(0, length());}
    bool equal(int start1, int start2, int length) const {
        return substring_hash(start1, start1 + length) == substring_hash(start2, start2 + length);
    }
    bool is_palindrome(int start, int end) const { // assert(BUILD_REVERSE = true)
        return substring_hash(start, end) == reverse_substring_hash(start, end);
    }
    int compare(int start1, int start2, int max_length = INF) const;
};
uint64_t concat_hashes(uint64_t hash1, uint64_t hash2, int len2) {
    if (len2 == 0) return hash1;
    uint64_t hash1_low = hash1 & unsigned(-1), hash2_low = hash2 & unsigned(-1);
    uint64_t power = uint64_t(hash_pow[0][len2]);
    uint64_t combined = (hash1_low * power + hash2_low + HASH_P - power) % HASH_P;
    if (HASH_COUNT > 1) {
        hash1 >>= 32, hash2 >>= 32;
        power = uint64_t(hash_pow[1][len2]);
        combined += (hash1 * power + hash2 + HASH_P - power) % HASH_P << 32;
    }
    return combined;
}
template<typename T_string>
int first_mismatch(const string_hash<T_string> &hash1, int start1,
                   const string_hash<T_string> &hash2, int start2, int max_len = INF) {
    max_len = min({max_len, hash1.length() - start1, hash2.length() - start2});
    static const int FIRST = 5;
    int first = min(max_len, FIRST);
    for (int i = 0; i < first; i++)
        if (hash1.str[start1 + i] != hash2.str[start2 + i]) return i;
    if (hash1.substring_hash(start1, start1 + max_len) == hash2.substring_hash(start2, start2 + max_len))
        return max_len;
    static const int MANUAL = 15;
    int low = first, high = max_len - 1;
    while (high - low > MANUAL) {
        int mid = (low + high + 1) / 2;
        if (hash1.substring_hash(start1, start1 + mid) == hash2.substring_hash(start2, start2 + mid))
            low = mid;
        else
            high = mid - 1;
    }
    for (int i = low; i < high; i++)
        if (hash1.str[start1 + i] != hash2.str[start2 + i]) return i;
    return high;
}
template<typename T_string>
int hash_compare(const string_hash<T_string> &hash1, int start1,
                 const string_hash<T_string> &hash2, int start2, int max_len = INF) {
    int mismatch = first_mismatch(hash1, start1, hash2, start2, max_len);
    int len1 = min(hash1.length() - start1, max_len), len2 = min(hash2.length() - start2, max_len);
    if (mismatch == min(len1, len2))
        return len1 == len2 ? 0 : (len1 < len2 ? -1 : +1);
    if (hash1.str[start1 + mismatch] == hash2.str[start2 + mismatch])
        return 0;
    return hash1.str[start1 + mismatch] < hash2.str[start2 + mismatch] ? -1 : +1;
}
template<typename T_string>
int string_hash<T_string>::compare(int start1, int start2, int max_len) const {
    return hash_compare(*this, start1, *this, start2, max_len);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    

    return 0;
}
