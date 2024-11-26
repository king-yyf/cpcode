#include <bits/stdc++.h>

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 1e18
#define pb push_back
#define pr pop_back
#define rep(a, b, c) for (int(a) = (b); (a) <= (c); ++(a))
#define irep(a, b, c) for (int(a) = (b); (a) >= (c); --(a))
#define pi pair<int, int>
#define pl pair<ll, ll>
#define vi vector<int>
#define vb vector<bool>
#define vl vector<ll>
#define vpi vector<pair<int, int>>
#define vpl vector<pair<ll, ll>>
#define vvi vector<vector<int>>
#define vvl vector<vector<ll>>
#define vvvi vector<vector<vector<int>>>
#define vvvl vector<vector<vector<ll>>>
#define popcount(x) (__builtin_popcountll(x))
ll M = 1000000007;

//---------------------------------------------//
ll gcd(ll X, ll Y) { return !Y ? X : gcd(Y, X % Y);}
ll lcm(ll X, ll Y) { return X * Y / gcd(X, Y); }
ll exppow(ll X, ll Y) { ll R = 1; X %= M; while (Y > 0) { if (Y % 2) { R = (R * X) % M; } X = (X * X) % M, Y /= 2; } return R; }
ll fracmod(ll X, ll Y) { ll Z = gcd(X, Y); X /= Z; Y /= Z; return (X * exppow(Y, M - 2)) % M; }
int random(int l, int r) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(l, r)(rng);
}

//---------------------------------------------//

void solve() {
    int n, a, b;
    string s;
    cin >> n >> a >> b >> s;
    int x = 0, y = 0;
    for (auto &i : s) {
        if (i == '0') x++;
        else y++;
    }
    if (!x || !y) {
        cout << 0;
        return;
    }
    int p = min(y * a, (y % 2) * min(a, 2 * b) + (y / 2) * b);
    int q = min(x * a, x * b);
    cout << min(p, q);
}

int main() {
    cin.sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif

    int tt = 1;
    cin >> tt;
    for (int TT = 1; TT <= tt; TT++) { solve(); cout << " \n"[TT != tt]; }
}
