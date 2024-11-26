// https://www.hackerrank.com/challenges/xor-subsequence/problem?isFullScreen=true


#include<bits/stdc++.h>
using namespace std;

mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}

int xorSumSeqSum(vector<int> &a) {
	int n = a.size(), m = 16;
	long long sum = 0;
	for (int i = 0; i < m; ++i) {
		vector<int> s(n), p(n + 1);
		s[n - 1] = (a[n - 1] >> i & 1);
		for (int j = n - 2; j >= 0; --j) {
			s[j] = (s[j + 1] + (a[j] >> i & 1)) % 2;
		}
		for (int j = 0; j < n; ++j) 
			p[j + 1] = p[j] + s[j];
		for (int j = 0; j < n; ++j) {
			int x = 0;
			if (a[j] >> i & 1) {
				x = (s[j] == 0) ? j + 1 - p[j + 1] : p[j + 1];
			} else {
				x = (s[j] == 0) ? p[j + 1] : j + 1 - p[j + 1];
			}
			sum += x * 1ll * (1 << i);
		}
	}
	return sum;
}

int broutforce(vector<int> &a) {
	long long s = 0;
	int n = a.size();
	for (int i = 0; i < n; ++i) {
		int x = 0;
		for (int j = i; j < n; ++j) {
			x = x ^ a[j];
			s += x;
		}
	}
	return s;
}


vector<int> max_freq_xor_brout_force(vector<int> &a) {
	map<int,int> mp;
	int n = a.size();
	for (int i = 0; i < n; ++i) {
		int x = 0;
		for (int j = 0; j < n; ++j) {
			x = x ^ a[j];
			mp[x]++;
		}
	}
	int x = 0, y = -1;
	for (auto &[k, v] : mp) {
		if (v > y) {
			y = v, x = k;
		}
	}
	return {x, y};
}


int main() {
	int mx = 100, N = 4000;
	bool o = 1;

	vector<int> a = {9,3,5,6,10,8,4};
	// cout << xorSumSeqSum(a) << " " << broutforce(a) << "\n";
	auto c = max_freq_xor_brout_force(a);
	cout << c[0] << ", " << c[1] << "\n";
}