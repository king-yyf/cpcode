#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <climits>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cmath>
#include <bitset>
#define endl "\n"
#define ll long long
#define maxn 200010
#define maxm 1000010
using namespace std;
template<typename T>
void printv(vector<T> &vv);
template<typename T>
void printa(T *vv, int sz);
int TT, kase;
int n, k;
int a[maxn];
void solve() {
    vector<int> v[1010];
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        v[a[i] % k].push_back(a[i]);
    }
    ll res = 0;
    while (v[0].size() > 1) {
        int x = v[0].back();
        v[0].pop_back();
        int y = v[0].back();
        v[0].pop_back();
        res += (x + y) / k;
    }
    if (k % 2 == 0 && v[k / 2].size() > 1) {
        int x = v[k / 2].back();
        v[k / 2].pop_back();
        int y = v[k / 2].back();
        v[k / 2].pop_back();
        res += (x + y) / k;
    }
    vector<int> remain;
    for (int i = 1; i <= (k - 1) / 2; i++) {
        for (int val: v[k - i]) remain.push_back(val);
        v[k - i].clear();
        while (!v[i].empty() && !remain.empty()) {
            int x = v[i].back();
            int y = remain.back();
            remain.pop_back();
            v[i].pop_back();
            res += (x + y) / k;
        }
    }
    if (k % 2 == 0 && !v[k / 2].empty() && !remain.empty()) {
        int x = v[k / 2].back();
        int y = remain.back();
        remain.pop_back();
        v[k / 2].pop_back();
        res += (x + y) / k;
    }
    for (int i = 0; i < k; i++) {
        for (int x: v[i]) remain.push_back(x);
    }
    for (int i = 0; i < remain.size(); i += 2) res += (remain[i] + remain[i + 1]) / k;
    cout << res << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    //infile.open("/Users/jiluyang/Desktop/input.txt");
    //outfile.open("/Users/jiluyang/Desktop/output.txt");
    TT = 1;
    cin >> TT;
    //pre();
    for (kase = 1; kase <= TT; kase++) {
        solve();
    }
    return 0;
}
template<typename T>
void printv(vector<T> &vv) {
    for (int i = 0; i < vv.size(); i++) {
        if (i) cout << " ";
        cout << vv[i];
    }
    cout << endl;
}

template<typename T>
void printa(T *vv, int sz) {
    for (int i = 1; i <= sz; i++) {
        if (i > 1) cout << " ";
        cout << vv[i];
    }
    cout << endl;
}