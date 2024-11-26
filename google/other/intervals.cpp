#include<bits/stdc++.h>

using namespace std;


int miniIntervals(vector<vector<int>> &a) {
	int n = a.size(), ans = 0, last = -1, pre = -1;
	sort(a.begin(), a.end(), [&](auto &x, auto &y){
		if (x[1] == y[1]) return x[0] > y[0];
		return x[1] < y[1];
	});
	for (int i = 0; i < n; ++i) {
		if (pre >= a[i][0]) continue;
		else if (last >= a[i][0]) {
			ans++, pre = last, last = a[i][1];
		} else {
			ans += 2, last = a[i][1], pre = last - 1;
		}
	}
	return ans;
}


int main() {
	// vector<vector<int>> a{
	// 	{3,6},{2,4},{0,2},{4,7}
	// };
	vector<vector<int>> a{
		{1,3},{2,5},{1,4}
	};
	cout<<miniIntervals(a)<<"\n";
}
