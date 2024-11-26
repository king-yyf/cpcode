#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1645

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    vector<int> p(n), sk;
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && a[i] < a[sk.back()]) {
            p[sk.back()] = i + 1;
            sk.pop_back();
        }
        sk.push_back(i);
    }
    for (int i = 0; i < n; ++i) {
        cout << p[i] << " ";
    }
   
    return 0;
}
