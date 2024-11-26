#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*

https://www.interviewbit.com/problems/count-total-set-bits/
统计从1到n的所有数字的二进制表示中的1的总数。
*/

int solve(int n) {
	long long ans = 0;
	int x = log10(n) / log10(2);
	for (int i = 0; i <= x; i++){
		int c = 1 << i, cnt = 0;
		int set = (n + 1) / c;
		cnt = (set / 2) * c;
		int d = (n + 1) % c;
		if (set % 2 != 0) cnt += d;
		ans = (ans + cnt) % 1000000007;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);



	return 0;
}
