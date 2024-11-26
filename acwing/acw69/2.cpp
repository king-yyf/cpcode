#include <bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/729/D
// https://codeforces.com/contest/729/standings

void solve() {
	int n, a, b, k;
    string s;
    cin >> n >> a >> b >> k >> s;
 
    int cnt = 0;
    for (int i = 0; i < n; ++i) if (s[i] == '0'){
        int j = i;
        while (j + 1 < s.size() && s[j + 1] == '0') j ++;
        cnt += (j - i + 1) / b;
        i = j;
    }
    vector<int> p;
    for (int i = 0; i < n; ++i) if (s[i] == '0'){
        int j = i;
        while (j + 1 < s.size() && s[j + 1] == '0') j ++;
        int k = i + b - 1;
        while (cnt >= a && k <= j){
            cnt --;
            p.push_back(k);
            k += b;
        }
        i = j;
    }
    int c = p.size();
    cout << c << "\n";
    for (int i = 0; i < c; ++i) 
        cout << p[i] + 1 << " \n"[i == c - 1];

}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    solve();

    return 0;
}
