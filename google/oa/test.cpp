#include <bits/stdc++.h>
using namespace std;

int maxScodeDiff(vector<int> &a) {
    int n = a.size();

    function<pair<int,int>(int, int)> dfs1;
    function<pair<int,int>(int, int)> dfs2;

    map<pair<int,int>,pair<int,int>> dp1,dp2;

    dfs1 = [&](int i, int j) {
        if (dp1.count({i, j})) return dp1[{i, j}];
        if (i == j) {
            dp1[{i, j}] = {a[i], 0};
            return dp1[{i, j}];
        }
        pair<int, int> d1{a[i] + dfs2(i + 1, j).first, dfs2(i + 1, j).second};
        pair<int, int> d2{a[j] + dfs2(i, j - 1).first, dfs2(i, j - 1).second};

        if (d1.first - d1.second >= d2.first - d2.second) {
        	dp1[{i, j}] = d1;
        	return d1;
        }
        dp1[{i, j}] = d2;
        return d2;
    };

    dfs2 = [&](int i, int j) {
    	if (dp2.count({i, j})) return dp2[{i, j}];
    	if (i == j) {
    		dp2[{i, j}] = {0, a[i]};
    		return dp2[{i, j}];
    	}
    	pair<int, int> d1{dfs1(i + 1, j).first, dfs1(i + 1, j).second + a[i]};
        pair<int, int> d2{dfs1(i, j - 1).first, dfs1(i, j - 1).second + a[j]};
        if (a[i] > a[j] || (a[i] == a[j] && d1.first - d1.second >= d2.first - d2.second)) {
        	dp2[{i, j}] = d1;
        	return d1;
        } 
        dp2[{i, j}] = d2;
        return d2;
    };

    auto [x, y] = dfs1(0, n - 1);

    return x - y;
}


int main(){

	vector<int> a{7, 5, 18, 9};
	auto c=maxScodeDiff(a);
	cout<<c<<"\n";
	vector<int> a1{7, 3, 12, 6};
	auto c1=maxScodeDiff(a1);
	cout<<c1<<"\n";

}