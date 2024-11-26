#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*

https://www.interviewbit.com/problems/xor-ing-the-subarrays/

求数组所有子数组的异或和的异或和
*/


int Solution::solve(vector<int> &a) {
	int ans = 0, n = a.size();
	for (int i = 0; i < n; ++i) {
		long long v = (i + 1ll) * (n - i);
		if (v % 2 != 0) {
			ans = ans ^ a[i];
		}
	}
	return ans;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    

    return 0;
}
