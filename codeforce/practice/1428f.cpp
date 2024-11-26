#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    string s;
    cin >> n >> s;

    long long ans = 0, sum = 0;
    vector<long long> p(n + 1);
    p[0] = 1;
    int cnt = 0;

    for (auto c : s) {
    	if (c == '0') {
    		cnt = 0;
    		p[0] += 1;
    	} else {
    		sum += p[cnt] + cnt;
    		p[cnt + 1] += p[cnt];
    		p[cnt] = 1;
    		cnt += 1;
    	}
    	ans += sum;
    }

    cout << ans << '\n';

    return 0;
}
