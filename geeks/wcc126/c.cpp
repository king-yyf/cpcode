#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string cyclicTree(int n, vector<vector<int>> &es) {
	vector<int> p(n);
	for (auto &e : es) {
		int x = e[0], y = e[1];
		x--, y--;
		p[x]++;
		p[y]++;
	}

	for (int i = 0; i < n; ++i) {
	    if (p[i] != 2) return "Yes";	
	}
	return "No";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    

    return 0;
}
