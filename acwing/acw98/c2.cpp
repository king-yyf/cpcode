// clang-format off
#include <algorithm>
#include <bitset>
#include <cassert>
#include <clocale>
#include <cmath>
#include <cstdlib> // for random
#include <ctime>   // for random
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
*/

using namespace std;
using namespace std::chrono;

#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

bool outTime = false;
high_resolution_clock::time_point start_time, end_time;
void calcTime();

typedef unsigned ull;
typedef long long ll;
typedef long double ld;

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const int extraMOD = 1e9 + 9;

#define int long long
#define all(a) a.begin(), a.end()

void solve() {
    int m;
    cin >> m;
    
    int cnt = 0;
    vector <int> ans;
    for (int i = 1; i <= 1000000; i++) {
        int tmp = i;
        while (tmp % 5 == 0) {
            tmp /= 5;
            cnt++;
        }
        if (cnt == m) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << "\n";
    for (int i : ans) {
        cout << i << " ";
    }
    cout << "\n";
}

signed main() {
//#ifdef __APPLE__
//    calcTime();
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
//    freopen("position.in", "r", stdin);
//    freopen("position.out", "w", stdout);

//    cout << fixed << setprecision(10);

//    srand(time(nullptr));

    int t = 1;
//    cin >> t;

    while (t--) {
        solve();
    }
    calcTime();
    return 0;
}

void calcTime() {
    if (outTime) {
        end_time = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end_time - start_time);
        cout << "\nTime " << duration.count() / 1000.0 << " ms\n";
    }
    outTime = true;
    start_time = high_resolution_clock::now();
}

