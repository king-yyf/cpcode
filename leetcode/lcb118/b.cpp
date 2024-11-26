#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <deque>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using lint = long long;
using pint = pair<int, int>;
using plint = pair<lint, lint>;
struct fast_ios { fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(20); }; } fast_ios_;
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
template <typename T> bool chmax(T &m, const T q) { return m < q ? (m = q, true) : false; }
template <typename T> bool chmin(T &m, const T q) { return m > q ? (m = q, true) : false; }
const std::vector<std::pair<int, int>> grid_dxs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int floor_lg(long long x) { return x <= 0 ? -1 : 63 - __builtin_clzll(x); }
template <class T1, class T2> T1 floor_div(T1 num, T2 den) { return (num > 0 ? num / den : -((-num + den - 1) / den)); }
template <class T1, class T2> std::pair<T1, T2> operator+(const std::pair<T1, T2> &l, const std::pair<T1, T2> &r) { return std::make_pair(l.first + r.first, l.second + r.second); }
template <class T1, class T2> std::pair<T1, T2> operator-(const std::pair<T1, T2> &l, const std::pair<T1, T2> &r) { return std::make_pair(l.first - r.first, l.second - r.second); }
template <class T> std::vector<T> sort_unique(std::vector<T> vec) { sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end()); return vec; }
template <class T> int arglb(const std::vector<T> &v, const T &x) { return std::distance(v.begin(), std::lower_bound(v.begin(), v.end(), x)); }
template <class T> int argub(const std::vector<T> &v, const T &x) { return std::distance(v.begin(), std::upper_bound(v.begin(), v.end(), x)); }
template <class IStream, class T> IStream &operator>>(IStream &is, std::vector<T> &vec) { for (auto &v : vec) is >> v; return is; }

template <class OStream, class T> OStream &operator<<(OStream &os, const std::vector<T> &vec);
template <class OStream, class T, size_t sz> OStream &operator<<(OStream &os, const std::array<T, sz> &arr);
template <class OStream, class T, class TH> OStream &operator<<(OStream &os, const std::unordered_set<T, TH> &vec);
template <class OStream, class T, class U> OStream &operator<<(OStream &os, const pair<T, U> &pa);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::deque<T> &vec);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::set<T> &vec);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::multiset<T> &vec);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::unordered_multiset<T> &vec);
template <class OStream, class T, class U> OStream &operator<<(OStream &os, const std::pair<T, U> &pa);
template <class OStream, class TK, class TV> OStream &operator<<(OStream &os, const std::map<TK, TV> &mp);
template <class OStream, class TK, class TV, class TH> OStream &operator<<(OStream &os, const std::unordered_map<TK, TV, TH> &mp);
template <class OStream, class... T> OStream &operator<<(OStream &os, const std::tuple<T...> &tpl);

