#include<bits/stdc++.h>
using namespace std;

long long countRanges(vector<vector<int>> &rs) {
	long long ans = 0, cnt_l = 0, n = rs.size();
	priority_queue<int, vector<int>, greater<int>> q;
	sort(rs.begin(), rs.end(),[&](auto &x, auto &y){
		return x[0] < y[0];
	});

	for (int i = 0; i < n; ++i) {
		while (q.size() && q.top() < rs[i][0]) {
			cnt_l++; q.pop();
		}
		int l = i + 1, r = n - 1, cnt_r = 0;
		while (l <= r) {
			int md = (l + r) / 2;
			if (rs[md][0] > rs[i][1]) {
				cnt_r = n - md;
				r = md - 1;
			}else l = md + 1;
		}
		ans += cnt_l * cnt_r;
		q.push(rs[i][1]);
	}
	return ans;

}


int main() {
	vector<vector<int>> rs={{5,7},{2,2},{3,4},{7,8}};
	auto p=countRanges(rs);
	cout<<p<<"\n";
}