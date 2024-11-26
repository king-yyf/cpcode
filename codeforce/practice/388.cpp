#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int k,s = 0, p = 0;
    cin >> k;
    for (int i = 0; i < 30; ++i) {
    	if ((k >> i) & 1) {
    		s += i > 0 ? 2 : 1;
    		p = i;
    	}
    }
    int n = p * s + 2;

    vector a(n + 1, vector<char>(n + 1, 'N'));
    for (int i = 1; i <= s; ++i) {
    	a[1][i + 2] = a[i + 2][1] =  'Y';
    }
    for (int i = (p - 1) * s + 1; i <= p * s; ++i) {
    	a[2][i + 2] = a[i][i + 2] = 'Y';
    }
    for (int i = 1; i <= s; ++i) {
    	for (int j = 0; j < p - 1; ++j) {
    		a[j * s + i + 2][(j + 1) * s + i + 2] = a[(j + 1) * s + i + 2][j * s + i + 2] = 'Y';
    	}
    }
    auto get = [&](int &x, int &y) {
    	return y * s + x + 2;
    };
    int c = 0;
    for (int i = 1; i < 30; ++i) {
    	if ((k >> i) & 1) {
    		
    	}
    }
    cout << n << "\n";
    for(int i=1;i<=n;++i){
    	for(int j=1;j<=n;++j){
    		cout<<a[i][j];
    	}
    	cout <<"\n";
    }

    return 0;
}