template <class OStream, class T> OStream &operator<<(OStream &os, const std::vector<T> &vec) { os << '['; for (auto v : vec) os << v << ','; os << ']'; return os; }
template <class OStream, class T, size_t sz> OStream &operator<<(OStream &os, const std::array<T, sz> &arr) { os << '['; for (auto v : arr) os << v << ','; os << ']'; return os; }
template <class... T> std::istream &operator>>(std::istream &is, std::tuple<T...> &tpl) { std::apply([&is](auto &&... args) { ((is >> args), ...);}, tpl); return is; }
template <class OStream, class... T> OStream &operator<<(OStream &os, const std::tuple<T...> &tpl) { os << '('; std::apply([&os](auto &&... args) { ((os << args << ','), ...);}, tpl); return os << ')'; }
template <class OStream, class T, class TH> OStream &operator<<(OStream &os, const std::unordered_set<T, TH> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::deque<T> &vec) { os << "deq["; for (auto v : vec) os << v << ','; os << ']'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::set<T> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::multiset<T> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::unordered_multiset<T> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T, class U> OStream &operator<<(OStream &os, const std::pair<T, U> &pa) { return os << '(' << pa.first << ',' << pa.second << ')'; }
template <class OStream, class TK, class TV> OStream &operator<<(OStream &os, const std::map<TK, TV> &mp) { os << '{'; for (auto v : mp) os << v.first << "=>" << v.second << ','; os << '}'; return os; }
template <class OStream, class TK, class TV, class TH> OStream &operator<<(OStream &os, const std::unordered_map<TK, TV, TH> &mp) { os << '{'; for (auto v : mp) os << v.first << "=>" << v.second << ','; os << '}'; return os; }
// #ifdef HITONANODE_LOCAL
const string COLOR_RESET = "\033[0m", BRIGHT_GREEN = "\033[1;32m", BRIGHT_RED = "\033[1;31m", BRIGHT_CYAN = "\033[1;36m", NORMAL_CROSSED = "\033[0;9;37m", RED_BACKGROUND = "\033[1;41m", NORMAL_FAINT = "\033[0;2m";
#define dbg(x) std::cerr << BRIGHT_CYAN << #x << COLOR_RESET << " = " << (x) << NORMAL_FAINT << " (L" << __LINE__ << ") " << __FILE__ << COLOR_RESET << std::endl
#define dbgif(cond, x) ((cond) ? std::cerr << BRIGHT_CYAN << #x << COLOR_RESET << " = " << (x) << NORMAL_FAINT << " (L" << __LINE__ << ") " << __FILE__ << COLOR_RESET << std::endl : std::cerr)
// #else
// #define dbg(x) std::cerr << BRIGHT_CYAN << #x << COLOR_RESET << " = " << (x) << NORMAL_FAINT << " (L" << __LINE__ << ") " << __FILE__ << COLOR_RESET << std::endl
// #define dbgif(cond, x) ((cond) ? std::cerr << BRIGHT_CYAN << #x << COLOR_RESET << " = " << (x) << NORMAL_FAINT << " (L" << __LINE__ << ") " << __FILE__ << COLOR_RESET << std::endl : std::cerr)
// #endif

string apply(string s01, string kak) {
    assert(s01.size() == kak.size());
    int depth = 0;
    REP(i, s01.size()) {
        int next_depth = depth;
        if (kak.at(i) == '(') {
            ++next_depth;
        } else if (kak.at(i) == ')') {
            --next_depth;
        } else {
            assert(false);
        }

        assert(next_depth >= 0);
        if (min(depth, next_depth) % 2 == 0) {
            if (s01.at(i) == '0') {
                s01.at(i) = '1';
            } else if (s01.at(i) == '1') {
                s01.at(i) = '0';
            } else {
                assert(false);
            }
        }

        depth = next_depth;
    }

    assert(depth == 0);

    return s01;
}

pint cntcrnt(const string &S) {
    int current_odd_1 = 0, current_even_1 = 0;
    REP(i, S.size()) {
        if (S.at(i) == '1') {
            if (i % 2 == 0) {
                ++current_even_1;
            } else {
                ++current_odd_1;
            }
        }
    }

    return {current_odd_1, current_even_1};
}
pair<bool, vector<string>> solve(string S) {

    if (S.front() != S.back() or count(S.begin(), S.end(), '1') % 2) return {false, {}};

    vector<string> ret;

    if (S.front() == '1') {
        string op = string(S.size() / 2, '(') + string(S.size() / 2, ')');
        ret.push_back(op);
        S = apply(S, op);
    }
    // dbg(S);

    {
        // auto [current_odd_1, current_even_1] = cntcrnt(S);
        int n01 = 0, n10 = 0;
        for (int i = 1; i + 1 < (int)S.size(); i += 2) {
            char o = S.at(i), e = S.at(i + 1);
            if (o != e) {
                if (o == '0' && e == '1') {
                    n01++;
                } else if (o == '1' && e == '0') {
                    n10++;
                } else {
                    assert(false);
                }
            }
        }

        const int nsum = n01 + n10;
        int nseen = 0;

        string str = "(";
        for (int i = 1; i + 1 < (int)S.size(); i += 2) {
            char o = S.at(i), e = S.at(i + 1);
            if (o == e) {
                str += "()";
            } else {
                if (nseen < nsum / 2) {
                    // to be 01
                    if (o == '0' and e == '1') {
                        // already 01
                        str += "()";
                    } else if (o == '1' and e == '0') {
                        str += ")(";
                    } else {
                        assert(false);
                    }
                } else {
                    // to be 10
                    if (o == '0' and e == '1') {
                        str += ")(";
                    } else if (o == '1' and e == '0') {
                        // already 10
                        str += "()";
                    } else {
                        assert(false);
                    }
                }
                ++nseen;
            }
        }
        str += ")";

        S = apply(S, str);
        ret.push_back(str);
    }
    // dbg(S);
    {
        string str;
        int h = 0;
        REP(i, S.size()) {
            if (S.at(i) == '1') {
                if (h % 2 == 0) {
                    str += '(';
                    ++h;
                } else {
                    str += ')';
                    --h;
                }
            } else if (S.at(i) == '0') {
                if (h % 2 == 0) {
                    str += ')';
                    --h;
                } else {
                    str += '(';
                    ++h;
                }
            } else {
                assert(false);
            }
            assert(h >= 0);
        }
        assert(h == 0);
        ret.push_back(str);
        S = apply(S, str);
    }
    // dbg(S);
    assert(S == string(S.size(), '0'));
    return {true, ret};
}


struct rand_int_ {
    using lint = long long;
    std::mt19937 mt;
    rand_int_() : mt(std::chrono::steady_clock::now().time_since_epoch().count()) {}
    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)
    lint operator()(lint l, lint r) {
        std::uniform_int_distribution<lint> d(l, r - 1);
        return d(mt);
    }
} rnd;

