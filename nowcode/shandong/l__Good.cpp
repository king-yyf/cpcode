#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC optimize("no-stack-protector,fast-math")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<double> vd;
typedef vector<string> vs;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<pdd> vpdd;
typedef vector<vd> vvd;
#define yn(ans) printf("%s\n", (ans)?"Yes":"No");
#define YN(ans) printf("%s\n", (ans)?"YES":"NO");
template<class T> bool chmax(T &a, T b) {
    if (a >= b) return false;
    a = b; return true;
}
template<class T> bool chmin(T &a, T b) {
    if (a <= b) return false;
    a = b; return true;
}
#define FOR(i, s, e, t) for ((i) = (s); (i) < (e); (i) += (t)) 
#define REP(i, e) for (int i = 0; i < (e); ++i) 
#define REP1(i, s, e) for (int i = (s); i < (e); ++i)
#define RREP(i, e) for (int i = (e); i >= 0; --i)
#define RREP1(i, e, s) for (int i = (e); i >= (s); --i)
#define all(v) v.begin(), v.end()
#define pb push_back
#define qb pop_back
#define pf push_front
#define qf pop_front
#define maxe max_element
#define mine min_element
ll inf = 1e18;
#define DEBUG printf("%d\n", __LINE__); fflush(stdout);
template<class T> void print(vector<T> &v, bool withSize = false) {
    if (withSize) cout << v.size() << endl;
    REP(i, v.size()) cout << v[i] << " "; 
    cout << endl;
}
mt19937_64 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

int __FAST_IO__ = []() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return 0;
}();

#define TESTS int t; cin >> t; while (t--)
#define TEST 
int main() {
    TESTS {
        ll N, M; ll X;
        cin >> N >> M >> X;
        
        auto calc = [&](ll x) {
            ll c = N * 2 + M * 2 - 4, d = 8;
            return 1ll * (c + c - d * x + d) * x / 2;
        };
        
        ll L = 0, R = min(N, M) / 2 + 1;
        while (L + 1 < R) {
            ll mid = (L + R) >> 1;
            ll sum = calc(mid);
        //  printf("%lld %lld\n", mid, sum);
            if (sum < X) L = mid; else R = mid;
        }
        
        ll sum = calc(L);
        ll left = X - sum;
        ll sx = L, sy = L;
        ll leftN = N - 2 * L, leftM = M - 2 * L;
        
    //  printf("%d %lld %lld %d %d %lld %lld\n", L, sum, left, sx, sy, leftN, leftM);
        if (left <= leftM) {
            sy += left - 1;
        } else if (left <= leftM + leftN - 1) {
            sx += left - leftM;
            sy += leftM - 1;
        } else if (left <= leftM + leftN - 1 + leftM - 1) {
            sx += leftN - 1;
            sy += leftM + leftN - 1 + leftM - 1 - left;
        } else {
            sx += leftN * 2 + leftM * 2 - 3 - left;
        }
        printf("%lld %lld\n", sx + 1, sy + 1);
    }
    
    return 0;
}
