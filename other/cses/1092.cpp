#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    long long s = n * (n + 1ll) / 2;

    if (s & 1) {
    	cout << "NO\n";
    	return 0;
    }
    s /= 2;

    vector<int> a,b;
    for (int i = n; i >= 1; --i) {
    	if (i <= s){
    		 a.push_back(i);
    		 s -= i;
    	}
    	else b.push_back(i);
    }

    if (s != 0) {
    	cout << "NO\n";
    	return 0;
    }

    cout << "YES ";

    cout << a.size() << ' ';
    for(auto &x : a) 
    	cout << x << ' ';

    cout << b.size() << ' ';
    for(int i = 0; i < b.size(); ++i)
    	cout << b[i] << " \n"[i == b.size() - 1];


    return 0;
}
