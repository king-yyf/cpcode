#include <bits/stdc++.h>
using namespace std;

using ll = long long;


// template<size_t N>
// bitset<N+1> partial_sum(vector<int> vs){
//   int sum=0;
//   for(int v:vs) sum+=v;
//   assert(sum<=N);
//   vector<int> cnt(sum+1,0);
//   for(int v:vs) cnt[v]++;
//   for(int i=1;i*2<=sum;i++){
//     int num=(cnt[i]-1)/2;
//     cnt[i]-=num*2;
//     cnt[i*2]+=num;
//   }
//   bitset<N+1> dp;
//   dp[0]=1;
//   for(int i=1;i<=sum;i++)
//     for(int t=0;t<cnt[i];t++)
//       dp|=dp<<i;
//   return dp;
// }

template<size_t n>
bitset<n + 1> partial_sum(vector<int> &a) {
	int s = accumulate(a.begin(), a.end(), 0ll);
	assert(s <= n);
	vector<int> cnt(s + 1);
	for (int x : a) {
		cnt[x] ++;
	}
	for (int i = 1; i * 2 <= s; ++i) {
		int num = (cnt[i] - 1) / 2;
		cnt[i] -= num * 2;
		cnt[i * 2] += num;
	}
	bitset<n + 1> dp;
	dp[0] = 1;
	for (int i = 1; i <= s; ++i) 
		for (int t = 0; t < cnt[i]; ++t) 
			dp |= dp << i;
	return dp;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    vector<int> a {2, 3, 5, 2, 2};

    auto dp = partial_sum<20>(a);

    for (int i =  0; i < 20; ++i) {
    	cout << dp.test(i) <<' ';
    }

    return 0;
}
