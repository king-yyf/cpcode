#include<bits/stdc++.h>
using namespace std;
using i128 = __int128;

void print(i128 x){
    if(x < 0) putchar('-'),x = - x;
    if(x > 9) print(x/10); 
    putchar(x%10+'0');
}

i128 almostDiff(vector<int> &a){
	int n = a.size();
	i128 ans = 0, s = 0;
	map<int, int> mp;
	for (long long i = 0; i < n; ++i) {
		ans += (i128)a[i] * i - s;
		ans -= mp[a[i] - 1] - mp[a[i] + 1];
		mp[a[i]]++;
		s += a[i];
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false); 
    cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	print(almostDiff(a));
}
