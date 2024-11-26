#include<bits/stdc++.h>
using namespace std;

int maxtimes(vector<int> &a, int k) {
    int m = 2 * k, n = a.size();
    map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        int x = m > 0 ? a[i] % m : a[i];
        mp[x]++;
    }
    int ans = 0;
    for (auto &[_, v]: mp) {
        ans = max(ans, v);
    }
    return ans;
}

int main() {
	std::vector<std::vector<int>> examples = {
        {3, 1, 3},
        {1, 2, 2},
        {2, 3, 4, 7, 4, 9, 11},
        {3,6,6,2,7}
    };
    vector<int> ks = {1, 1, 1,0};
    for (int i = 0; i < examples.size(); ++i) {
    	cout << maxtimes(examples[i], ks[i]) << "\n";
    }
}