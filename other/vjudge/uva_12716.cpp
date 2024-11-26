#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 30000001;

int f[N];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    for (int i = 1; i < N; ++i) {
    	for (int j = 2 * i; j < N; j += i) {
    		if (((j - i) ^ j) == i) f[j]++;
    	}
    }
    for (int i = 1; i < N; ++i) {
    	f[i] += f[i - 1];
    }
    
    int T, n;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
		cin >> n;	    
	    cout << "Case " << t << ": " << f[n] << '\n';
    }
    return 0;
}
