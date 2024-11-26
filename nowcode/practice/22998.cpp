#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, K = 23, M = K * N;
int tr[M][2], idx, id[M]; 
void add(int x, int k) {
    int p = 0;
    for (int i = K - 1; ~i; --i) {
        int b = (x >> i) & 1;
        if (!tr[p][b]) tr[p][b] = ++idx;
        p = tr[p][b];
    }
    id[p] = k;
}

int query(int x, int &y) {
    int p = 0, ans = 0;
    for (int i = K - 1; ~i; --i) {
        int b = (x >> i) & 1;
        if (tr[p][!b]) ans |= 1 << i, p = tr[p][!b];
        else p = tr[p][b];
    }
    y = id[p];
    return ans;
}

int s[N], x, y, n;

int main(){
	scanf("%d",&n);
	add(0,0);
	int ans = 0, l = 1, r = 1;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &s[i]);
		s[i] ^= s[i - 1];
		x = query(s[i], y);
		if (x > ans) ans = x, l = y + 1, r = i;
		add(s[i], i);
	}
	printf("%d %d %d\n", ans,l,r);
	
}