template <typename... Args> void err(Args... args) {
    Writer<cerr, true, false>{}.print_with_sep(" | ", args...);
}
template <typename... Args> void errn(Args... args) {
    Writer<cerr, true, true>{}.print_with_sep(" | ", args...);
}
void err_prefix(string func, int line, string args) {
    cerr << "\033[0;31m\u001b[1mDEBUG\033[0m"
         << " | "
         << "\u001b[34m" << func << "\033[0m"
         << ":"
         << "\u001b[34m" << line << "\033[0m"
         << " - "
         << "[" << args << "] = ";
}
#define dbg(args...) err_prefix(__FUNCTION__, __LINE__, #args), err(args)
#define dbgn(args...) err_prefix(__FUNCTION__, __LINE__, #args), errn(args)
 
// #ifdef LOCAL

// #else
// #define dbg(...)
// #define dbgn(args...)
// #endif


int main() {
    // FOR(n, 1, 10) {
    //     const int len = n * 2;
    //     REP(S, 1 << len) {
    //         if (__builtin_parity(S)) continue;
    //         string s01(len, '0');
    //         REP(i, len) {
    //             if (S & (1 << i)) s01.at(i) = '1';
    //         }
    //         // dbg(s01);
    //         solve(s01);
    //     }
    // }

    // for (long long ntry = 1;; ntry++) {
    //     int n = rnd(2, 100);
    //     const int len = n * 2;
    //     string S(len, '0');
    //     REP(i, len) {
    //         if (rnd(2)) S.at(i) = '1';
    //     }
    //     // dbg(S);
    //     auto sol = solve(S);
    //     if (__builtin_popcountll(ntry) == 1) {
    //         dbg(ntry);
    //         ;
    //     }
    // }
    
    
    int T;
    cin >> T;
    while (T--) {
        int N;
        string S;
        cin >> N >> S;
        dbg(S);
        auto [flg, ans] = solve(S);
        if (flg) {
            cout << ans.size() << '\n';
            for (auto s : ans) cout << s << '\n';
        } else {
            cout << "-1\n";
        }
    }
}
