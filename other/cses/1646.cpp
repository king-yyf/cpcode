#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,q;
    cin>>n>>q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin>>a[i];
    }
    vector<long long> s(n+1);
    for (int i = 0; i < n; ++i) {
        s[i+1]=s[i]+a[i];
    }

    while(q--)
    {
    	int x,y;
    	cin>>x>>y;
    	x--;
    	cout << s[y] - s[x] << '\n';
    }

    return 0;
}
