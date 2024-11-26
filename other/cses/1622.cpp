#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void dfs(string s, int i) {
	if (i == s.size()) {
		cout << s << '\n';
	} else {
		for (int j = i; j < s.size(); ++j) {
			if (j == i || s[j] != s[i]) {
				swap(s[j], s[i]);
				dfs(s, i + 1);
			}
		}
	}
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s;
    cin>>s;
    sort(s.begin(), s.end());
    vector<int> f(9);
    f[1]=1;f[0]=1;
    for(int i =2;i<9;++i)
    	f[i]=f[i-1]*i;
    int n =s.size();

    int p=f[n];
    vector<int> a(26);
    for(int i = 0; i < n; ++i) {
    	a[s[i] - 'a']++;
    }
    for (int i = 0; i < 26; ++i) {
    	p/=f[a[i]];
    }
    cout<<p<<'\n';
    dfs(s, 0);




    return 0;
}
