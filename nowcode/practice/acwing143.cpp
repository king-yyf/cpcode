#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, K = 32, M = K * N;
int tr[M][2], idx, cnt[M];

void add(int x) {
    int p = 0;
    for (int i = K - 1; ~i; --i) {
        int b = (x >> i) & 1;
        if (!tr[p][b]) tr[p][b] = ++idx;
        cnt[p = tr[p][b]]++;
    }
}

void del(int x) {
    int p = 0;
    for (int i = K - 1; ~i; --i) 
        cnt[p = tr[p][(x >> i) & 1]]--;
}

int query(int x) {
    int p = 0, ans = 0;
    for (int i = K - 1; ~i; --i) {
        int b = (x >> i) & 1;
        ans = ans << 1;
        if (cnt[tr[p][b]]) ans++, p = tr[p][b];
        else p = tr[p][!b];
    }
    return ans;
}

int main(){
	int n,ans = 0, x;
	scanf("%d",&n);
	for (int i = 0; i < n; ++i) {
		scanf("%d",&x);
		if (i > 0) ans = max(ans, query(~x));
		add(x);
	}
	printf("%d\n", ans);
	return 0;
}
