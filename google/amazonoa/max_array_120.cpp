#include<bits/stdc++.h>
using namespace std;


int calSubArrayMeanSum(vector<int> &a) {
    int n = a.size(), mod = 1e9 + 7;
    vector<long long> p(n + 1), s(n + 1);
    for (int i = 0; i < n; ++i)
        p[i + 1] = (p[i] + a[i]) % mod;
    for (int l = 1; l <= n; ++l) {
        if (l <= (n + 1) / 2) s[l] = (s[l-1] + p[n + 1 - l] - p[l - 1]) % mod;
        else s[l] = s[n + 1 - l];
    }

    long long ans = 0;
    for (int l = 1; l <= n; l += 1) {
       ans = ans + s[l];
    }
    return ans;
}


int main() {
	string s;
	cin>>s;
	int n=s.size();
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
	{
		if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u'){
			a[i]=1;
		}
	}
	for(int i=0;i<n;++i)
		cout<<a[i]<<" ";cout<<"\n";
	int ans=calSubArrayMeanSum(a);
	cout<<ans<<"\n";
}
